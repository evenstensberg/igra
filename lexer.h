
#ifndef IGRA_LEXER_H
#define IGRA_LEXER_H

#include "igra.h"
#include <map>

using namespace std;

class OpTable {
public:
  typedef map<string, string> OpMap;
  static OpMap opMap_;
};

void run_lexer(string source);


#endif