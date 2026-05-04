from .tokens import NewToken, TokenType, Token
from typing import List

# basically we want to take in the source code, read everything
#   and output a token stream that's functionally identical

class Scanner():
    def __init__(self,
                 Source: str,
                 Line: int,
                 Column: int,
                 Position: int):
        self.Source = Source
        self.Line = Line
        self.Column = Column
        self.Position = Position

# (core) helpers first

def Consume(Lexer: Scanner) -> str:
    if Lexer.Position >= len(Lexer.Source):
        return None
    
    Char = Lexer.Source[Lexer.Position]
    Lexer.Position += 1
    
    if Char == "\n":
        Lexer.Line += 1
        Lexer.Column = 1
    else:
        Lexer.Column += 1
    
    return Char

def Peek(Lexer: Scanner) -> str:
    if Lexer.Position >= len(Lexer.Source):
        return None

    return Lexer.Source[Lexer.Position]

def PeekNext(Lexer: Scanner) -> str:
    if Lexer.Position + 1 >= len(Lexer.Source):
        return None
    
    return Lexer.Source[Lexer.Position + 1]

def Match(Lexer: Scanner, Expected: str) -> bool:
    if Lexer.Position >= len(Lexer.Source):
        return False
    
    if Lexer.Source[Lexer.Position] == Expected:
        Consume(Lexer)
        return True
    return False

# extra helpers

def PassSpaces(Lexer: Scanner) -> None:
    Char = Peek(Lexer)
    while Char != None and Char.isspace():
        Consume(Lexer)
        Char = Peek(Lexer)

def NextToken(Lexer: Scanner):
    PassSpaces(Lexer)

    Char = Peek(Lexer)

    if Char is None:
        return NewToken(TokenType.TOKEN_EOF, Lexer.Line, Lexer.Column, Lexer.Position, "EOF")

    # fallback (important so scanner always advances)
    Consume(Lexer)
    return NewToken(TokenType.TOKEN_ERROR, Lexer.Line, Lexer.Column, Lexer.Position, Char)

# (core) lexical scanner

def NewScanner(Source: str,
               Line: int,
               Column: int,
               Position: int) -> Scanner:
    Lexer = Scanner(Source, Line, Column, Position)
    return Lexer

def Scan(Lexer: Scanner) -> List[Token]:
    Tokens = []

    while True:
        Tok = NextToken(Lexer)
        Tokens.append(Tok)

        if Tok.TokType == TokenType.TOKEN_EOF:
            break

    return Tokens