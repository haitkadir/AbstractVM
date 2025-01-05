#include "../include/Exceptions.hpp"

/*------------------------- For Overfflow ------------------------------*/




OverfflowException::OverfflowException(const char* msg) : message(msg){}

const char* OverfflowException::what() const noexcept
{
    return message.c_str();
}

// canonical form
OverfflowException::OverfflowException():message("overfflow exception"){}

OverfflowException::OverfflowException(const OverfflowException &other){
    this->message = other.message;
}

OverfflowException& OverfflowException::operator=(const OverfflowException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

OverfflowException::~OverfflowException() noexcept =  default;


/*-------------------- For Division or Modulo by zero --------------------*/
DiviModuByZeroException::DiviModuByZeroException(const char* msg) : message(msg)
{
}

const char* DiviModuByZeroException::what() const noexcept
{
    return message.c_str();
}
// canonical form
DiviModuByZeroException::DiviModuByZeroException():message("Div/Mod by zero exception"){}

DiviModuByZeroException::DiviModuByZeroException(const DiviModuByZeroException &other){
    this->message = other.message;
}

DiviModuByZeroException& DiviModuByZeroException::operator=(const DiviModuByZeroException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

DiviModuByZeroException::~DiviModuByZeroException() noexcept =  default;

/*---------------------------- Lexecal errors -----------------------------*/
LexecalException::LexecalException(const char* msg) : message(msg)
{
}

const char* LexecalException::what() const noexcept
{
    return message.c_str();
}

// canonical form
LexecalException::LexecalException():message("lexecal exception"){}

LexecalException::LexecalException(const LexecalException &other){
    this->message = other.message;
}

LexecalException& LexecalException::operator=(const LexecalException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

LexecalException::~LexecalException() noexcept =  default;

/*------------------------------ Execution errors ---------------------------------*/
VMException::VMException(const char* msg) : message(msg)
{
}

const char* VMException::what() const noexcept
{
    return message.c_str();
}

// canonical form
VMException::VMException():message("vm exception"){}

VMException::VMException(const VMException &other){
    this->message = other.message;
}

VMException& VMException::operator=(const VMException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

VMException::~VMException() noexcept =  default;

/*------------------------------ Execution errors ---------------------------------*/
AssertException::AssertException(const char* msg) : message(msg)
{
}

const char* AssertException::what() const noexcept
{
    return message.c_str();
}


// canonical form
AssertException::AssertException():message("assert exception"){}

AssertException::AssertException(const AssertException &other){
    this->message = other.message;
}

AssertException& AssertException::operator=(const AssertException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

AssertException::~AssertException() noexcept =  default;
/*------------------------------ Execution errors ---------------------------------*/
PopOnEmptyException::PopOnEmptyException(const char* msg) : message(msg)
{
}

const char* PopOnEmptyException::what() const noexcept
{
    return message.c_str();
}

// canonical form
PopOnEmptyException::PopOnEmptyException():message("pop on empty stack exception"){}

PopOnEmptyException::PopOnEmptyException(const PopOnEmptyException &other){
    this->message = other.message;
}

PopOnEmptyException& PopOnEmptyException::operator=(const PopOnEmptyException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

PopOnEmptyException::~PopOnEmptyException() noexcept =  default;
/*------------------------------ Execution errors ---------------------------------*/
ExitException::ExitException(const char* msg) : message(msg)
{
}

const char* ExitException::what() const noexcept
{
    return message.c_str();
}

// canonical form
ExitException::ExitException():message("Exit exception"){}

ExitException::ExitException(const ExitException &other){
    this->message = other.message;
}

ExitException& ExitException::operator=(const ExitException &other){
    if (this != &other){
        this->message = other.message;
    }
    return *this;
}

ExitException::~ExitException() noexcept =  default;