#[derive(Debug)]
pub enum Token {
    Ident(String),
    Number(f64),

//  Keywords
    Let,
    
//  Symbols
    Equal,
}
