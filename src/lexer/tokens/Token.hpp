#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <stack>
#include <string>
#include "TokenType.hpp"

class Token{
    private:
        std::string value;
        TokenType type;
    public:
        Token();
        Token(std::string value, TokenType type);
        std::string getValue() const;
        TokenType getType() const;
};

#endif