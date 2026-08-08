mod front_end;
use front_end::lexer::lexer::Lexer;

fn main() {
    let source = String::from("let x = 5");
    let mut lexer = Lexer::new(source);

    let tokens = lexer.lex();
    for token in &tokens {
        println!("{:?} -> {}", token.token_type, token.lexeme);
    }
}
