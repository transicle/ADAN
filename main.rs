mod front_end;
use front_end::lexer::lexer::Lexer;

use std::fs;

fn main() {
    // testing file for now
    let source = fs::read_to_string("./test/sample.adn")
        .unwrap_or("".to_string());

    let mut lexer = Lexer::new(source);

    let tokens = lexer.lex();
    for token in &tokens {
        println!("{:?} -> {}", token.token_type, token.lexeme);
    }
}
