use super::tokens::TokenType;

pub struct Lexer {
    pub source: Vec<char>,
    pub position: usize,
}

impl Lexer {
    pub fn new(source: String) -> Self {
        Self {
            source: source.chars().collect(),
            position: 0,
        }
    }

    // core

    fn peek(&self, offset: usize) -> char {
        *self.source.get(self.position + offset).unwrap_or(&'\0')
    }

    fn peek_next(&self) -> char {
        self.peek(1)
    }

    fn current(&self) -> char {
        self.peek(0)
    }

    fn consume(&mut self) {
        self.position += 1;
    }

    fn at_end(&self) -> bool {
        self.position >= self.source.len()
    }

    // pub

    pub fn lex(&mut self) -> Vec<TokenType> {
        let mut tokens = Vec::new();

        while !self.at_end() {
            let current = self.current();

            match current {
                ' ' | '\0' | '\r' | '\t' | '\n' => {
                    self.consume();
                }

                c if c.is_alphabetic() || c == '_' => {
                    let token = self.read_ident();
                    tokens.push(token);
                }

                c if c.is_ascii_digit() => {
                    let token = self.read_number();
                    tokens.push(token);
                }

                // regular symbols
                ':' => {
                    self.consume();
                    tokens.push(TokenType::TokenColon);
                }

                '=' => {
                    self.consume();
                    tokens.push(TokenType::TokenEqual);
                }

                '(' => {
                    self.consume();
                    tokens.push(TokenType::TokenLeftParen);
                }

                ')' => {
                    self.consume();
                    tokens.push(TokenType::TokenRightParen);
                }

                '*' => {
                    self.consume();
                    tokens.push(TokenType::TokenMul);
                }

                '/' => {
                    self.consume();
                    tokens.push(TokenType::TokenDiv);
                }

                '+' => {
                    self.consume();
                    tokens.push(TokenType::TokenAdd);
                }

                '-' => {
                    self.consume();
                    tokens.push(TokenType::TokenSub);
                }

                '%' => {
                    self.consume();
                    tokens.push(TokenType::TokenMod);
                }

                '.' => {
                    self.consume();
                    tokens.push(TokenType::TokenPeriod);
                }

                // boring unhandled stufff
                _ => {
                    println!("Unknown symbol: \"{}\"", current);
                    self.consume();
                }
            }
        }

        tokens
    }

    // helpers

    fn get_keyword(&self, keyword: &str) -> Option<TokenType> {
        match keyword {
            "let" => Some(TokenType::TokenLet),
            _ => None,
        }
    }

    fn read_ident(&mut self) -> TokenType {
        let start = self.position;

        while self.current().is_alphanumeric() || self.current() == '_' {
            self.consume();
        }

        let lexeme: String = self.source[start..self.position].iter().collect();
        let token_type = self
            .get_keyword(&lexeme)
            .unwrap_or(TokenType::TokenIdent(lexeme));

        token_type
    }

    fn read_number(&mut self) -> TokenType {
        let start = self.position;
        let mut is_float = false;

        while self.current().is_ascii_digit()
            || (self.current() == '.' && !is_float && self.peek_next().is_ascii_digit())
        {
            if self.current() == '.' {
                is_float = true;
            }
            self.consume();
        }

        let lexeme: String = self.source[start..self.position].iter().collect();
        let token_type = if is_float {
            TokenType::TokenFloat(lexeme)
        } else {
            TokenType::TokenInt(lexeme)
        };

        token_type
    }
}
