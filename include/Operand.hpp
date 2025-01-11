#ifndef __OPERAND_H__
#define __OPERAND_H__

#include <cmath>
#include <limits>

#include "IOperand.interface.hpp"
#include "Factory.class.hpp"
#include "Exceptions.hpp"

#include <iostream>
#include <sstream>
#include <type_traits>
#include <limits>
#include <iomanip>

template <typename T>
class Operand : public IOperand {
private:
    T               _value;
    eOperandType    _type;
    std::string     _strValue;

public:

    /*----------------------------------------------------------------------------*/
    Operand(): _value(), _type(Int8), _strValue("0")
    {
    }

    /*----------------------------------------------------------------------------*/
    Operand(const Operand& other) {
        this->_value = std::stod(other.toString());
        this->_type = other.getType();
        this->_strValue = other.toString();
    }

    /*----------------------------------------------------------------------------*/
    Operand& operator=(const Operand& other){
        if (this != &other){
            this->_value = std::stod(other.toString());
            this->_type = other.getType();
            this->_strValue = other.toString();
        }
        return *this;
    }

    /*----------------------------------------------------------------------------*/
    ~Operand()
    {
    }

    /*----------------------------------------------------------------------------*/
    Operand(std::string const &value, eOperandType type){
        if(!isoverflow(type, value)){
            _value = std::stod(value);
            _type = type;
            _strValue = value;
        }else {
            throw OverfflowException("Error: Out Of Range");
        }
    }

    /*----------------------------------------------------------------------------*/
    int getPrecision() const override {
        return static_cast<int>(_type);
    }

    /*----------------------------------------------------------------------------*/
    eOperandType getType() const override {
        return _type;
    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator+(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, typeNormaliser(v1 + v2, resultType));
		return newOperand;

    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator-(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, typeNormaliser(v1 - v2, resultType));
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator*(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, typeNormaliser(v1 * v2, resultType));
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw DiviModuByZeroException("Division by zero");
        }

        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, typeNormaliser(v1 / v2, resultType));
		return newOperand;

    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw DiviModuByZeroException("Modulo by zero");
        }
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, typeNormaliser(std::fmod(v1 , v2), resultType));
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    std::string const& toString() const override {
        return _strValue;
    }
private:

    /*----------------------------------------------------------------------------*/
    std::string typeNormaliser(double value, eOperandType type) const {
        std::ostringstream oss;

        if (!isoverflow(type, std::to_string(value))){

            switch (type) {
                case Int8 ... Int32: {
                    int intValue = static_cast<int>(std::round(value));
                    return std::to_string(intValue);
                }
                case Float: {
                    float floatValue = static_cast<float>(value);
                    oss << std::fixed << std::setprecision(7) << floatValue; 
                    return oss.str();
                }
                case Double: {
                    oss << std::fixed << std::setprecision(15) << value;
                    return oss.str();
                }
                default:
                    return std::to_string(value);
            }
        }else {
            throw OverfflowException("Error: Out Of Range");
        }
    }

    /*----------------------------------------------------------------------------*/

    bool isoverflow(eOperandType type, const std::string& input) const {
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
                    int intvalue = std::stoi(input);
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

    /*----------------------------------------------------------------------------*/

};

#endif