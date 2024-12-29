#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


class OverfflowException : public std::exception {
private:
    std::string message;

public:
    OverfflowException(const char* msg);

    const char* what() const throw();
};



#endif