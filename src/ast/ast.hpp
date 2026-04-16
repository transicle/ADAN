#ifndef AST
#define AST

#include <string>
#include <vector>

using namespace std;

typedef enum {
    NODE_PROGRAM,
    NODE_STATEMENT,
    NODE_EXPRESSION,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_BINARY_EXPR,
    NODE_IDENTIFIER,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    string value;
    ASTNode* left = nullptr;
    ASTNode* right = nullptr;
    ASTNode** children = nullptr;
    int child_count = 0;
} ASTNode;

void free_ast(ASTNode* node);

ASTNode* create_program_node(const vector<ASTNode*>& statements);

ASTNode* create_declaration_node(string name, ASTNode* initializer);

ASTNode* create_assignment_node(string name, ASTNode* value);

ASTNode* create_expression_statement_node(ASTNode* expr);

ASTNode* create_binary_expr_node(string op, ASTNode* left, ASTNode* right);

ASTNode* create_identifier_node(string name);

ASTNode* create_int_literal_node(string value);

ASTNode* create_float_literal_node(string value);

#endif // AST