#ifndef SCANNER
#define SCANNER

#include <string>
#include <vector>
#include "../../tokens/tokens.hpp"

using namespace std;

typedef struct {
    string source;
    vector<Token*> tokens;
    int line;
    int column;
    int position;
    bool has_error;
} Scanner;

Scanner* create_scanner(const string& source);

void free_scanner(Scanner* scanner);

void scan(Scanner* scanner);

#endif // SCANNER