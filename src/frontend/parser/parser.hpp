#ifndef PARSER
#define PARSER

#include "../scanner/scanner.hpp"

typedef struct {
    Scanner* scanner;
    int position;
    bool has_error;
} Parser;

Parser* create_parser(Scanner* scanner);

void free_parser(Parser* parser);

void parse(Parser* parser);

#endif // PARSER