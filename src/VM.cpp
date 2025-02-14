#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "../include/VM.hpp"
#include "../include/Exceptions.hpp"
#include <iomanip>

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
VM::~VM () {
    while (!this->_stack.empty()) {
        const IOperand *operand = this->_stack.top();
        delete operand;
        this->_stack.pop();
    }
}


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
    file.close();
    this->_buffer =  buffer.str();
}

/*----------------------------------------------------------------------------*/
void VM::readStdin() {
    std::string line;
    std::string result;

    std::regex endOfProgram(R"(^;;$)");
    while(std::getline(std::cin, line)){
        if (std::regex_match(line, endOfProgram)){
            break;
        }else{
            result += (line + "\n");
        }
    }

    this->_buffer =  result;
}


/*----------------------------------------------------------------------------*/
void    VM::runLexecal(){
    this->_lexer.tokenize(this->_buffer);
}


/*----------------------------------------------------------------------------*/
void    VM::printTokens() const{
    this->_lexer.printTokens();
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
                || std::stod(this->_stack.top()->toString()) != std::stod(newOperand->toString()))){
            delete newOperand;
            throw   AssertException("");
        }
        delete newOperand;
    } catch (const OverfflowException&){
        std::string error = "Error: Out of range on line: " + std::to_string(token.line);
        throw OverfflowException(error.c_str());
    }catch (const AssertException&){
        std::string error = "Error: ASSERT instruction not true on line: " + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}


/*----------------------------------------------------------------------------*/
void    VM::Dump() const {
    std::stack<const IOperand *>    temp = this->_stack;
    while(!temp.empty()){
        if (temp.top()->getPrecision() == Double){
            std::cout << std::fixed << std::setprecision(15);
            std::cout << temp.top()->toString() << std::endl;
        } else if(temp.top()->getPrecision() == Float){
            std::cout << std::fixed << std::setprecision(7);
            std::cout << temp.top()->toString() << std::endl;
        } else {
            std::cout << temp.top()->toString() << std::endl;
        }
        temp.pop();
    }
}


/*----------------------------------------------------------------------------*/
void    VM::Pop(Token &token){
    if(this->_stack.size()){
        const IOperand *to_del = this->_stack.top();
        this->_stack.pop();
        delete to_del;
    }else{
        std::string error = "Error: POP instruction on an empty stack on line: " + std::to_string(token.line);
        throw   PopOnEmptyException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Print(Token &token) const {
    if (!this->_stack.size() || this->_stack.top()->getPrecision() != Int8){
        std::string error = "Error: ASSERT instruction not true on line: " + std::to_string(token.line);
        throw   AssertException(error.c_str());
    }else{
        int value = std::stoi(this->_stack.top()->toString());
        std::cout << static_cast<char>(value) << std::endl;
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Add(Token &token){
    try{
        if (this->_stack.size() < 2){
            throw   AssertException("");
        }else{
            const IOperand *v1 = this->_stack.top();
            this->_stack.pop();
            const IOperand *v2 = this->_stack.top();
            this->_stack.pop();
            try{
                const IOperand *resultOp = *v2 + *v1;
                this->_stack.push(resultOp);
                delete v1;
                delete v2;
            }catch(OverfflowException&){
                delete v1;
                delete v2;
                std::string error = "Error: Out of range on line: " + std::to_string(token.line);
                throw OverfflowException(error.c_str());
            }
        }
    }catch (const AssertException&){
        std::string error \
        = "Error: stack is less than two values when an arithmetic instruction executed on line: " \
        + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Sub(Token &token){
    try{
        if (this->_stack.size() < 2){
            throw   AssertException("");
        }else{
            const IOperand *v1 = this->_stack.top();
            this->_stack.pop();
            const IOperand *v2 = this->_stack.top();
            this->_stack.pop();
            try{
                const IOperand *resultOp = *v2 - *v1;
                this->_stack.push(resultOp);
                delete v1;
                delete v2;
            }catch(OverfflowException&){
                delete v1;
                delete v2;
                std::string error = "Error: Out of range on line: " + std::to_string(token.line);
                throw OverfflowException(error.c_str());
            }
        }
    }catch (const AssertException&){
        std::string error \
        = "Error: stack is less than two values when an arithmetic instruction executed on line: " \
        + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Mul(Token &token){
    try{
        if (this->_stack.size() < 2){
            throw   AssertException("");
        }else{
            const IOperand *v1 = this->_stack.top();
            this->_stack.pop();
            const IOperand *v2 = this->_stack.top();
            this->_stack.pop();
            try{
                const IOperand *resultOp = *v2 * *v1;
                this->_stack.push(resultOp);
                delete v1;
                delete v2;
            }catch(OverfflowException&){
                delete v1;
                delete v2;
                std::string error = "Error: Out of range on line: " + std::to_string(token.line);
                throw OverfflowException(error.c_str());
            }
        }
    }catch (const AssertException&){
        std::string error \
        = "Error: stack is less than two values when an arithmetic instruction executed on line: " \
        + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Div(Token &token){
    try{
        if (this->_stack.size() < 2){
            throw   AssertException("");
        }else{
            const IOperand *v1 = this->_stack.top();
            this->_stack.pop();
            const IOperand *v2 = this->_stack.top();
            this->_stack.pop();
            try{
                const IOperand *resultOp = *v2 / *v1;
                this->_stack.push(resultOp);
                delete v1;
                delete v2;
            }catch(DiviModuByZeroException&){
                delete v1;
                delete v2;
                std::string error = "Error: Divission by Zero on line: " + std::to_string(token.line);
                throw DiviModuByZeroException(error.c_str());
            }
        }
    }catch (const AssertException&){
        std::string error \
        = "Error: stack is less than two values when an arithmetic instruction executed on line: " \
        + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Mod(Token &token){
    try{
        if (this->_stack.size() < 2){
            throw   AssertException("");
        }else{
            const IOperand *v1 = this->_stack.top();
            this->_stack.pop();
            const IOperand *v2 = this->_stack.top();
            this->_stack.pop();
            try{
                const IOperand *resultOp = *v2 % *v1;
                this->_stack.push(resultOp);
                delete v1;
                delete v2;
            }catch(DiviModuByZeroException&){
                delete v1;
                delete v2;
                std::string error = "Error: Modulo by Zero on line: " + std::to_string(token.line);
                throw DiviModuByZeroException(error.c_str());
            }
        }
    }catch (const AssertException&){
        std::string error \
        = "Error: stack is less than two values when an arithmetic instruction executed on line: " \
        + std::to_string(token.line);
        throw AssertException(error.c_str());
    }
}

/*----------------------------------------------------------------------------*/
void    VM::Exit(){
    throw   ExitException("Exited");
}

/*----------------------------------------------------------------------------*/
void    VM::execute(){
    for(auto &token: this->_lexer.getTokens()){

        switch(token.type){
            case PUSHINT8 ... PUSHDOUBLE: this->Push(token); break;
            case ASSERTINT8 ... ASSERTDOUBLE: this->Assert(token); break;
            case POP: this->Pop(token); break;
            case DUMP: this->Dump(); break;
            case ADD: this->Add(token); break;
            case SUB: this->Sub(token); break;
            case MUL: this->Mul(token); break;
            case DIV: this->Div(token); break;
            case MOD: this->Mod(token); break;
            case PRINT: this->Print(token); break;
            case EXIT: this->Exit(); break;
            default:
                break;
        }
        if ((&token == &this->_lexer.getTokens().back()) && token.type != EXIT) {
            throw VMException("Error: expected Exit instruction got nothing");
        }
    }
}