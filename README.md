# Abstract VM

A C++ project to create a simple stack-based virtual machine capable of interpreting basic assembly-like programs for arithmetic operations.

## Features

- Supports arithmetic and stack operations like `add`, `sub`, `mul`, `div`, `push`, and `pop`.
- Handles multiple data types: `int8`, `int16`, `int32`, `float`, and `double`.
- Validates inputs with robust error handling.

## Assembly Language Overview

### Example Program
```assembly
; Basic program example  
push int32(42)  
push int32(33)  
add  
dump  
exit  
```
### Instructions

- `push v`: Push a value onto the stack (`int8(n)`, `int16(n)`, `int32(n)`, `float(z)`, `double(z)`).
- `pop`: Remove the top value from the stack.
- `dump`: Print stack values without altering the stack.
- `assert v`: Verify the top stack value matches the provided value.
- `add`, `sub`, `mul`, `div`, `mod`: Perform arithmetic on the top two stack values.
- `print`: Display the ASCII character of an `int8` value on top of the stack.
- `exit`: End the program.

### Error Handling

The VM detects and handles:
- Lexical/syntactic errors.
- Operations on an empty stack.
- Division/modulo by zero.
- Overflow/underflow issues.
- Missing `exit` instruction.

## Implementation Details

### The Stack

The VM uses a stack structure with pointers to `IOperand` objects representing different data types.

### Operand Types

- **Int8**, **Int16**, **Int32**: Represent signed integers.
- **Float**, **Double**: Represent floating-point numbers.

### Precision Rules

Operands with different types use the highest precision type for operations:  
`Int8 < Int16 < Int32 < Float < Double`.

### Operand Factory

Uses a factory method to create operands dynamically based on type.

## Usage

### Compilation

Run the following:  
make

### Running the VM

Provide a program file or use standard input:  
./avm program.avm

Example of standard input:
```assembly  
./avm  
push int32(42)  
push int32(33)  
add  
dump  
exit  
;;  
```
## Contributing

Feel free to suggest improvements or report issues via GitHub.

## License

This project is for educational purposes and follows standard project rules.
