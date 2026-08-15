#[derive(Debug)]
#[allow(unused)]
pub enum Token {
    Ident(String),
    Number(f64),

//  Keywords
    Let,

//  Symbols
    Equal,
}

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
        if !self.eof() {
            self.pos += 1;
        }
    }

    fn current(&self) -> u8 {
        self.source.as_bytes()[self.pos]
    }

    fn eof(&self) -> bool {
        self.pos >= self.source.len()
    }

    fn skip_ws(&mut self) {
        while !self.eof() && (self.current() as char).is_ascii_whitespace() {
            self.consume();
        }
    }

//  Public
    pub fn lex(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        while !self.eof() {
            self.skip_ws();

            let curr = self.current();
            match curr {
                b'=' => {
                    self.consume();
                    tokens.push(Token::Equal);
                }

                _ => {
                    if char::is_alphabetic(curr as char) || curr == b'_' {
                        let start = self.pos;
                        
                        while !self.eof() && char::is_alphanumeric(self.current() as char) {
                            self.consume();
                        }

                        tokens.push(match self.source[start..self.pos].as_ref() {
                            "let" => Token::Let,

                            ident => Token::Ident(ident.to_string())
                        });
                    } else if char::is_digit(curr as char, 10) {
                        let start = self.pos;
                        let mut is_float = false;

                        while !self.eof() {
                            let byte = self.current();

                            if char::is_digit(byte as char, 10) {
                                self.consume();
                            } else if byte == b'.' && !is_float {
                                is_float = true;
                                
                                self.consume();
                            } else {
                                break;
                            }
                        }

                        tokens.push(Token::Number(self.source[start..self.pos].parse().unwrap()));
                    }
                }
            }
        }

        tokens
    }
}
