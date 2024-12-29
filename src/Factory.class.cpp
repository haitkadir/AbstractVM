#include "../include/Factory.class.hpp"



OperandFactory::OperandFactory() { // default constractor
    _createFunctions = {
        &OperandFactory::createInt8,
        &OperandFactory::createInt16,
        &OperandFactory::createInt32,
        &OperandFactory::createFloat,
        &OperandFactory::createDouble
    };
}

// OperandFactory::OperandFactory(const OperandFactory& other) = default;
// OperandFactory& OperandFactory::operator=(const OperandFactory& other) = default;
// OperandFactory::~OperandFactory() = default;


IOperand const* OperandFactory::createOperand(eOperandType type, std::string const& value) const {
    return (this->*_createFunctions[type])(value);
}

IOperand const* OperandFactory::createInt8(std::string const& value) const {
    return new Operand<int8_t>(std::stoi(value), Int8);
}

IOperand const* OperandFactory::createInt16(std::string const& value) const {
    return new Operand<int16_t>(std::stoi(value), Int16);
}

IOperand const* OperandFactory::createInt32(std::string const& value) const {
    return new Operand<int32_t>(std::stoi(value), Int32);
}

IOperand const* OperandFactory::createFloat(std::string const& value) const {
    return new Operand<float>(std::stof(value), Float);
}

IOperand const* OperandFactory::createDouble(std::string const& value) const {
    return new Operand<double>(std::stod(value), Double);
}
