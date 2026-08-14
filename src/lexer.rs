use super::tokens::Token;

pub struct Lexer<'a> {
    pub source: &'a str,
    pub pos: usize
}

impl<'a> Lexer<'a> {
    pub fn new(source: &'a str) -> Self {
        Self {
            source,
            pos: 0
        }
    }

//  Helper functions
    fn consume(&mut self) {
        self.pos += 1;
    }

//  Public
    pub fn lex(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        tokens
    }
}
