#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string read_file(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filepath);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}