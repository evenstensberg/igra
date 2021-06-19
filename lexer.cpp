#include "lexer.h"
#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#define DEBUG 1

using namespace std;

class Lexer
{
public:
  int pos = 0;
  void *buff;
  int buff_len = 0;
  Lexer(string buffer)
  {
    buff_len = buffer.length();
  };
  void skip_tokens();
  int token(char *buff);
};

void Lexer::skip_tokens(){

};

int Lexer::token(char *buff)
{
  Lexer::skip_tokens();
  // cursor at EOF
  if (pos >= buff_len)
  {
    return 0;
  }
  char cursorChar = buff[pos];

  if(cursorChar == '/') {
    char nextCharFromPos = buff[pos + 1];
    if(nextCharFromPos == '/') {
      // comment
      return;
    } else {
      // divide token
      return;
    }
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
    {"=", "EQUALS"}};

enum Token
{

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

void run_lexer(string source)
{
  debug_log(source);
  Lexer lexer(source);
  int source_length = source.length();
  char source_array[source_length + 1];
  strcpy(source_array, source.c_str());
  lexer.token(source_array);
};