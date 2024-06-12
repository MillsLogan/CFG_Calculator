#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP
#include <stack>
#include <string>

enum TokenType {
    NUMBER,
    IDENTIFIER,
    ADDOPS,
    MULOPS,
    LPAREN,
    RPAREN,
    END,
    UNKNOWN,
    WHITESPACE
};

#endif
