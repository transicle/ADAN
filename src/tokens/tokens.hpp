#ifndef TOKENS
#define TOKENS

#include <string>

using namespace std;

typedef enum {
    TOKEN_EOF,
    UNKNOWN,
    ERROR,
    IDENTIFIER,

    // Keywords
    SET,

    // Literals
    INT_LITERAL,
    FLOAT_LITERAL,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    EQUAL,
    SEMICOLON,
    
    // Delimiters
    LPAREN,
    RPAREN,
} TokenType;

typedef struct {
    TokenType type;
    string lexeme;
} Token;

Token* create_token(TokenType type, string lexeme);

void free_token(Token* token);

#endif // TOKENS