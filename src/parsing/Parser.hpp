#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <stack>
#include "../lexer/tokens/Token.hpp"
#include "../lexer/Lexer.hpp"
#include "tree_nodes/ASTNode.hpp"

class Parser {
    private:
        Lexer* lexer;
        Token currentToken;
    public:
        Parser(Lexer* lexer);
        ASTNode* parse();
        ASTNode* createExpression();
        ASTNode* createTerm();
        ASTNode* createFactor();
        ASTNode* createPrimary();
        void eat(TokenType type);
        ASTNode* parse(std::string expression);
        ~Parser();
};

#endif