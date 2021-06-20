#include "lexer.h"
#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#define DEBUG 1

using namespace std;

struct Token
{
  int pos = 0;
  string value;
  string name;
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
};

void Lexer::skip_tokens(char buff[])
{
  while(pos < buff_len) {
    char char_at_pos = buff[pos];
    if(char_at_pos == ' ' || char_at_pos == '\t' || char_at_pos == '\r' || char_at_pos == '\n') {
      pos++;
    } else {
      break;
    }
  }
};

bool Lexer::is_new_line(char c)
{
  return (c == '\r' || c == '\n') ? true : false;
};

Token Lexer::parse_comment(char buff[])
{
  int end_pos = pos + 2;
  char charAtPos = buff[pos + 2];
  // walk to end of line
  while (end_pos < buff_len && !(Lexer::is_new_line(buff[end_pos])))
  {
    end_pos++;
  }
  // copy char array to string
  string token_string;
  int buff_size = sizeof(buff) / sizeof(char);
  for (int i = 0; i < buff_size; i++)
  {
    token_string = token_string + buff[i];
  }

  Token token;
  token.name = "COMMENT";
  token.value = token_string.substr(pos, end_pos);
  token.pos = pos;
  pos = end_pos + 1;
  return token;
};

Token Lexer::token(char buff[])
{
  Lexer::skip_tokens(buff);
  // cursor at EOF
  if (pos >= buff_len)
  {
    Token token;
    return token;
  }
  char cursorChar = buff[pos];
  if (cursorChar == '/')
  {
    char nextCharFromPos = buff[pos + 1];
    if (nextCharFromPos == '/')
    {
      return Lexer::parse_comment(buff);
    }
    else
    {
      // divide token
      Token token;
      token.name = "DIVIDE";
      token.value = '/';
      token.pos = pos++;
      return token;
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

static void next() {}

void run_lexer(string source)
{
  Lexer lexer(source);
  int source_length = source.length();
  char source_array[source_length + 1];
  strcpy(source_array, source.c_str());
  lexer.token(source_array);
};