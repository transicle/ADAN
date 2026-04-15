#include "../../tokens/tokens.hpp"
#include "parser.hpp"

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

static Token* expect(Parser* parser, TokenType type) {

}

// Public API for parsing //

void parse(Parser* parser) {

}