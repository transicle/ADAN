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
