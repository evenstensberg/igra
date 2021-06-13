#include <iostream>
#include <fstream>


using namespace std;

class Configuration {
    public: 

    string entry;
};

static void log(string msg) {
    cout << msg << endl;
}

int main(int argc, char **argv) {
    Configuration config;
    config.entry = argv[1];
    log(config.entry);
    string entryContent;
    ifstream entryFile (config.entry);
    if(entryFile.is_open()) {
        while(getline(entryFile, entryContent)) {}
             cout << entryContent << "HEY" << endl;
    }
    return 0;
}