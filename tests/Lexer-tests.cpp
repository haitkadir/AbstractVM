#include <iostream>
#include "../include/Lexer.hpp"
#include <fstream>

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read file buffer into stringstream
    return buffer.str(); // Convert stringstream to string
}

 
int main()
{
    try{
        Lexer lexer;
        std::string filePath = "../programs/exemple.avm";

        std::string content = readFileToString(filePath);
        std::vector<Token> tokens = lexer.tokenize(content);
        std::cout << "===================================================================================================" << std::endl;;
        for (auto token : tokens){
            std::cout << "{" << std::endl;
            std::cout << "  type : " << token.type << std::endl;
            std::cout << "  value:(" << token.value << ")" << std::endl;
            std::cout << "  type : " << token.line << std::endl;
            std::cout << "}" << std::endl;
        }
    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return(0);
}


