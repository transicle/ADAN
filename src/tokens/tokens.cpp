#include <string>
#include "tokens.hpp"

Token* create_token(TokenType type, string lexeme) {
    Token* token = new Token;
    token->type = type;
    token->lexeme = lexeme;
    return token;
}

void free_token(Token* token) {
    delete token;
}