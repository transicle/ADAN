#include "ast.hpp"

using namespace std;

static ASTNode* create_node(NodeType type) {
    ASTNode* node = new ASTNode;
    node->type = type;
    return node;
}

void free_ast(ASTNode* node) {
    if (!node) {
        return;
    }

    free_ast(node->left);
    free_ast(node->right);

    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }

    delete[] node->children;
    delete node;
}

ASTNode* create_program_node(const vector<ASTNode*>& statements) {
    ASTNode* node = create_node(NODE_PROGRAM);
    node->children = new ASTNode*[statements.size()];
    for (size_t i = 0; i < statements.size(); i++) {
        node->children[i] = statements[i];
    }
    node->child_count = statements.size();
    return node;
}

ASTNode* create_declaration_node(string name, ASTNode* initializer) {
    ASTNode* node = create_node(NODE_DECLARATION);
    node->value = name;
    node->left = initializer;
    return node;
}

ASTNode* create_assignment_node(string name, ASTNode* value) {
    ASTNode* node = create_node(NODE_ASSIGNMENT);
    node->value = name;
    node->left = value;
    return node;
}

ASTNode* create_expression_statement_node(ASTNode* expr) {
    ASTNode* node = create_node(NODE_EXPRESSION);
    node->left = expr;
    return node;
}

ASTNode* create_binary_expr_node(string op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(NODE_BINARY_EXPR);
    node->value = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_identifier_node(string name) {
    ASTNode* node = create_node(NODE_IDENTIFIER);
    node->value = name;
    return node;
}

ASTNode* create_int_literal_node(string value) {
    ASTNode* node = create_node(NODE_INT_LITERAL);
    node->value = value;
    return node;
}

ASTNode* create_float_literal_node(string value) {
    ASTNode* node = create_node(NODE_FLOAT_LITERAL);
    node->value = value;
    return node;
}