#include <cfenv>
#include <cmath>
#include <iostream>
 
// #pragma STDC FENV_ACCESS ON
 
volatile double zero = 0.01; // volatile not needed where FENV_ACCESS is supported
volatile double one = 1.0;  // volatile not needed where FENV_ACCESS is supported
 
int main()
{
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout <<  "1.0/0.0 = " << 127.0 / zero << '\n';
    if (std::fetestexcept(FE_DIVBYZERO))
        std::cout << "division by zero reported\n";
    else
        std::cout << "division by zero not reported\n";
 
    // std::feclearexcept(FE_ALL_EXCEPT);
    // std::cout << "1.0/10 = " << one / 10 << '\n';
    // if (std::fetestexcept(FE_INEXACT))
    //     std::cout << "inexact result reported\n";
    // else
    //     std::cout << "inexact result not reported\n";
 
    // std::feclearexcept(FE_ALL_EXCEPT);
    // std::cout << "sqrt(-1) = " << std::sqrt(-1) << '\n';
    // if (std::fetestexcept(FE_INVALID))
    //     std::cout << "invalid result reported\n";
    // else
    //     std::cout << "invalid result not reported\n";
}

// #include <sstream>
// #include <iostream>
// #include <cmath>


// int main(){
//     double a = -1e308; // Close to the maximum for double
//     double b = -1e308;

//     double result = a * b;

//     // Check for overflow
//     if (std::isinf(result)) {
//         std::cout << "Overflow detected: result is " << result << std::endl;
//     } else {
//         std::cout << "Result is " << result << std::endl;
//     }
// }