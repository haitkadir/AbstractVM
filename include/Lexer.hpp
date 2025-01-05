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
    void                tokenize(const std::string& input);
    void                printTokens() const;
    std::vector<Token>  &getTokens();
private:
    std::string _input;
    size_t      _line;
    std::vector<Token>              _Tokens;

    Token identifyToken(const std::string& value);
    void trim(std::string &str, const char *to_trim);
};


#endif

