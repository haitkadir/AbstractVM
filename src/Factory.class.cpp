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
    if(!isoverflow(type, value)){
        return (this->*_createFunctions[type])(value);
    }else{
        throw OverfflowException("Error: Out Of Range");
    }
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt8(std::string const& value) const {
    return new Operand<int8_t>(std::stoi(value), Int8);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt16(std::string const& value) const {
    return new Operand<int16_t>(std::stoi(value), Int16);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createInt32(std::string const& value) const {
    return new Operand<int32_t>(std::stoi(value), Int32);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createFloat(std::string const& value) const {
    return new Operand<float>(std::stof(value), Float);
}

/*----------------------------------------------------------------------------*/
IOperand const* OperandFactory::createDouble(std::string const& value) const {
    return new Operand<double>(std::stod(value), Double);
}

/*----------------------------------------------------------------------------*/

bool OperandFactory::isoverflow(eOperandType type, const std::string& input) const {
    try {
        switch (type) {
            case Int8: {
                int int8value = std::stoi(input);
                if (int8value < std::numeric_limits<int8_t>::min() || int8value > std::numeric_limits<int8_t>::max()) {
                    return true;
                }
                break;
            }
            case Int16: {
                int int16value = std::stoi(input);
                if (int16value < std::numeric_limits<int16_t>::min() || int16value > std::numeric_limits<int16_t>::max()) {
                    return true;
                }
                break;
            }
            case Int32: {
                std::cout << "I'm here before-------------------" << input << std::endl;
                float intvalue = std::stof(input);
                std::cout << "I'm here after-------------------" << (intvalue > std::numeric_limits<int32_t>::max()) << std::endl;
                if (intvalue < std::numeric_limits<int32_t>::min() || intvalue > std::numeric_limits<int32_t>::max()) {
                    return true;
                }
                break;
            }
            case Float: {
                float floatValue = std::stof(input);
                if (std::isinf(floatValue)) {
                    return true;
                }
                break;
            }
            case Double: {
                double doubleValue = std::stod(input);
                if (std::isinf(doubleValue)) {
                    return true;
                }
                break;
            }
            default:
                return false;
        }

    } catch (const std::out_of_range&) {
        return true;
    }
    return false;
}