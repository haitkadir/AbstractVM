#include <iostream>
#include <fstream>
#include <sstream>
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
std::string VM::readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::string error = "Could not open the file: " + filePath;
        throw VMException(error.c_str());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}