#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <functional>

// Enumeration for operand types
enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

// IOperand interface
class IOperand {
public:
    virtual int getPrecision() const = 0;
    virtual eOperandType getType() const = 0;
    virtual IOperand const* operator+(IOperand const& rhs) const = 0;
    virtual IOperand const* operator-(IOperand const& rhs) const = 0;
    virtual IOperand const* operator*(IOperand const& rhs) const = 0;
    virtual IOperand const* operator/(IOperand const& rhs) const = 0;
    virtual IOperand const* operator%(IOperand const& rhs) const = 0;
    virtual std::string const& toString() const = 0;
    virtual ~IOperand() {}
};

// BaseOperand template class template for reusability
template <typename T>
class Operand : public IOperand {
private:
    T _value;
    eOperandType _type;
    std::string _strValue;

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

// Factory for creating operands
class OperandFactory {
private:
    using CreateFunction = IOperand const* (OperandFactory::*)(std::string const&) const;
    std::vector<CreateFunction> _createFunctions;

    OperandFactory() {
        _createFunctions = {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
        };
    }

public:
    static OperandFactory& getInstance() {
        static OperandFactory instance;
        return instance;
    }

    IOperand const* createOperand(eOperandType type, std::string const& value) const {
        return (this->*_createFunctions[type])(value);
    }

private:
    IOperand const* createInt8(std::string const& value) const {
        return new Operand<int8_t>(std::stoi(value), Int8);
    }

    IOperand const* createInt16(std::string const& value) const {
        return new Operand<int16_t>(std::stoi(value), Int16);
    }

    IOperand const* createInt32(std::string const& value) const {
        return new Operand<int32_t>(std::stoi(value), Int32);
    }

    IOperand const* createFloat(std::string const& value) const {
        return new Operand<float>(std::stof(value), Float);
    }

    IOperand const* createDouble(std::string const& value) const {
        return new Operand<double>(std::stod(value), Double);
    }
};

// Example Usage
int main() {
    OperandFactory& factory = OperandFactory::getInstance();

    IOperand const* op1 = factory.createOperand(Int32, "42");
    IOperand const* op2 = factory.createOperand(Float, "3.14");

    IOperand const* result = *op1 + *op2;

    std::cout << "Result: " << result->toString() << "\n";

    delete op1;
    delete op2;
    delete result;

    return 0;
}
