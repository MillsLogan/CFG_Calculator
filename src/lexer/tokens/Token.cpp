#include "Token.hpp"
#include "TokenType.hpp"

Token::Token(std::string value, TokenType type){
    this->value = value;
    this->type = type;
}

Token::Token(){
    this->value = "";
    this->type = TokenType::UNKNOWN;
}

std::string Token::getValue() const{
    return this->value;
}

TokenType Token::getType() const{
    return this->type;
}