#include <iostream>
#include <fstream>
#include <numeric>

#include "igra.h"
#include "parser.h"
#include "lexer.h"

#define DEBUG 1

using namespace std;

// Entry point of the application 
class EntryPoint {
    public: 
    string entry_content;
    string entry_path;
};


void debug_log(string msg) {
    if(DEBUG) {
        cout << msg << endl;
    }
    return;
}

int main(int argc, char **argv) {
    EntryPoint entry_point;
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments to igra");
        return -1;
    }
    entry_point.entry_path = argv[1];
    ifstream entryFile (entry_point.entry_path);
    if(entryFile.is_open()) {
        while(getline(entryFile, entry_point.entry_content)) {}

    }
    run_lexer(entry_point.entry_content);
/*     noop_parser(); */
    return 0;
}