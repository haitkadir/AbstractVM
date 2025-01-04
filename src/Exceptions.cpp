#include "../include/Exceptions.hpp"

/*------------------------- For Overfflow ------------------------------*/
OverfflowException::OverfflowException(const char* msg) : message(msg)
{
}

const char* OverfflowException::what() const noexcept
{
    return message.c_str();
}

/*-------------------- For Division or Modulo by zero --------------------*/
DiviModuByZeroException::DiviModuByZeroException(const char* msg) : message(msg)
{
}

const char* DiviModuByZeroException::what() const noexcept
{
    return message.c_str();
}

/*---------------------------- Lexecal errors -----------------------------*/
LexecalException::LexecalException(const char* msg) : message(msg)
{
}

const char* LexecalException::what() const noexcept
{
    return message.c_str();
}

/*------------------------------ Execution errors ---------------------------------*/
VMException::VMException(const char* msg) : message(msg)
{
}

const char* VMException::what() const noexcept
{
    return message.c_str();
}

/*------------------------------ Execution errors ---------------------------------*/
AssertException::AssertException(const char* msg) : message(msg)
{
}

const char* AssertException::what() const noexcept
{
    return message.c_str();
}

/*------------------------------ Execution errors ---------------------------------*/
PopOnEmptyException::PopOnEmptyException(const char* msg) : message(msg)
{
}

const char* PopOnEmptyException::what() const noexcept
{
    return message.c_str();
}