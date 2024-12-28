#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <vector>
#include <regex>
#include <stdexcept>


class Lexer{
private:
    std::string input_;
    size_t current_line_ = 1;
    
    static TokenType identifyToken(const std::string &str);
    static bool isValue(const std::string &str);
public:
    Lexer ();
    Lexer (const Lexer &a);
    Lexer & operator = (const Lexer &a);
    ~Lexer ();

    enum TokenType {
        PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, VALUE, COMMENT, SEP, INVALID
    };

    struct Token {
        TokenType type;
        std::string value;
        size_t line;
    };

    explicit Lexer(const std::string &input);
    std::vector<Token> tokenize();
};

#endif

