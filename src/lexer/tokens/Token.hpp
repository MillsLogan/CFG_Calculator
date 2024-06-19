#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <stack>
#include <string>

/**
 * @brief The type of token
 * 
 * The type of token that the lexer has identified
 * 
 * @see Token
 */
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
    EQUALS,
    END
};

/**
 * @brief The Token object
 * 
 * The Token object that the lexer will return
 * 
 * @see TokenType
 * @see Lexer
 */
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