#include "Lexer.hpp"
#include <vector>
#include <regex>
#include "tokens/Token.hpp"
#include <iostream>

/**
 * @brief Initialize the Lexer object
 * 
 * Initializes the token regexes vector with the regexes for each token type
 * 
 * @see TokenType
 * @see Token
 */
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

/**
 * @brief Construct a new Lexer:: Lexer object
 * 
 * Creates a new Lexer object with the input set to `input` and the position set to 0
 * 
 * @param[in] input The string to tokenize
 */
Lexer::Lexer(std::string input){
    init();
    this->input = input;
    this->position = 0;
}

/**
 * @brief Construct a new Lexer:: Lexer object
 * 
 * Creates a new Lexer object with the input set to an empty string and the position set to 0
 */
Lexer::Lexer(){
    init();
}

/**
 * @brief Set the input string
 * 
 * Sets the input string to `input` and the position to 0
 * 
 * @param[in] input The string to tokenize
 */
void Lexer::setInput(std::string input){
    this->input = input;
    this->position = 0;
}

/**
 * @brief Get the next token from the input string
 * 
 * Loops through the token regexes and tries to match the input string with each regex,
 * if a match is found, the token text is stored in `tokenText`, the input string is updated
 * to the suffix of the match, and the token type is returned
 * 
 * @return Token The next token in the input string
 */
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

/**
 * @brief Check if there are more tokens in the input string
 * 
 * @return true If there are more tokens in the input string
 * @return false If there are no more tokens in the input string
 */
bool Lexer::hasNextToken(){
    return input.length() > 0;
}


