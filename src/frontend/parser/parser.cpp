#include "../../tokens/tokens.hpp"
#include "parser.hpp"
#include "../../ast/ast.hpp"

Parser* create_parser(Scanner* scanner) {
    Parser* parser = new Parser;
    parser->scanner = scanner;
    parser->position = 0;
    parser->has_error = false;
    return parser;
}

void free_parser(Parser* parser) {
    delete parser;
}

// Helper functions for parsing //

static Token* peek(Parser* parser, int offset = 0) {
    
}

static Token* expect(Parser* parser, TokenType type, const string& error_message) {

}

static Token advance(Parser* parser) {

}

// Recursive descent parsing functions (statements) //

static ASTNode* parse_program(Parser* parser) {

}

static ASTNode* parse_statement(Parser* parser) {

}

// handles `set var = expr;` statements
static ASTNode* parse_declaration(Parser* parser) {

}

// handles `var = expr;` statements
static ASTNode* parse_assignment(Parser* parser) {

}

// handles `var + 1;` standalone expressions
static ASTNode* parse_expression_statement(Parser* parser) {

}

// Pratt parser for handling various expressions //

static ASTNode* parse_expression(Parser* parser, int precedence = 0) {

}

static ASTNode* parse_prefix(Parser* parser) {

}

// Public API for parsing //

void parse(Parser* parser) {

}