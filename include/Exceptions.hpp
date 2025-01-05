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
    //canonical form
    OverfflowException();
    OverfflowException(const OverfflowException &other);
    OverfflowException& operator=(const OverfflowException &other);
    ~OverfflowException() noexcept override;
};

/*-------------------- For Division or Modulo by zero --------------------*/
class   DiviModuByZeroException : public std::exception {
private:
    std::string message;

public:
    DiviModuByZeroException(const char* msg);
    const char* what() const noexcept override;
    //canonical form
    DiviModuByZeroException();
    DiviModuByZeroException(const DiviModuByZeroException &other);
    DiviModuByZeroException& operator=(const DiviModuByZeroException &other);
    ~DiviModuByZeroException() noexcept override;
};

/*---------------------------- Lexecal errors -----------------------------*/
class   LexecalException : public std::exception {
private:
    std::string message;

public:
    LexecalException(const char* msg);
    const char* what() const noexcept override;
    //canonical form
    LexecalException();
    LexecalException(const LexecalException &other);
    LexecalException& operator=(const LexecalException &other);
    ~LexecalException() noexcept override;
};

/*---------------------------- Lexecal errors -----------------------------*/
class   VMException : public std::exception {
private:
    std::string message;

public:
    VMException(const char* msg);
    const char* what() const noexcept override;
    //canonical form
    VMException();
    VMException(const VMException &other);
    VMException& operator=(const VMException &other);
    ~VMException() noexcept override;
};

/*---------------------------- Execution errors -----------------------------*/
class   AssertException : public std::exception {
private:
    std::string message;

public:
    AssertException(const char* msg);
    const char* what() const noexcept override;
        //canonical form
    AssertException();
    AssertException(const AssertException &other);
    AssertException& operator=(const AssertException &other);
    ~AssertException() noexcept override;
};

/*---------------------------- Execution errors -----------------------------*/
class   PopOnEmptyException : public std::exception {
private:
    std::string message;

public:
    PopOnEmptyException(const char* msg);
    const char* what() const noexcept override;
        //canonical form
    PopOnEmptyException();
    PopOnEmptyException(const PopOnEmptyException &other);
    PopOnEmptyException& operator=(const PopOnEmptyException &other);
    ~PopOnEmptyException() noexcept override;
};


/*---------------------------- Exit exception -----------------------------*/
class   ExitException : public std::exception {
private:
    std::string message;

public:
    ExitException(const char* msg);
    const char* what() const noexcept override;
        //canonical form
    ExitException();
    ExitException(const ExitException &other);
    ExitException& operator=(const ExitException &other);
    ~ExitException() noexcept override;
};



#endif