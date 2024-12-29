#include <iostream>
#include <limits>
#include <cmath>
#include <string>

enum eOperandType {
    Int8, Int16, Int32, Float, Double
};

bool    isoverfflow(eOperandType type, long value){
    switch (type)
    {
        case Int8: return (value < std::numeric_limits<int8_t>::min() || value > std::numeric_limits<int8_t>::max()) ? true: false;
        case Int16: return (value < std::numeric_limits<int16_t>::min() || value > std::numeric_limits<int16_t>::max()) ? true: false;
        case Int32: return (value < std::numeric_limits<int32_t>::min() || value > std::numeric_limits<int32_t>::max()) ? true: false;
        default:
            return false;
    }
}

int main(){


    std::cout << "int min: " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "int max: " << std::numeric_limits<int>::max() << std::endl;

    std::cout << isoverfflow(Int8, -2147483649) << std::endl;

    // eOperandType resultType = static_cast<eOperandType>(std::max(0, 1));
    // std::cout << resultType << std::endl;

}