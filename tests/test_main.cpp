#include "../include/Factory.class.hpp"
#include <iostream>

int main() {
    OperandFactory& factory = OperandFactory::getInstance();

    IOperand const* op1 = factory.createOperand(Int32, "42");
    IOperand const* op2 = factory.createOperand(Float, "3.14");

    IOperand const* result = *op1 + *op2;

    std::cout << "Result: " << result->toString() << "\n";

    delete op1;
    delete op2;
    delete result;

    return 0;
}
