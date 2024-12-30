#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


class OverfflowException : public std::exception {
private:
    std::string message;

public:
    OverfflowException(const char* msg);

    const char* what() const noexcept override;
};

class   DiviModuByZeroException : public std::exception {
private:
    std::string message;

public:
    DiviModuByZeroException(const char* msg);

    const char* what() const noexcept override;
};



#endif