#include "../include/Lexer.hpp"
#include "../include/Exceptions.hpp"

/*----------------------------------------------------------------------------*/
Lexer::Lexer (): _input(""), _line(1) {}

/*----------------------------------------------------------------------------*/
Lexer::Lexer (const Lexer &a){
    this->_input = a._input;
    this->_line = a._line;
}

/*----------------------------------------------------------------------------*/
Lexer & Lexer::operator = (const Lexer &a){
    if (this != &a){
        this->_input = a._input;
        this->_line = a._line;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
Lexer::~Lexer () {
    this->_Tokens.clear();
}


/*----------------------------------------------------------------------------*/
Token Lexer::identifyToken(const std::string& value) {
    Token token;

    const std::vector<std::pair<std::regex, TokenType>> patterns = {
        {std::regex(R"(^push\s+int8\((-?\d+)\)\s*(?:;.*)?$)"), PUSHINT8},
        {std::regex(R"(^push\s+int16\((-?\d+)\)\s*(?:;.*)?$)"), PUSHINT16},
        {std::regex(R"(^push\s+int32\((-?\d+)\)\s*(?:;.*)?$)"), PUSHINT32},
        {std::regex(R"(^push\s+float\((-?\d+\.\d+)\)\s*(?:;.*)?$)"), PUSHFLOAT},
        {std::regex(R"(^push\s+double\((-?\d+\.\d+)\)\s*(?:;.*)?$)"), PUSHDOUBLE},
        {std::regex(R"(^assert\s+int8\((-?\d+)\)\s*(?:;.*)?$)"), ASSERTINT8},
        {std::regex(R"(^assert\s+int16\((-?\d+)\)\s*(?:;.*)?$)"), ASSERTINT16},
        {std::regex(R"(^assert\s+int32\((-?\d+)\)\s*(?:;.*)?$)"), ASSERTINT32},
        {std::regex(R"(^assert\s+float\((-?\d+\.\d+)\)\s*(?:;.*)?$)"), ASSERTFLOAT},
        {std::regex(R"(^assert\s+double\((-?\d+\.\d+)\)\s*(?:;.*)?$)"), ASSERTDOUBLE},
        {std::regex(R"(^pop\s*(?:;.*)?$)"), POP},
        {std::regex(R"(^dump\s*?$)"), DUMP},
        {std::regex(R"(^add\s*(?:;.*)?$)"), ADD},
        {std::regex(R"(^sub\s*(?:;.*)?$)"), SUB},
        {std::regex(R"(^mul\s*(?:;.*)?$)"), MUL},
        {std::regex(R"(^div\s*(?:;.*)?$)"), DIV},
        {std::regex(R"(^mod\s*(?:;.*)?$)"), MOD},
        {std::regex(R"(^print\s*(?:;.*)?$)"), PRINT},
        {std::regex(R"(^exit\s*(?:;.*)?$)"), EXIT}
    };
    std::smatch match;
    for (const auto& [pattern, type] : patterns) {
        if (std::regex_match(value, match, pattern)) {
            token.type = type;
            if (token.type > ASSERTDOUBLE)
                token.value = match[0];
            else
                token.value = match[1];
            this->trim(token.value, "\t ");
            return token;
        }
    }
    token.type = INVALID;
    return token;
}


/*----------------------------------------------------------------------------*/
void Lexer::trim(std::string &str, const char *to_trim){
    str.erase(0, str.find_first_not_of(to_trim));                                                                                               
    str.erase(str.find_last_not_of(to_trim)+1);
}


/*
        This function toknizes the input as type, value and line
--------------------------------------------------------------------------------
*/
void    Lexer::tokenize(const std::string& input) {
    this->_input = input;
    std::istringstream streamfile(input);
    std::string line;

    while (std::getline(streamfile, line)) {
        if (std::regex_match(line, std::regex(R"(^\s+$)"))
            || std::regex_match(line, std::regex(R"(^;.*$)"))
            || std::regex_match(line, std::regex(R"(^$)"))){
            ++_line;
            continue;
        }
        Token token;
        Token temp;
        temp = identifyToken(line);
        token.value = line;
        token.type = temp.type;
        token.value = temp.value;
        token.line = _line;

        if (token.type == INVALID) {
            std::string error = "Lexical error on line " + std::to_string(_line);
            throw LexecalException(error.c_str());
        }
        this->_Tokens.push_back(token);
        ++_line;
    }
    // if(this->_Tokens.size() && this->_Tokens.rbegin()->type != EXIT)
    //     throw LexecalException("Lexecal error: Program must end with 'exit' instruction");
}


/*
        This function Prints Tokens if there are any
--------------------------------------------------------------------------------
*/
void    Lexer::printTokens() const {
    std::vector<std::string>  types;
    types = {
    "PUSHINT8",
    "PUSHINT16",
    "PUSHINT32",
    "PUSHFLOAT",
    "PUSHDOUBLE",
    "ASSERTINT8",
    "ASSERTINT16",
    "ASSERTINT32",
    "ASSERTFLOAT",
    "ASSERTDOUBLE",
    "POP",
    "DUMP",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "PRINT",
    "EXIT",
    "INVALID"

    };
    for(auto &token: this->_Tokens){
        std::cout << "token: {" << std::endl;
        std::cout << "      line: " << token.line << std::endl;
        std::cout << "      type: " << types[token.type] << std::endl;
        std::cout << "      value: " << token.value << std::endl;
        std::cout << "}\n" << std::endl;
    }
}


/*
        This function returns toknes if there are any
--------------------------------------------------------------------------------
*/
std::vector<Token>  &Lexer::getTokens(){
    return this->_Tokens;
}
