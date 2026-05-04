from frontend.scanner.scanner import Scanner, Scan

TARGET_FILE = "samples/preview.adn"

if __name__ == "__main__":
    Source = ""
    with open(TARGET_FILE, "r") as File:
        Source = File.read()

    Lexer = Scanner(Source, 1, 1, 1)
    Stream = Scan(Lexer)

    for Tok in Stream:
        print(f"Lexeme: {Tok.Lexeme} | Line, Column: {Tok.Line}, {Tok.Column}")