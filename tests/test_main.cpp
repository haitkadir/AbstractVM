#include "../include/Factory.class.hpp"
#include <iostream>
#include <cstdlib>


void memecheck(){
    system("leaks a.out");
}

int main() {
    std::atexit(memecheck);
    try{
        OperandFactory typeFactory;

        IOperand const* op1 = typeFactory.createOperand(Float, "1.3"); // should throw overflow exception
        IOperand const* op2 = typeFactory.createOperand(Int8, "1");

        std::cout << "op1   : " << op1->toString() << "\n";
        std::cout << "op2: " << op2->toString() << "\n";

        IOperand const* result = *op1 % *op2;

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