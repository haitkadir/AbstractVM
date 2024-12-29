#include "../include/Factory.class.hpp"
#include <iostream>
#include <fcntl.h>


void memecheck(){
    system("leaks a.out");
}

int main() {
    // atexit(memcheck);
    try{
        OperandFactory typeFactory;

        IOperand const* op1 = typeFactory.createOperand(Int16, "100"); // should throw overflow exception
        IOperand const* op2 = typeFactory.createOperand(Int8, "100");

        std::cout << "op1: " << op1->toString() << "\n";
        std::cout << "op2: " << op2->toString() << "\n";

        IOperand const* result = *op1 + *op2;

        std::cout << "Result: " << result->toString() << "\n";
        std::cout << "Result Precision: " << result->getPrecision() << "\n";
        delete op1;
        delete op2;
        delete result;
    } catch (const std::exception &e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}