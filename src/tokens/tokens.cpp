#include <string>
#include <iostream>
#include "tokens.hpp"

Token* create_token(TokenType type, string lexeme) {
    Token* token = new Token;
    token->type = type;
    token->lexeme = lexeme;
    cout << "Created token: " << lexeme << " (type: " << type << ")" << endl;
    return token;
}

void free_token(Token* token) {
    delete token;
}