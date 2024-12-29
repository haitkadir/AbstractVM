#include <iostream>

enum eOperandType {
    Int8, Int16, Int32, Float, Double
};



int main(){

    eOperandType resultType = static_cast<eOperandType>(std::max(0, 1));
    std::cout << resultType << std::endl;

}