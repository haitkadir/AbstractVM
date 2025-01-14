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
    Operand(): _value(0), _type(Int8), _strValue("0")
    {
    }

    /*----------------------------------------------------------------------------*/
    Operand(const Operand& other) {
        this->_value = other._value;
        this->_type = other.getType();
        this->_strValue = other._strValue;
    }

    /*----------------------------------------------------------------------------*/
    Operand& operator=(const Operand& other){
        if (this != &other){
            this->_value = other._value;
            this->_type = other.getType();
            this->_strValue = other._strValue;
        }
        return *this;
    }

    /*----------------------------------------------------------------------------*/
    ~Operand()
    {
    }

    /*----------------------------------------------------------------------------*/
    Operand(T const &value, eOperandType type){

        _value = value;
        _strValue = std::to_string(_value);
        _type = type;

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
        IOperand const *newOperand;

		OperandFactory factory;
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType)
        {
            case Int8 ... Int32:{
                int int_v1 = (std::stoi(this->toString()));
                int int_v2 = (std::stoi(rhs.toString()));
                checkOverflow<long long>((static_cast<long long>(int_v1) + int_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 + int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                checkOverflow<double>((static_cast<double>(float_v1) + float_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 + float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
                checkOverflow<long double>((static_cast<long double>(double_v1) + double_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(double_v1 + double_v2));
                break;
            }
            default:{

                throw   VMException("Uknown type on + operand");
                break;
            }
        }
		return newOperand;

    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator-(IOperand const& rhs) const override {
        IOperand const *newOperand;

		OperandFactory factory;
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType)
        {
            case Int8 ... Int32:{
                int int_v1 = (std::stoi(this->toString()));
                int int_v2 = (std::stoi(rhs.toString()));
                checkOverflow<long long>((static_cast<long long>(int_v1) - int_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 - int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                checkOverflow<double>((static_cast<double>(float_v1) - float_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 - float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
                checkOverflow<long double>((static_cast<long double>(double_v1) - double_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(double_v1 - double_v2));
                break;
            }
            
            default:{

                throw   VMException("Uknown type on - operand");
                break;
            }
        }
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator*(IOperand const& rhs) const override {
        IOperand const *newOperand;

		OperandFactory factory;
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType)
        {
            case Int8 ... Int32:{
                int int_v1 = (std::stoi(this->toString()));
                int int_v2 = (std::stoi(rhs.toString()));
                checkOverflow<long long>((static_cast<long long>(int_v1) * int_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 * int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                checkOverflow<double>((static_cast<double>(float_v1) * float_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 * float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
                checkOverflow<long double>((static_cast<long double>(double_v1) * double_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(double_v1 * double_v2));
                break;
            }
            
            default:{

                throw   VMException("Uknown type on * operand");
                break;
            }
        }
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator/(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw DiviModuByZeroException("Division by zero");
        }

        IOperand const *newOperand;

		OperandFactory factory;
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType)
        {
            case Int8 ... Int32:{
                int int_v1 = (std::stoi(this->toString()));
                int int_v2 = (std::stoi(rhs.toString()));
                checkOverflow<long long>((static_cast<long long>(int_v1) / int_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 / int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                checkOverflow<double>((static_cast<double>(float_v1) / float_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 / float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
                checkOverflow<long double>((static_cast<long double>(double_v1) / double_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(double_v1 / double_v2));
                break;
            }
            
            default:{

                throw   VMException("Uknown type on / operand");
                break;
            }
        }
		return newOperand;

    }

    /*----------------------------------------------------------------------------*/
    IOperand const* operator%(IOperand const& rhs) const override {
        if (std::stod(rhs.toString()) == 0) {
            throw DiviModuByZeroException("Modulo by zero");
        }
        IOperand const *newOperand;

		OperandFactory factory;
        eOperandType resultType = static_cast<eOperandType>(std::max(getPrecision(), rhs.getPrecision()));
        switch (resultType)
        {
            case Int8 ... Int32:{
                int int_v1 = (std::stoi(this->toString()));
                int int_v2 = (std::stoi(rhs.toString()));
                checkOverflow<long long>((static_cast<long long>(int_v1) % int_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 % int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                checkOverflow<double>(std::fmod(static_cast<double>(float_v1), float_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(std::fmodf(float_v1, float_v2)));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
                checkOverflow<long double>(fmodl(static_cast<long double>(double_v1), double_v2), resultType);
                newOperand = factory.createOperand(resultType, std::to_string(std::fmod(double_v1, double_v2)));
                break;
            }
            
            default:{

                throw   VMException("Uknown type on \% operand");
                break;
            }
        }
		return newOperand;
    }

    /*----------------------------------------------------------------------------*/
    std::string const& toString() const override {
        return _strValue;
    }

private:
    /*----------------------------------------------------------------------------*/
    template <typename P>
    void    checkOverflow(P input, eOperandType type) const{
        try{
            switch (type)
            {
            case Int8:{
                int int8Value = std::stoi(std::to_string(input));
          if (int8Value < INT8_MIN || int8Value > INT8_MAX)
                    throw   OverfflowException("int8 overflow");
                break;
            }
            case Int16:{
                int int16Value = std::stoi(std::to_string(input));
                if (int16Value < INT16_MIN || int16Value > INT16_MAX)
                    throw   OverfflowException("int16 overflow");
                break;
            }
            case Int32:{
                std::stoi(std::to_string(input));
                break;
            }
            case Float:{
                float floatValue = std::stod(std::to_string(input));
                if (std::isinf(floatValue)) {
                    throw   OverfflowException("overflow");
                }
                break;
            }
            case Double:{
                double doubleValue = std::stod(std::to_string(input));
                if (std::isinf(doubleValue)) {
                    throw   OverfflowException("overflow");
                }
                break;
            }
            default:
                break;
            }
        }catch(std::out_of_range &){
            throw   OverfflowException("overflow");
        }
    }

};

#endif