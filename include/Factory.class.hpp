#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <vector>
// #include <string>

#include "IOperand.interface.hpp"

class OperandFactory {
private:
    typedef  IOperand const* (OperandFactory::*CreateFunction)(std::string const&) const;
    std::vector<CreateFunction> _createFunctions;

public:
    // Default constructor
    OperandFactory();

    OperandFactory(const OperandFactory& other) = default;
    OperandFactory& operator=(const OperandFactory& other) = default;
    ~OperandFactory() = default;


    IOperand const* createOperand(eOperandType type, std::string const& value) const;

private:
    IOperand const* createInt8(std::string const& value) const;
    IOperand const* createInt16(std::string const& value) const;
    IOperand const* createInt32(std::string const& value) const;
    IOperand const* createFloat(std::string const& value) const;
    IOperand const* createDouble(std::string const& value) const;
};



#endif