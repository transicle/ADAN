from enum import Enum

# in C/C++ we're able to just do 
"""
typedef enum {
    TOKEN_<TOKEN-TYPE>
} TokenType;
"""

class TokenType(Enum):
    # SPECIAL TOKENS
    TOKEN_EOF = 1
    TOKEN_ERROR = 2

class Token():
    # Position = current char in file
    def __init__(self, 
                 TokType: TokenType,
                 Line: int, 
                 Column: int, 
                 Position: int,
                 Lexeme: str):
        self.TokType = TokType
        self.Line = Line
        self.Column = Column
        self.Position = Position
        self.Lexeme = Lexeme

def NewToken(TokType: TokenType,
             Line: int, 
             Column: int, 
             Position: int,
             Lexeme: str) -> Token:
    Tok = Token(TokType, Line, Column, Position, Lexeme)
    return Tok