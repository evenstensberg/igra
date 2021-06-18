#include <iostream>
#include <fstream>
#include <numeric>

#include "igra.h"

#define DEBUG 1

using namespace std;

class Configuration {
    public: 
    string entry_content;
    string entry_path;
};


enum Token {

    E_OF
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
    return 0;
}