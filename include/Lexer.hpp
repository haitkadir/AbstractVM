#ifndef __LEXER_H__
#define __LEXER_H__

#include <regex>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>

enum TokenType { PUSHINT8, PUSHINT16, PUSHINT32, PUSHINT, PUSHFLOAT, PUSHDOUBLE, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, COMMENT, SEP, INVALID };
struct Token {
    TokenType type;
    std::string value;
    size_t line;
};
class Lexer {
public:
    

    Lexer() : _input(""), _line(1) {}
    // Lexer(const std::string& input) : _input(input), _line(1) {}

    std::vector<Token> tokenize(const std::string& input) {
        this->_input = input;
        std::istringstream streamfile(input);
        std::string line;
        std::vector<Token> tokens;

        while (std::getline(streamfile, line)) {

            std::cout << "before{" << line << "}" << std::endl;
            if (std::regex_match(line, std::regex(R"(^\s+$)")) || std::regex_match(line, std::regex(R"(^;.*$)"))){
                std::cout << "spaces catched" << std::endl;
                ++_line;
                continue;
            }
            std::cout << "after{" << line << "}" << std::endl;
            Token token;
            Token temp;
            temp = identifyToken(line);
            token.value = line;
            token.type = temp.type;
            token.value = temp.value;
            std::cout << "toketype: " << token.type << std::endl;
            std::cout << "tokeValue: " << token.value << std::endl;
            token.line = _line;

            if (token.type == INVALID) {
                throw std::runtime_error("Lexical error on line " + std::to_string(_line));
            }
            tokens.push_back(token);
            ++_line;
        }
        return tokens;
    }

private:
    std::string _input;
    size_t _line;

    Token identifyToken(const std::string& value) {
        Token token;
        std::smatch match;
        if (std::regex_match(value, match, std::regex(R"(^push\s+int8\((\d+)\)$)"))){
            token.type = PUSHINT8;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^push\s+int16\((\d+)\)$)"))){
            token.type = PUSHINT16;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^push\s+int32\((\d+)\)$)"))){
            token.type = PUSHINT32;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^push\s+int\((\d+)\)$)"))){
            token.type = PUSHINT;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^push\s+float\((\d+\.\d+)\)$)"))){
            token.type = PUSHFLOAT;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^push\s+double\((\d+\.\d+)\)$)"))){
            token.type = PUSHDOUBLE;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+int8\((\d+)\)$)"))){
            token.type = ASSERTINT8;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+int16\((\d+)\)$)"))){
            token.type = ASSERTINT16;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+int32\((\d+)\)$)"))){
            token.type = ASSERTINT32;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+int\((\d+)\)$)"))){
            token.type = ASSERTINT;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+float\((\d+\.\d+)\)$)"))){
            token.type = ASSERTFLOAT;
            token.value = match[1];
            return token;
        }
        if (std::regex_match(value, match, std::regex(R"(^assert\s+double\((\d+\.\d+)\)$)"))){
            token.type = ASSERTDOUBLE;
            token.value = match[1];
            return token;
        }

        token.type = INVALID;
        return token;
    }
};


#endif

