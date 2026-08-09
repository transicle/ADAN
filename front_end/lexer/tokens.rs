#[derive(Debug)]
#[allow(unused)] // genuinely have to put this, because they are used..
pub enum TokenType {
    TokenIdent(String),

    TokenLet,

    TokenInt(String),
    TokenFloat(String),

    TokenEqual,
    TokenColon,
    TokenLeftParen,
    TokenRightParen,
    TokenPeriod,

    TokenSub, // also is used for unary negation
    TokenAdd,
    TokenMul,
    TokenDiv,
    TokenMod,
}
