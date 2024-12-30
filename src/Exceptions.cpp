#include "../include/Exceptions.hpp"

// ======================== Overfflow ===============================
OverfflowException::OverfflowException(const char* msg) : message(msg)
{
}

const char* OverfflowException::what() const noexcept
{
    return message.c_str();
}
// ======================== DiviModuByZero ===============================
DiviModuByZeroException::DiviModuByZeroException(const char* msg) : message(msg)
{
}

const char* DiviModuByZeroException::what() const noexcept
{
    return message.c_str();
}