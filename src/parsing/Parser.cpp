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

/**
 * @brief Takes a string expression and uses the lexer to tokenize it
 * and then parses the tokens into an Abstract Syntax Tree (AST) and 
 * returns the root node of the AST
 * 
 * @param string expression 
 * @return ASTNode* - The root node of the AST
 */
ASTNode* Parser::parse(std::string expression){
    this->lexer->setInput(expression);
    this->currentToken = this->getNextToken();
    return this->parse();
}

/**
 * @brief This function parses the tokens from the lexer into
 * an Abstract Syntax Tree (AST) and returns the root node of the AST
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::parse(){
    ASTNode* expression = this->createExpression();
    cout << "Parsed expression: " << expression->toString() << endl;
    return expression;
}

/**
 * @brief This function checks if the current token is of the type
 * specified in the argument and if it is, it moves to the next token
 * 
 * @param type 
 */
void Parser::eat(TokenType type){
    if(this->currentToken.getType() == type){
        this->currentToken = this->getNextToken();
    } else {
        cout << "Unexpected token: " << this->currentToken.getValue() << endl;
        exit(0);
    }
}

/**
 * @brief This function creates an expression node
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::createExpression(){
    ASTNode* node = this->createTerm();

    while(currentToken.getType() == TokenType::ADDOPS){
        Token token = this->currentToken;
        this->eat(TokenType::ADDOPS);
        node = new ASTNode(token, node, this->createTerm());
    }

    return node;
}

/**
 * @brief This function creates a term node
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::createTerm(){
    ASTNode* term = this->createFactor();

    while(currentToken.getType() == TokenType::MULOPS){
        Token token = this->currentToken;
        this->eat(TokenType::MULOPS);
        term = new ASTNode(token, term, this->createFactor());    
    }

    return term;
}

/**
 * @brief This function creates a factor node
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::createFactor(){
    return this->createPrimary();
}

/**
 * @brief This function creates a primary node
 * 
 * @return ASTNode* 
 */
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
    } else if(token.getType() == TokenType::IDENTIFIER){
        this->eat(TokenType::IDENTIFIER);
        
        return new ASTNode(token);
    }else{
        cout << "Unexpected token: " << token.getValue() << endl;
        exit(0);
    }
}

/**
 * @brief This function gets the next token from the lexer
 * and checks if the token is of type WHITESPACE and if it is
 * it gets the next token until it gets a token that is not of
 * type WHITESPACE and returns that token
 * 
 * @return Token 
 */
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

Parser::~Parser(){
    /**
     * @brief Destroy the Parser:: Parser object
     */
    delete this->lexer;
}