#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "../include/VM.hpp"
#include "../include/Exceptions.hpp"

/*----------------------------------------------------------------------------*/
VM::VM () {}

/*----------------------------------------------------------------------------*/
VM::VM (const VM &a){
    *this = a;
}

/*----------------------------------------------------------------------------*/
VM & VM::operator = (const VM &a){
    if (this != &a){
        std::cout << "VM: Copy assignment operator called!" << std::endl;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
VM::~VM () {}


/*----------------------------------------------------------------------------*/
void VM::readFile(const std::string& filePath) {
    if(!std::regex_match(filePath, std::regex(R"(^(.*/)?[^/]+\.avm$)"))){
        std::string error = "file type not valid: " + filePath + "\nexampel: path/to/program.avm";
        throw VMException(error.c_str());
    }
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::string error = "Could not open the file: " + filePath;
        throw VMException(error.c_str());
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    this->_buffer =  buffer.str();
}


/*----------------------------------------------------------------------------*/
void    VM::runLexecal(){
    this->_Tokens = this->_lexecal.tokenize(this->_buffer);
}


/*----------------------------------------------------------------------------*/
void    VM::Push(Token &token){
    try{
		IOperand const *newOperand = _Factory.createOperand(static_cast<eOperandType>(token.type), token.value);
        this->_stack.push(newOperand);
    } catch (const OverfflowException&){
        std::string error = "Out of range on line: " + std::to_string(token.line);
        throw OverfflowException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Assert(Token &token){
    try{
		IOperand const *newOperand = _Factory.createOperand(static_cast<eOperandType>(token.type - 5), token.value);

        if (!this->_stack.size() 
            || (this->_stack.top()->getPrecision() != newOperand->getPrecision() 
                || this->_stack.top()->toString() != newOperand->toString())){
            throw   AssertException("");
        }
    } catch (const OverfflowException&){
        std::string error = "Out of range on line: " + std::to_string(token.line);
        throw OverfflowException(error.c_str());
    }catch (const AssertException&){
        std::string error = "ASSERT instruction not true";
        throw AssertException(error.c_str());
    }
}


/*----------------------------------------------------------------------------*/
void    VM::Dump() const {
    std::stack<const IOperand *>    temp = this->_stack;
    while(!temp.empty()){
        std::cout << temp.top()->toString() << std::endl;
        temp.pop();
    }
}

/*----------------------------------------------------------------------------*/
void    VM::execute(){
    for(auto &token: this->_Tokens){
        if (token.type >= PUSHINT8 && token.type <= PUSHDOUBLE){
            this->Push(token);
        }
        if (token.type >= ASSERTINT8 && token.type <= ASSERTDOUBLE){
            this->Assert(token);
        }
        if(token.type == DUMP){
            this->Dump();
        }
    }

    // while(!this->_stack.empty()){
    //     std::cout << "stack item: " << this->_stack.top()->toString() << std::endl;
    //     std::cout << "stack item: " << this->_stack.top()->getType() << std::endl;
    //     this->_stack.pop();
    // }
}