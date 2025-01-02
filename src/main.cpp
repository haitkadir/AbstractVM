#include <iostream>

int main(int ac, char **av) {

    try{
        if (ac < 2){
            std::cout << "Reading from stdin not handled yet" << std::endl;
        }else if (ac == 2){
            std::cout << av[1] << std::endl;
        } else{
            std::cout << "Bad arguments:\n./avm path/to/example.avm" << std::endl;
        }
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
