#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/*------------------------- For Overfflow ------------------------------*/
class OverfflowException : public std::exception {
private:
    std::string message;

public:
    OverfflowException(const char* msg);
    const char* what() const noexcept override;
};

/*-------------------- For Division or Modulo by zero --------------------*/
class   DiviModuByZeroException : public std::exception {
private:
    std::string message;

public:
    DiviModuByZeroException(const char* msg);
    const char* what() const noexcept override;
};

/*---------------------------- Lexecal errors -----------------------------*/
class   LexecalException : public std::exception {
private:
    std::string message;

public:
    LexecalException(const char* msg);
    const char* what() const noexcept override;
};

/*---------------------------- Lexecal errors -----------------------------*/
class   VMException : public std::exception {
private:
    std::string message;

public:
    VMException(const char* msg);
    const char* what() const noexcept override;
};

/*---------------------------- Lexecal errors -----------------------------*/
class   AssertException : public std::exception {
private:
    std::string message;

public:
    AssertException(const char* msg);
    const char* what() const noexcept override;
};



#endif