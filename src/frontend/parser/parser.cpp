#include "../../tokens/tokens.hpp"
#include "parser.hpp"
#include "../../ast/ast.hpp"

static Token* peek(Parser* parser, int offset = 0);

static Token* advance_token(Parser* parser);

static Token* expect(Parser* parser, TokenType type, const string& error_message);

static ASTNode* parse_program(Parser* parser);

static ASTNode* parse_statement(Parser* parser);

static ASTNode* parse_declaration(Parser* parser);

static ASTNode* parse_assignment(Parser* parser);

static ASTNode* parse_expression_statement(Parser* parser);

static ASTNode* parse_infix(Parser* parser, ASTNode* left);

static ASTNode* parse_expression(Parser* parser, int precedence = 0);

static ASTNode* parse_prefix(Parser* parser);

Parser* create_parser(Scanner* scanner) {
    Parser* parser = new Parser;
    parser->scanner = scanner;
    parser->position = 0;
    parser->has_error = false;
    parser->ast = nullptr;
    return parser;
}

void free_parser(Parser* parser) {
    delete parser;
}

// Helper functions for parsing //

static Token* peek(Parser* parser, int offset) {
    int index = parser->position + offset;
    if (index >= 0 && index < (int)parser->tokens.size()) {
        return parser->tokens[index];
    }
    return nullptr;
}

static Token* expect(Parser* parser, TokenType type, const string& error_message) {
    Token* token = peek(parser);
    if (!token || token->type != type) {
        parser->has_error = true;
        return nullptr;
    }
    (void)error_message;
    advance_token(parser);
    return token;
}

static Token* advance_token(Parser* parser) {
    Token* current = peek(parser);
    if (current) {
        parser->position++;
    }
    return current;
}

static int get_precedence(TokenType type) {
    switch (type) {
        case TokenType::PLUS:
        case TokenType::MINUS:
            return 1;
        case TokenType::STAR:
        case TokenType::SLASH:
        case TokenType::PERCENT:
            return 2;
        default:
            return 0;
    }
}

// Recursive descent parsing functions (statements) //

static ASTNode* parse_program(Parser* parser) {
    vector<ASTNode*> statements;
    while (peek(parser) && peek(parser)->type != TokenType::TOKEN_EOF) {
        ASTNode* stmt = parse_statement(parser);
        if (stmt) {
            statements.push_back(stmt);
        } else {
            advance_token(parser);
        }
    }
    return create_program_node(statements);
}

static ASTNode* parse_statement(Parser* parser) {
    Token* token = peek(parser);
    if (!token) {
        return nullptr;
    }
    switch (token->type) {
        case TokenType::SET:
            return parse_declaration(parser);
        case TokenType::IDENTIFIER:
            if (peek(parser, 1) && peek(parser, 1)->type == TokenType::EQUAL) {
                return parse_assignment(parser);
            }
            return parse_expression_statement(parser);
        case TokenType::INT_LITERAL:
        case TokenType::FLOAT_LITERAL:
        case TokenType::LPAREN:
            return parse_expression_statement(parser);
        default:
            parser->has_error = true;
            return nullptr;
    }
}

// handles `set var = expr;` statements
static ASTNode* parse_declaration(Parser* parser) {
    expect(parser, TokenType::SET, "Expected 'set' keyword for variable declaration");
    Token* identifier = expect(parser, TokenType::IDENTIFIER, "Expected variable name after 'set'");
    expect(parser, TokenType::EQUAL, "Expected '=' after variable name in declaration");
    ASTNode* initializer = parse_expression(parser);
    expect(parser, TokenType::SEMICOLON, "Expected ';' after variable declaration");

    if (!identifier || !initializer) {
        parser->has_error = true;
        return nullptr;
    }

    return create_declaration_node(identifier->lexeme, initializer);
}

// handles `var = expr;` statements
static ASTNode* parse_assignment(Parser* parser) {
    Token* identifier = expect(parser, TokenType::IDENTIFIER, "Expected variable name for assignment");
    expect(parser, TokenType::EQUAL, "Expected '=' after variable name in assignment");
    ASTNode* value = parse_expression(parser);
    expect(parser, TokenType::SEMICOLON, "Expected ';' after assignment");

    if (!identifier || !value) {
        parser->has_error = true;
        return nullptr;
    }

    return create_assignment_node(identifier->lexeme, value);
}

// handles `var + 1;` standalone expressions
static ASTNode* parse_expression_statement(Parser* parser) {
    ASTNode* expr = parse_expression(parser);
    expect(parser, TokenType::SEMICOLON, "Expected ';' after expression");

    if (!expr) {
        parser->has_error = true;
        return nullptr;
    }

    return create_expression_statement_node(expr);
}

static ASTNode* parse_infix(Parser* parser, ASTNode* left) {
    Token* token = peek(parser);
    if (!token) {
        return nullptr;
    }
    switch (token->type) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
        case TokenType::PERCENT: {
            string op = token->lexeme;
            int precedence = get_precedence(token->type);
            advance_token(parser);
            ASTNode* right = parse_expression(parser, precedence);
            if (!right) {
                return nullptr;
            }
            return create_binary_expr_node(op, left, right);
        }
        default:
            parser->has_error = true;
            return nullptr;
    }
}

// Pratt parser for handling various expressions //

static ASTNode* parse_expression(Parser* parser, int precedence) {
    Token* token = peek(parser);
    if (!token) {
        return nullptr;
    }
    ASTNode* left = parse_prefix(parser);
    if (!left) {
        parser->has_error = true;
        return nullptr;
    }

    while (true) {
        token = peek(parser);
        if (!token || get_precedence(token->type) <= precedence) {
            break;
        }
        left = parse_infix(parser, left);
        if (!left) {
            parser->has_error = true;
            return nullptr;
        }
    }
    return left;
}

static ASTNode* parse_prefix(Parser* parser) {
    Token* token = peek(parser);
    if (!token) {
        return nullptr;
    }
    switch (token->type) {
        case TokenType::IDENTIFIER:
            advance_token(parser);
            return create_identifier_node(token->lexeme);
        case TokenType::INT_LITERAL:
            advance_token(parser);
            return create_int_literal_node(token->lexeme);
        case TokenType::FLOAT_LITERAL:
            advance_token(parser);
            return create_float_literal_node(token->lexeme);
        case TokenType::LPAREN: {
            advance_token(parser);
            ASTNode* expr = parse_expression(parser);
            if (!expr || !expect(parser, TokenType::RPAREN, "Expected ')' after expression")) {
                parser->has_error = true;
                return nullptr;
            }
            return expr;
        }
        default:
            parser->has_error = true;
            return nullptr;
    }
}

// Public API for parsing //

void parse(Parser* parser) {
    parser->tokens = parser->scanner->tokens;
    parser->position = 0;
    parser->has_error = parser->scanner->has_error;

    if (parser->has_error) {
        parser->ast = nullptr;
        return;
    }

    parser->ast = parse_program(parser);
}