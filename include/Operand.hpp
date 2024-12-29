#ifndef __OPERAND_H__
#define __OPERAND_H__

#include <cmath>
#include <limits>

#include "IOperand.interface.hpp"
#include "Factory.class.hpp"
#include "Exceptions.hpp"

#include <iostream>


template <typename T>
class Operand : public IOperand {
private:
    T               _value;
    eOperandType    _type;
    std::string     _strValue;

public:
    Operand(T value, eOperandType type){
        if(!isoverfflow(type, value)){
            _value = value;
            _type = type;
            _strValue = std::to_string(value);
        }else {
            throw OverfflowException("Overfflow/Undefflow");
        }
    }

    int getPrecision() const override {
        return static_cast<int>(_type);
    }

    eOperandType getType() const override {
        return _type;
    }

    IOperand const* operator+(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory *factory = new OperandFactory();
		IOperand const *newOperand = factory->createOperand(resultType, std::to_string(v1 + v2));
		delete factory;
		return newOperand;

    }

    IOperand const* operator-(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory *factory = new OperandFactory();
		IOperand const *newOperand = factory->createOperand(resultType, std::to_string(v1 - v2));
		delete factory;
		return newOperand;
    }

    IOperand const* operator*(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory *factory = new OperandFactory();
		IOperand const *newOperand = factory->createOperand(resultType, std::to_string(v1 * v2));
		delete factory;
		return newOperand;
    }

    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) { // re implement the check Division by zero logic
            throw std::runtime_error("Division by zero");
        }

        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory *factory = new OperandFactory();
		IOperand const *newOperand = factory->createOperand(resultType, std::to_string(v1 / v2));
		delete factory;
		return newOperand;

    }

    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) { // re implement this check Modulo by zero logic
            throw std::runtime_error("Modulo by zero");
        }
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory *factory = new OperandFactory();
		IOperand const *newOperand = factory->createOperand(resultType, std::to_string(std::fmod(v1 , v2)));
		delete factory;
		return newOperand;
    }

    std::string const& toString() const override {
        return _strValue;
    }
private:
    bool    isoverfflow(eOperandType type, T value){
        switch (type)
        {
            case Int8: return (value < std::numeric_limits<int8_t>::min() || value > std::numeric_limits<int8_t>::max()) ? true: false;
            case Int16: return (value < std::numeric_limits<int16_t>::min() || value > std::numeric_limits<int16_t>::max()) ? true: false;
            case Int32: return (value < std::numeric_limits<int32_t>::min() || value > std::numeric_limits<int32_t>::max()) ? true: false;
            case Float: return std::isinf(value) ? true: false;
            case Double: return std::isinf(value) ? true: false;
            default:
                return false;
        }
    }
    bool    iszerovalue(eOperandType type, T value){

    }

};



#endif