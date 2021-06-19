#include "lexer.h"
#include <iostream>
#include <map>

#define DEBUG 1

using namespace std;

class Lexer {
  public:
    int pos = 0;
    void *buff;
    int buff_len = 0;
    Lexer(string buffer) {
      buff_len = buffer.length();
    }
};

OpTable::OpMap OpTable::opMap_ = {
  {"+", "PLUS"},
  {"-", "MINUS"},
  {"*", "MULTIPLY"},
  {".", "PERIOD"},
  {"\\", "BACKSLASH"},
  {":", "COLON"},
  {"%", "PERCENT"},
  {"|", "PIPE"},
  {"!", "EXCLAMATION"},
  {"?", "QUESTION"},
  {"#", "POUND"},
  {"&", "AMPERSAND"},
  {";", "SEMI"},
  {",", "COMMA"},
  {"(", "L_PAREN"},
  {")", "R_PAREN"},
  {"<", "L_ANG"},
  {">", "R_ANG"},
  {"{", "L_BRACE"},
  {"}", "R_BRACE"},
  {"[", "L_BRACKET"},
  {"]", "R_BRACKET"},
  {"=", "EQUALS"}
};

enum Token {

  Num = 128,
  Fun,
  Sys,
  Glo,
  Loc,
  Id,
  Char,
  Else,
  Enum,
  If,
  Int,
  Return,
  Sizeof,
  While,
  Assign,
  Cond,
  Lor,
  Lan,
  Or,
  Xor,
  And,
  Eq,
  Ne,
  Lt,
  Gt,
  Le,
  Ge,
  Shl,
  Shr,
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Inc,
  Dec,
  Brak
};

static void next() {}

void run_lexer(string source) { 
  debug_log(source);
  Lexer lexer(source);
  
};