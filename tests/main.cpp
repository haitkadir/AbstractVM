#include <iostream> 
#include <stack> 
#include <string>
using namespace std; 
  
int main() 
{ 
    std::string str = "0.0000000001";
    if (static_cast<float>(std::stod(str)) == 0){
        std::cout << "zero" << std::endl;
    }else{
        std::cout << "not zero" << std::endl;

    }


} 