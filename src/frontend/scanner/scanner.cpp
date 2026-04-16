#include <string>
#include <vector>
#include <cctype>
#include "scanner.hpp"

Scanner* create_scanner(const string& source) {
    Scanner* scanner = new Scanner;
    scanner->source = source;
    scanner->line = 1;
    scanner->column = 1;
    scanner->position = 0;
    scanner->has_error = false;
    return scanner;
}

void free_scanner(Scanner* scanner) {
    for (Token* token : scanner->tokens) {
        free_token(token);
    }
    delete scanner;
}

// Internal helper functions for scanning //

static char peek(Scanner* scanner, int offset = 0) {
    if (scanner->position + offset >= scanner->source.length()) {
        return '\0'; // TOKEN_EOF
    }
    return scanner->source[scanner->position + offset];
}

static char advance(Scanner* scanner) {
    char current_char = peek(scanner);
    if (current_char == '\n') {
        scanner->line++;
        scanner->column = 1;
    } else {
        scanner->column++;
    }
    scanner->position++;
    return current_char;
}

static void pass_spaces(Scanner* scanner) {
    while (isspace((unsigned char)peek(scanner))) {
        advance(scanner);
    }
}

static void add_token(Scanner* scanner, TokenType type, const string& lexeme) {
    scanner->tokens.push_back(create_token(type, lexeme));
}

static bool is_keyword(Scanner* scanner, const string& keyword) {
    int length = keyword.length();
    if (scanner->position + length > scanner->source.length()) {
        return false;
    }
    if (scanner->source.substr(scanner->position, length) != keyword) {
        return false;
    }

    char next = peek(scanner, length);
    return !isalnum((unsigned char)next) && next != '_';
}

static bool is_ident(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

// Public API for lexical scanning //

void scan(Scanner* scanner) {
    for (Token* token : scanner->tokens) {
        free_token(token);
    }
    scanner->tokens.clear();
    scanner->position = 0;
    scanner->line = 1;
    scanner->column = 1;
    scanner->has_error = false;

    pass_spaces(scanner);

    while (peek(scanner) != '\0') {
        char current_char = peek(scanner);

        // Skip comments and stuff
        if (current_char == '/') {
            if (peek(scanner, 1) == '/') {
                // Single-line comment
                while (peek(scanner) != '\n' && peek(scanner) != '\0') {
                    advance(scanner);
                }
                pass_spaces(scanner);
                continue;
            } else if (peek(scanner, 1) == '*') {
                advance(scanner);
                advance(scanner);
                while (!(peek(scanner) == '*' && peek(scanner, 1) == '/') && peek(scanner) != '\0') {
                    advance(scanner);
                }
                if (peek(scanner) == '\0') {
                    add_token(scanner, ERROR, "Unterminated multi-line comment");
                    scanner->has_error = true;
                    return;
                }
                advance(scanner);
                advance(scanner);
                pass_spaces(scanner);
                continue;
            }
        }

        // Keyword checking
        if (is_keyword(scanner, "set")) {
            add_token(scanner, SET, "set");
            advance(scanner);
            advance(scanner);
            advance(scanner);
            pass_spaces(scanner);
            continue;
        }

        if (is_ident(current_char)) {
            int start = scanner->position;
            while (is_ident(peek(scanner))) {
                advance(scanner);
            }
            add_token(scanner, IDENTIFIER, scanner->source.substr(start, scanner->position - start));
            pass_spaces(scanner);
            continue;
        }

        // Probably is unoptimal to check for float literals this way, but it should work for now
        if (isdigit((unsigned char)current_char)) {
            int start = scanner->position;
            while (isdigit((unsigned char)peek(scanner))) {
                advance(scanner);
            }
            if (peek(scanner) == '.') {
                if (isdigit((unsigned char)peek(scanner, 1))) {
                    advance(scanner);
                    while (isdigit((unsigned char)peek(scanner))) {
                        advance(scanner);
                    }
                    add_token(scanner, FLOAT_LITERAL, scanner->source.substr(start, scanner->position - start));
                } else {
                    add_token(scanner, ERROR, scanner->source.substr(start, scanner->position - start) + ".");
                    scanner->has_error = true;
                    advance(scanner);
                }
            } else {
                add_token(scanner, INT_LITERAL, scanner->source.substr(start, scanner->position - start));
            }
            continue;
        } else if (peek(scanner) == '.' && isdigit((unsigned char)peek(scanner, 1))) {
            int start = scanner->position;
            advance(scanner);
            while (isdigit((unsigned char)peek(scanner))) {
                advance(scanner);
            }
            add_token(scanner, FLOAT_LITERAL, scanner->source.substr(start, scanner->position - start));
            continue;
        }

        switch (current_char) {
            case '+':
                add_token(scanner, PLUS, "+");
                advance(scanner);
                break;
            case '-':
                add_token(scanner, MINUS, "-");
                advance(scanner);
                break;
            case '*':
                add_token(scanner, STAR, "*");
                advance(scanner);
                break;
            case '/':
                add_token(scanner, SLASH, "/");
                advance(scanner);
                break;
            case '%':
                add_token(scanner, PERCENT, "%");
                advance(scanner);
                break;
            case '(':
                add_token(scanner, LPAREN, "(");
                advance(scanner);
                break;
            case ')':
                add_token(scanner, RPAREN, ")");
                advance(scanner);
                break;
            case '=':
                add_token(scanner, EQUAL, "=");
                advance(scanner);
                break;
            case ';':
                add_token(scanner, SEMICOLON, ";");
                advance(scanner);
                break;
            default:
                add_token(scanner, UNKNOWN, string(1, current_char));
                scanner->has_error = true;
                advance(scanner);
                break;
        }
        pass_spaces(scanner);
    }

    add_token(scanner, TOKEN_EOF, "");
}