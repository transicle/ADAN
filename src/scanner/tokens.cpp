#include <string>

#include "tokens.hpp"

Token* make_token(TokenType type, const char* lexeme) {
    Token* token = new Token;
    token->type = type;
    token->lexeme = string(lexeme);
    return token;
}

void free_token(Token* token) {
    delete token;
}