// ##include "../include/Factory.class.hpp"
#include <iostream>

int modulue(int8_t a, int b){
    return a % b;
}

int main() {

    std::cout << "Result: " << modulue(2, 2777) << "\n";

    return 0;
}