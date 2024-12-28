#ifndef __PARSER_H__
#define __PARSER_H__

#include "Lexer.hpp"
#include <stdexcept>

class Parser{
private:
    std::vector<Lexer::Token> tokens_;
    size_t current_index_ = 0;

    void validateInstruction(const Lexer::Token &token);
    void validateValue(const std::string &value);
public:
    Parser ();
    Parser (const Parser &a);
    Parser & operator = (const Parser &a);
    ~Parser ();

    explicit Parser(const std::vector<Lexer::Token> &tokens);
    void parse();
};

#endif

