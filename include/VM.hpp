#ifndef __VM_H__
#define __VM_H__
#include <vector>
#include <stack>
#include "Lexer.hpp"
#include "Global.hpp"
#include "IOperand.interface.hpp"
#include "Factory.class.hpp"

class VM{
private:
    std::string                     _buffer;
    Lexer                           _lexecal;
    std::vector<Token>              _Tokens;
    std::stack<const IOperand *>    _stack;
    OperandFactory                  _Factory;
    /*----------------------------------------------------------------------------*/
    void    Push(Token &token);
    void    Assert(Token &token);
    void    Pop(Token &token);
    void    Dump() const;
    void    Print(Token &token) const;
    void    Add(Token &token);
    void    Sub(Token &token);
    void    Mul(Token &token);
    void    Div(Token &token);
    void    Mod(Token &token);


public:
    VM ();
    VM (const VM &a);
    VM & operator = (const VM &a);
    ~VM ();

    /*----------------------------------------------------------------------------*/
    void    readFile(const std::string& filePath);
    void    runLexecal();
    void    execute();
    
};

#endif