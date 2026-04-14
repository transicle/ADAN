#ifndef TOKENS
#define TOKENS

#include <string>

using namespace std;

typedef enum {
    TOKEN_EOF,

    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    
    // Delimiters
    TOKEN_LPAREN,
    TOKEN_RPAREN,
} TokenType;

typedef struct {
    TokenType type;
    string lexeme;
} Token;

Token* make_token(TokenType type, string lexeme);

void free_token(Token* token);

#endif