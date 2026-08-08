#[derive(Debug)]
pub enum TokenType {
    TokenIdent,

    //  KEYWORDS
    TokenLet,

    //  TYPES
    TokenInt,
    TokenFloat,

    //  SYMBOLS
    TokenEqual,
    TokenColon,
    TokenSub,
    TokenAdd, // also is used for unary negation
    TokenMul,
    TokenDiv,
    TokenMod,
    TokenLeftParen,
    TokenRightParen,
    TokenPeriod,
}

#[derive(Debug)]
pub struct Token {
    pub lexeme: String,
    pub token_type: TokenType,
}
