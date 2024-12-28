#include "../include/Parser.hpp"

/*----------------------------------------------------------------------------*/
Parser::Parser () {}

/*----------------------------------------------------------------------------*/
Parser::Parser (const Parser &a){
    *this = a;
}

/*----------------------------------------------------------------------------*/
Parser & Parser::operator = (const Parser &a){
    if (this != &a){
        std::cout << "Parser: Copy assignment operator called!" << std::endl;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
Parser::~Parser () {}

