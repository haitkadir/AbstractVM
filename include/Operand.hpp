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
    Operand(): _value(), _type(Int8), _strValue("0")
    {
    }
    Operand(const Operand& other) {
        this->_value = static_cast<T>(std::stod(other.toString()));
        this->_type = other.getType();
        this->_strValue = other.toString();
    }
    Operand& operator=(const Operand& other){
        if (this != &other){
            this->_value = static_cast<T>(std::stod(other.toString()));
            this->_type = other.getType();
            this->_strValue = other.toString();
        }
        return *this;
    }
    ~Operand()
    {
    }


    Operand(std::string const &value, eOperandType type){
        if(!isoverfflow(type, value)){
            _value = static_cast<T>(std::stod(value));
            _type = type;
            _strValue = std::to_string(static_cast<T>(std::stod(value)));
        }else {
            throw OverfflowException("Error: Out Of Range");
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
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, std::to_string(v1 + v2));
		return newOperand;

    }

    IOperand const* operator-(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, std::to_string(v1 - v2));
		return newOperand;
    }

    IOperand const* operator*(IOperand const& rhs) const override {
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, std::to_string(v1 * v2));
		return newOperand;
    }

    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) { // re implement the check Division by zero logic
            throw DiviModuByZeroException("Division by zero");
        }

        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, std::to_string(v1 / v2));
		return newOperand;

    }

    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) { // re implement this check Modulo by zero logic
            throw DiviModuByZeroException("Modulo by zero");
        }
        double v1 = (static_cast<double>(_value));
        double v2 = (std::stod(rhs.toString()));
        // I should check overflow here.
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
		OperandFactory factory;
		IOperand const *newOperand = factory.createOperand(resultType, std::to_string(std::fmod(v1 , v2)));
		return newOperand;
    }

    std::string const& toString() const override {
        return _strValue;
    }
private:
    bool    isoverfflow(eOperandType type, std::string const &input){
        double  value;
        try{
            if (type == Float)
                value = std::stof(input);
            else
                value = std::stod(input);
        }  catch (const std::out_of_range&) {
            return true;
        } catch (const std::invalid_argument&) {
            return true;
        }
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

};

#endif