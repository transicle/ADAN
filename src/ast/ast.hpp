#ifndef AST
#define AST

#include <string>

using namespace std;

typedef enum {
    NODE_PROGRAM,
    NODE_STATEMENT,
    NODE_EXPRESSION,
    NODE_ASSIGNMENT,
    NODE_BINARY_EXPR,
    NODE_IDENTIFIER,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    string value;
    ASTNode* left;
    ASTNode* right;
    ASTNode** children;
    int child_count;
} ASTNode;

#endif // AST