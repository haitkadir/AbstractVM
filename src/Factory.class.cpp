#include "../include/Factory.class.hpp"
#include "../include/Operand.hpp"



/*----------------------------------------------------------------------------*/
OperandFactory::OperandFactory() {
    _createFunctions = {
        &OperandFactory::createInt8,
        &OperandFactory::createInt16,
        &OperandFactory::createInt32,
        &OperandFactory::createFloat,
        &OperandFactory::createDouble
    };
}

/*----------------------------------------------------------------------------*/
OperandFactory::OperandFactory(const OperandFactory& other){
    this->_createFunctions = other._createFunctions;
}

/*----------------------------------------------------------------------------*/
OperandFactory& OperandFactory::operator=(const OperandFactory& other){
    if (this == &other){
        this->_createFunctions = other._createFunctions;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
OperandFactory::~OperandFactory(){
    this->_createFunctions.clear();
}


/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createOperand(eOperandType type, std::string const& value) const {
    return (this->*_createFunctions[type])(value);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt8(std::string const& value) const {
    return new Operand<int8_t>(value, Int8);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt16(std::string const& value) const {
    return new Operand<int16_t>(value, Int16);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt32(std::string const& value) const {
    return new Operand<int32_t>(value, Int32);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createFloat(std::string const& value) const {
    return new Operand<float>(value, Float);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createDouble(std::string const& value) const {
    return new Operand<double>(value, Double);
}
