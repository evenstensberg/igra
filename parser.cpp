#include <iostream>
#include <fstream>
#include <cstring>
#include "lexer.h"
#include "parser.h"

class Interpreter {
    public:
        Token curr_token;
        string text;
        int pos;
        string expr();
        string validate(string text);
        Token get_next_token();
};

string Interpreter::expr() {

};

string Interpreter::validate(string txt) {
    text = txt;
};

Token Interpreter::get_next_token() {
    string txt = text;
    if(pos > txt.length() -1) {
        Token token;
        token.value = EOF;
        token.name = "EOF";
        token.pos = pos;
        return token;
    }
};

void noop_parser(string text) {
    Interpreter interpret;
    interpret.validate(text);
};