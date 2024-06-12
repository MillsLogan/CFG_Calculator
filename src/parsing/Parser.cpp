#include "Parser.hpp"
#include "../lexer/tokens/Token.hpp"
#include "../lexer/tokens/TokenType.hpp"
#include <iostream>
#include "tree_nodes/ASTNode.hpp"

using namespace std;

Parser::Parser(Lexer* lexer){
    /**
     * @brief Construct a new Parser:: Parser object
     */
    this->lexer = lexer;
    this->currentToken = this->getNextToken();
}

ASTNode* Parser::parse(){
    ASTNode* expression = this->createExpression();
    cout << "Parsed expression: " << expression->toString() << endl;
    return expression;
}

void Parser::eat(TokenType type){
    if(this->currentToken.getType() == type){
        this->currentToken = this->getNextToken();
    } else {
        cout << "Unexpected token: " << this->currentToken.getValue() << endl;
        exit(0);
    }
}

ASTNode* Parser::createExpression(){
    ASTNode* node = this->createTerm();

    while(currentToken.getType() == TokenType::ADDOPS){
        Token token = this->currentToken;
        this->eat(TokenType::ADDOPS);
        node = new ASTNode(token, node, this->createTerm());
    }

    return node;
}

ASTNode* Parser::createTerm(){
    ASTNode* term = this->createFactor();

    while(currentToken.getType() == TokenType::MULOPS){
        Token token = this->currentToken;
        this->eat(TokenType::MULOPS);
        term = new ASTNode(token, term, this->createFactor());    
    }

    return term;
}

ASTNode* Parser::createFactor(){
    return this->createPrimary();
}

ASTNode* Parser::createPrimary(){
    Token token = this->currentToken;
    if(token.getType() == TokenType::NUMBER){
        this->eat(TokenType::NUMBER);

        return new ASTNode(token);
    } else if(token.getType() == TokenType::LPAREN){
        this->eat(TokenType::LPAREN);
        ASTNode* node = this->createExpression();
        this->eat(TokenType::RPAREN);

        return node;
    } else {
        cout << "Unexpected token: " << token.getValue() << endl;
        exit(0);
    }
}

Token Parser::getNextToken(){
    Token token = this->lexer->getNextToken();
    if(token.getType() == TokenType::UNKNOWN){
        cout << "Unknown token found: " << token.getValue() << endl;
        exit(0);
    }

    if(token.getType() != TokenType::WHITESPACE){
        return token;
    } else {
        return this->getNextToken();
    }
}