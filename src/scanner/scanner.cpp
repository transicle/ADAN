#include <string>
#include <cctype>
#include "scanner.hpp"
#include "tokens.hpp"

Scanner* create_scanner(const string& source) {
    Scanner* scanner = new Scanner;
    scanner->source = source;
    scanner->line = 1;
    scanner->column = 1;
    scanner->position = 0;
    return scanner;
}

void free_scanner(Scanner* scanner) {
    delete scanner;
}

// Internal helper functions for scanning //

static char peek(Scanner* scanner, int offset = 0) {
    if (scanner->position + offset >= scanner->source.length()) {
        return '\0'; // EOF
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

// Public API for lexical scanning //

void scan(Scanner* scanner) {
    pass_spaces(scanner);

    while (peek(scanner) != '\0') {
        char current_char = peek(scanner);

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
                    create_token(TOKEN_FLOAT_LITERAL, scanner->source.substr(start, scanner->position - start));
                } else {
                    create_token(TOKEN_ERROR, scanner->source.substr(start, scanner->position - start) + ".");
                    advance(scanner);
                }
            } else {
                create_token(TOKEN_INT_LITERAL, scanner->source.substr(start, scanner->position - start));
            }
            continue;
        } else if (peek(scanner) == '.' && isdigit((unsigned char)peek(scanner, 1))) {
            int start = scanner->position;
            advance(scanner);
            while (isdigit((unsigned char)peek(scanner))) {
                advance(scanner);
            }
            create_token(TOKEN_FLOAT_LITERAL, scanner->source.substr(start, scanner->position - start));
            continue;
        }

        switch (current_char) {
            case '+':
                create_token(TOKEN_PLUS, "+");
                advance(scanner);
                break;
            case '-':
                create_token(TOKEN_MINUS, "-");
                advance(scanner);
                break;
            case '*':
                create_token(TOKEN_STAR, "*");
                advance(scanner);
                break;
            case '/':
                create_token(TOKEN_SLASH, "/");
                advance(scanner);
                break;
            case '%':
                create_token(TOKEN_PERCENT, "%");
                advance(scanner);
                break;
            case '(':
                create_token(TOKEN_LPAREN, "(");
                advance(scanner);
                break;
            case ')':
                create_token(TOKEN_RPAREN, ")");
                advance(scanner);
                break;
            default:
                create_token(TOKEN_UNKNOWN, string(1, current_char));
                advance(scanner);
                break;
        }
        pass_spaces(scanner);
    }
}