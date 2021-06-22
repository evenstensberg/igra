#include "lexer.h"
#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#define DEBUG 1

map<char, string> OpTable = {
    {'+', "PLUS"},
    {'-', "MINUS"},
    {'*', "MULTIPLY"},
    {'.', "PERIOD"},
    {'\\', "BACKSLASH"},
    {':', "COLON"},
    {'%', "PERCENT"},
    {'|', "PIPE"},
    {'!', "EXCLAMATION"},
    {'?', "QUESTION"},
    {'#', "POUND"},
    {'&', "AMPERSAND"},
    {';', "SEMI"},
    {',', "COMMA"},
    {'(', "L_PAREN"},
    {')', "R_PAREN"},
    {'<', "L_ANG"},
    {'>', "R_ANG"},
    {'{', "L_BRACE"},
    {'}', "R_BRACE"},
    {'[', "L_BRACKET"},
    {']', "R_BRACKET"},
    {'=', "EQUALS"}};

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
  Token process_number(char buff[]);
  Token process_identifier(char buff[]);
  Token proccess_quote(char buff[]);
  bool is_digit(char c);
  bool isalphanum(char c);
};

void Lexer::skip_tokens(char buff[])
{
  while (pos < buff_len)
  {
    char char_at_pos = buff[pos];
    if (char_at_pos == ' ' || char_at_pos == '\t' || char_at_pos == '\r' || char_at_pos == '\n')
    {
      pos++;
    }
    else
    {
      break;
    }
  }
};

Token Lexer::proccess_quote(char buff[])
{
  string token_string;
  int buff_size = sizeof(buff) / sizeof(char);
  for (int i = 0; i < buff_size; i++)
  {
    token_string = token_string + buff[i];
  }
  string::size_type loc = token_string.find('"', pos + 1);
  if (loc == -1)
  {
    fprintf(stderr, "Error at %d", pos);
  }
  else
  {
    Token token;
    token.name = "QUOTE";
    token.value = token_string.substr(pos, loc + 1);
    token.pos = loc + 1;
    pos = loc + 1;
    return token;
  }
}
bool Lexer::isalphanum(char c)
{
  return (c >= 'a' && c <= 'z') ||
             (c >= 'A' && c <= 'Z') ||
             (c >= '0' && c <= '9') ||
             (c == '_' || c == '$');
}
Token Lexer::process_identifier(char buff[])
{
  int end_pos = pos + 1;
  while (end_pos < buff_len && Lexer::isalphanum(buff[end_pos]))
  {
    end_pos++;
  }
}

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

bool Lexer::is_digit(char c)
{
  return int(c) >= 0 && int(c) <= 9;
}

Token Lexer::process_number(char buff[])
{
  int end_pos = pos + 1;
  while (end_pos < buff_len && Lexer::is_digit(buff[end_pos]))
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
  token.name = "NUMBER";
  token.value = token_string.substr(pos, end_pos);
  token.pos = pos;
  pos = end_pos;
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
  else
  {
    map<char, string>::iterator it;
    it = OpTable.find(cursorChar);
    // Undefined operator
    if (it == OpTable.end())
    {
      if (Lexer::isalphanum(cursorChar))
      {
        return Lexer::process_identifier(buff);
      }
      else if (Lexer::is_digit(cursorChar))
      {
        return Lexer::process_number(buff);
      }
      else if (cursorChar == '"')
      {
        return Lexer::proccess_quote(buff);
      }
      else
      {
        fprintf(stderr, "Error at %d", pos);
      }
    }
    else
    {
      Token token;
      token.name = string(it->second);
      token.value = cursorChar;
      token.pos = pos++;
    }
  }
};

static void next() {}

void run_lexer(string source)
{
  Lexer lexer(source);
  int source_length = source.length();
  char source_array[source_length + 1];
  strcpy(source_array, source.c_str());
  lexer.token(source_array);
};