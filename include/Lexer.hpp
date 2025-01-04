#ifndef __LEXER_H__
#define __LEXER_H__

#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Global.hpp"

class Lexer {
public:
    Lexer();
    Lexer (const Lexer &a);
    Lexer & operator = (const Lexer &a);
    ~Lexer ();
    std::vector<Token> tokenize(const std::string& input);
private:
    std::string _input;
    size_t      _line;

    Token identifyToken(const std::string& value);
    void trim(std::string &str, const char *to_trim);
};


#endif

