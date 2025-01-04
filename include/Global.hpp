#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <string>

enum TokenType { 
    PUSHINT8,
    PUSHINT16,
    PUSHINT32,
    PUSHFLOAT,
    PUSHDOUBLE,
    ASSERTINT8,
    ASSERTINT16,
    ASSERTINT32,
    ASSERTFLOAT,
    ASSERTDOUBLE,
    POP,
    DUMP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    EXIT,
    INVALID
};

struct Token {
    TokenType type;
    std::string value;
    size_t line;
};


#endif