#include "Lexer.hpp"
#include <vector>
#include <regex>
#include "tokens/Token.hpp"
#include <iostream>

void Lexer::init(){
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^([\\d]+([\\.][\\d]+)?)"), TokenType::LITERAL));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^(sqrt)"), TokenType::UNARYOPS));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^([a-zA-Z]+)"), TokenType::IDENTIFIER));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^(=)"), TokenType::EQUALS));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^([\\+\\-])"), TokenType::ADDOPS));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^([\\*\\/])"), TokenType::MULOPS));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^([\\^])"), TokenType::EXPONENT));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^(\\()"), TokenType::LPAREN));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^(\\))"), TokenType::RPAREN));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex("^(\\s+)"), TokenType::WHITESPACE));
    token_regexes.push_back(std::pair<std::regex, TokenType>(std::regex(".{1}"), TokenType::UNKNOWN));
}

Lexer::Lexer(std::string input){
    init();
    this->input = input;
    this->position = 0;
}

Lexer::Lexer(){
    init();
}

void Lexer::setInput(std::string input){
    this->input = input;
    this->position = 0;
}

Token Lexer::getNextToken(){
    for(const std::pair <std::regex, TokenType> &it : token_regexes){
        std::regex regex = it.first;
        TokenType type = it.second;

        std::smatch match;
        if(std::regex_search(input, match, regex)){
            std::string tokenText = match.str();
            input = match.suffix();
            if(type == WHITESPACE){
                return getNextToken();
            }
            return Token(tokenText, type);
        }
    }
    return Token("", END);
}

bool Lexer::hasNextToken(){
    return input.length() > 0;
}


