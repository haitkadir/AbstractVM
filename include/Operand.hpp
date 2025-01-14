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
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 + int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 + float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
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
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 - int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 - float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
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
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 * int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 * float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
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
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 / int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                newOperand = factory.createOperand(resultType, std::to_string(float_v1 / float_v2));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
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
                newOperand = factory.createOperand(resultType, std::to_string(int_v1 % int_v2));
                break;
            }
            case Float:{
                float float_v1 = (std::stof(this->toString()));
                float float_v2 = (std::stof(rhs.toString()));
                newOperand = factory.createOperand(resultType, std::to_string(std::fmodf(float_v1, float_v2)));
                break;
            }
            case Double:{
                double double_v1 = (std::stod(this->toString()));
                double double_v2 = (std::stod(rhs.toString()));
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

};

#endif