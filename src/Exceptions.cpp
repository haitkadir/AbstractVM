#include "../include/Exceptions.hpp"

// ======================== Overfflow ===============================
OverfflowException::OverfflowException(const char* msg) : message(msg)
{
}

const char* OverfflowException::what() const throw()
{
    return message.c_str();
}