#include <iostream>
#include "../include/VM.hpp"
#include "../include/Exceptions.hpp"


int main(int ac, char **av) {
    try{
        VM  avm;
        if (ac < 2){
            avm.readStdin();
            avm.runLexecal();
            // avm.printTokens();
            avm.execute();
        }else if (ac == 2){
            avm.readFile(av[1]);
            avm.runLexecal();
            // avm.printTokens();
            avm.execute();
        } else{
            std::cout << "Bad arguments:\n./avm path/to/example.avm" << std::endl;
            std::cout << "Or:\n./avm\nTo read from stdin" << std::endl;
        }
    } catch (ExitException &e){
        exit(0);
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
