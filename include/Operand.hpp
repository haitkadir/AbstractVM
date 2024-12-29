#ifndef __OPERAND_H__
#define __OPERAND_H__

#include <cmath>
#include <limits>

#include "IOperand.interface.hpp"


template <typename T>
class Operand : public IOperand {
private:
    T               _value;
    eOperandType    _type;
    std::string     _strValue;

public:
    Operand(T value, eOperandType type){
        if(isoverfflow(type, value)){
            _value = value;
            _type = type
            _strValue = std::to_string(value);
        }
    }

    int getPrecision() const override {
        return static_cast<int>(_type);
    }

    eOperandType getType() const override {
        return _type;
    }

    IOperand const* operator+(IOperand const& rhs) const override {
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
            switch (resultType) {
            case Int8: return new Operand<int8_t>(static_cast<int8_t>(_value) + std::stoi(rhs.toString()), Int8);
            case Int16: return new Operand<int16_t>(static_cast<int16_t>(_value) + std::stoi(rhs.toString()), Int16);
            case Int32: return new Operand<int32_t>(static_cast<int32_t>(_value) + std::stoi(rhs.toString()), Int32);
            case Float: return new Operand<float>(static_cast<float>(_value) + std::stof(rhs.toString()), Float);
            case Double: return new Operand<double>(static_cast<double>(_value) + std::stod(rhs.toString()), Double);
            default: throw std::invalid_argument("Invalid operand type");
        }
    }

    IOperand const* operator-(IOperand const& rhs) const override {
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
            switch (resultType) {
            case Int8: return new Operand<int8_t>(static_cast<int8_t>(_value) - std::stoi(rhs.toString()), Int8);
            case Int16: return new Operand<int16_t>(static_cast<int16_t>(_value) - std::stoi(rhs.toString()), Int16);
            case Int32: return new Operand<int32_t>(static_cast<int32_t>(_value) - std::stoi(rhs.toString()), Int32);
            case Float: return new Operand<float>(static_cast<float>(_value) - std::stof(rhs.toString()), Float);
            case Double: return new Operand<double>(static_cast<double>(_value) - std::stod(rhs.toString()), Double);
            default: throw std::invalid_argument("Invalid operand type");
        }
    }

    IOperand const* operator*(IOperand const& rhs) const override {
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
            switch (resultType) {
            case Int8: return new Operand<int8_t>(static_cast<int8_t>(_value) * std::stoi(rhs.toString()), Int8);
            case Int16: return new Operand<int16_t>(static_cast<int16_t>(_value) * std::stoi(rhs.toString()), Int16);
            case Int32: return new Operand<int32_t>(static_cast<int32_t>(_value) * std::stoi(rhs.toString()), Int32);
            case Float: return new Operand<float>(static_cast<float>(_value) * std::stof(rhs.toString()), Float);
            case Double: return new Operand<double>(static_cast<double>(_value) * std::stod(rhs.toString()), Double);
            default: throw std::invalid_argument("Invalid operand type");
        }
    }

    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw std::runtime_error("Division by zero");
        }
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
            switch (resultType) {
            case Int8: return new Operand<int8_t>(static_cast<int8_t>(_value) / std::stoi(rhs.toString()), Int8);
            case Int16: return new Operand<int16_t>(static_cast<int16_t>(_value) / std::stoi(rhs.toString()), Int16);
            case Int32: return new Operand<int32_t>(static_cast<int32_t>(_value) / std::stoi(rhs.toString()), Int32);
            case Float: return new Operand<float>(static_cast<float>(_value) / std::stof(rhs.toString()), Float);
            case Double: return new Operand<double>(static_cast<double>(_value) / std::stod(rhs.toString()), Double);
            default: throw std::invalid_argument("Invalid operand type");
        }
    }

    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType) {
            case Int8: return new Operand<int8_t>(static_cast<int8_t>(_value) % std::stoi(rhs.toString()), Int8);
            case Int16: return new Operand<int16_t>(static_cast<int16_t>(_value) % std::stoi(rhs.toString()), Int16);
            case Int32: return new Operand<int32_t>(static_cast<int32_t>(_value) % std::stoi(rhs.toString()), Int32);
            case Float: return new Operand<float>(std::fmod(static_cast<float>(_value), std::stof(rhs.toString())), Float);
            case Double: return new Operand<double>(std::fmod(static_cast<double>(_value), std::stod(rhs.toString())), Double);
            default: throw std::invalid_argument("Invalid operand type");
        }
    }

    std::string const& toString() const override {
        return _strValue;
    }
private:
    bool    isoverfflow(eOperandType type, T value){
        switch (type)
        {
        case Int8: value > std::numeric_limits<int8>::lowest()
        default:
            break;
        }
    }

};



#endif