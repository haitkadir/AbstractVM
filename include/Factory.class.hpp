#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <vector>
#include <string>

#include "IOperand.interface.hpp"
// #include "Operand.tpp"

class OperandFactory {
private:
    using CreateFunction = IOperand const* (OperandFactory::*)(std::string const&) const;

    std::vector<CreateFunction> _createFunctions;

    OperandFactory() {
        _createFunctions = {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
        };
    }

public:
    static OperandFactory& getInstance() {
        static OperandFactory instance;
        return instance;
    }

    IOperand const* createOperand(eOperandType type, std::string const& value) const {
        return (this->*_createFunctions[type])(value);
    }

private:
    IOperand const* createInt8(std::string const& value) const {
        return new Operand<int8_t>(std::stoi(value), Int8);
    }

    IOperand const* createInt16(std::string const& value) const {
        return new Operand<int16_t>(std::stoi(value), Int16);
    }

    IOperand const* createInt32(std::string const& value) const {
        return new Operand<int32_t>(std::stoi(value), Int32);
    }

    IOperand const* createFloat(std::string const& value) const {
        return new Operand<float>(std::stof(value), Float);
    }

    IOperand const* createDouble(std::string const& value) const {
        return new Operand<double>(std::stod(value), Double);
    }
};



#endif