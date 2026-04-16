#ifndef PARSER
#define PARSER

#include <vector>
#include "../scanner/scanner.hpp"
#include "../../ast/ast.hpp"

using namespace std;

typedef struct {
    Scanner* scanner;
    vector<Token*> tokens;
    int position;
    bool has_error;
    ASTNode* ast;
} Parser;

Parser* create_parser(Scanner* scanner);

void free_parser(Parser* parser);

void parse(Parser* parser);

#endif // PARSER