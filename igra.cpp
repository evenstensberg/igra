#include <iostream>
#include <fstream>
#include <numeric>

#include "igra.h"
#include "parser.h"
#include "lexer.h"

#define DEBUG 1

using namespace std;

class Configuration {
    public: 
    string entry_content;
    string entry_path;
};


enum Token {

    TOKEN_EOF = -1,
    ILLEGAL,
    IDENT,
    INT,
    SEMI,
    ADD,
    SUB,
    MUL,
    DIV,
    ASSIGN
};


void debug_log(string msg) {
    if(DEBUG) {
        cout << msg << endl;
    }
    return;
}

int main(int argc, char **argv) {
    Configuration config;
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments to igra");
        return -1;
    }
    config.entry_path = argv[1];
    ifstream entryFile (config.entry_path);
    if(entryFile.is_open()) {
        while(getline(entryFile, config.entry_content)) {}

    }
    debug_log(config.entry_content);
    noop_parser();
    noop_lexer();
    return 0;
}