#ifndef __OPERAND_H__
#define __OPERAND_H__

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <functional>

#include "IOperand.interface.hpp"

#include "Factory.class.hpp"

template <typename T>
class Operand : public IOperand {
private:
    T               _value;
    eOperandType    _type;
    std::string     _strValue;

public:
    Operand(T value, eOperandType type) : _value(value), _type(type) {
        std::ostringstream oss;
        oss << value;
        _strValue = oss.str();
    }

    int getPrecision() const override {
        return static_cast<int>(_type);
    }

    eOperandType getType() const override {
        return _type;
    }

    IOperand const* operator+(IOperand const& rhs) const override {
        double result = std::stod(toString()) + std::stod(rhs.toString());
        return createResultOperand(result, rhs);
    }

    IOperand const* operator-(IOperand const& rhs) const override {
        double result = std::stod(toString()) - std::stod(rhs.toString());
        return createResultOperand(result, rhs);
    }

    IOperand const* operator*(IOperand const& rhs) const override {
        double result = std::stod(toString()) * std::stod(rhs.toString());
        return createResultOperand(result, rhs);
    }

    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw std::runtime_error("Division by zero");
        }
        double result = std::stod(toString()) / std::stod(rhs.toString());
        return createResultOperand(result, rhs);
    }

    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        double result = std::fmod(std::stod(toString()), std::stod(rhs.toString()));
        return createResultOperand(result, rhs);
    }

    std::string const& toString() const override {
        return _strValue;
    }

private:
    IOperand const* createResultOperand(double result, IOperand const& rhs) const {

        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        
        return OperandFactory::getInstance().createOperand(resultType, std::to_string(result));
    }
};



#endif