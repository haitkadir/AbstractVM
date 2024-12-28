#include "../include/Lexer.hpp"

/*----------------------------------------------------------------------------*/
Lexer::Lexer () {}

/*----------------------------------------------------------------------------*/
Lexer::Lexer (const Lexer &a){
    *this = a;
}

/*----------------------------------------------------------------------------*/
Lexer & Lexer::operator = (const Lexer &a){
    if (this != &a){
        std::cout << "Lexer: Copy assignment operator called!" << std::endl;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
Lexer::~Lexer () {}

