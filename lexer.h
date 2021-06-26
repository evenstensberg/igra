
#ifndef IGRA_LEXER_H
#define IGRA_LEXER_H

#include "igra.h"
#include <map>

using namespace std;

struct Token
{
  int pos = 0;
  string value;
  string name;
};

class OpTable {
public:
  typedef map<string, string> OpMap;
  static OpMap opMap_;
};



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
  void skip_tokens(char buff[]);
  Token token(char buff[]);
  Token parse_comment(char buff[]);
  bool is_new_line(char c);
  Token process_number(char buff[]);
  Token process_identifier(char buff[]);
  Token proccess_quote(char buff[]);
  bool is_digit(char c);
  bool isalphanum(char c);
};

Lexer run_lexer(string source);


#endif