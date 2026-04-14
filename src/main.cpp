#include <iostream>
#include <filesystem>
#include "fs.hpp"
#include "scanner/scanner.hpp"

using namespace std;
using namespace filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <source_file>" << endl;
        return 1;
    }

    string source_file = argv[1];
    if (!exists(source_file)) {
        cerr << "Error: File '" << source_file << "' does not exist." << endl;
        return 1;
    }

    string source_code;
    try {
        source_code = read_file(source_file);
    } catch (const exception& e) {
        cerr << "Error reading file: " << e.what() << endl;
        return 1;
    }

    Scanner* scanner = create_scanner(source_code);
    scan(scanner);

    // Freeing allocated resources //

    free_scanner(scanner);
    
    return 0;
}