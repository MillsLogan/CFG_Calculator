#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <stack>
#include <string>


enum TokenType{
    LITERAL,
    IDENTIFIER,
    ADDOPS,
    MULOPS,
    EXPONENT,
    UNARYOPS,
    LPAREN,
    RPAREN,
    WHITESPACE,
    UNKNOWN,
    END
};

struct Token{
    Token(): value(""), type(TokenType::UNKNOWN){};
    Token(std::string value, TokenType type): value(value), type(type){};
    std::string value;
    TokenType type;
    void operator=(const Token& other){
        this->value = other.value;
        this->type = other.type;
    };
    virtual ~Token() = default;
};

#endif