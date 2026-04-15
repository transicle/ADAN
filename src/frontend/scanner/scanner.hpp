#ifndef SCANNER
#define SCANNER

#include <string>

using namespace std;

typedef struct {
    string source;
    int line;
    int column;
    int position;
} Scanner;

Scanner* create_scanner(const string& source);

void free_scanner(Scanner* scanner);

void scan(Scanner* scanner);

#endif // SCANNER