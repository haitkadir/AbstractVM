#include <iostream>
#include "../include/VM.hpp"

int main(int ac, char **av) {

    try{
        VM  avm;
        if (ac < 2){
            std::cout << "Reading from stdin not handled yet" << std::endl;
            // avm.readStdin();
            // avm.runLexecal();
            // avm.execute();
        }else if (ac == 2){
            avm.readFile(av[1]);
            avm.runLexecal();
            avm.execute();
        } else{
            std::cout << "Bad arguments:\n./avm path/to/example.avm" << std::endl;
        }
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
