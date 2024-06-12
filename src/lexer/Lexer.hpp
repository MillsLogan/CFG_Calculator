#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <regex>
#include "tokens/TokenType.hpp"
#include "tokens/Token.hpp"
#include <vector>

class Lexer {
    private:
        std::vector<std::pair <std::regex,TokenType> > token_regexes;
        std::string input;
        int position;
        void init();
    public:
        Lexer();
        Lexer(std::string input);
        void setInput(std::string input);
        Token getNextToken();
        bool hasNextToken();
};

#endif