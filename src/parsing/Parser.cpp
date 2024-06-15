#include "Parser.hpp"
#include "../lexer/tokens/Token.hpp"
#include <iostream>
#include "tree_nodes/ASTNode.hpp"

using namespace std;

Parser::Parser(Lexer* lexer){
    /**
     * @brief Construct a new Parser:: Parser object
     */
    this->lexer = lexer;
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
    this->currentToken = this->lexer->getNextToken();
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
    if(this->currentToken.type != type){
        cout << "Unexpected token: " << this->currentToken.value << "with type: " << this->currentToken.type << endl;
        exit(0);
    }

    if(this->lexer->hasNextToken()){
        this->currentToken = this->lexer->getNextToken();
    }else{
        this->currentToken = Token("", END);
    }
}

/**
 * @brief This function creates an expression node
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::createExpression(){
    ASTNode* node = this->createTerm();

    while(currentToken.type == TokenType::ADDOPS){
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

    while(currentToken.type == TokenType::MULOPS){
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
    ASTNode* factor = this->createPrimary();
    while(this->currentToken.type == TokenType::EXPONENT){
        Token token = this->currentToken;
        this->eat(TokenType::EXPONENT);
        factor = new ASTNode(token, factor, this->createFactor());
    }
    return factor;
}

/**
 * @brief This function creates a primary node
 * 
 * @return ASTNode* 
 */
ASTNode* Parser::createPrimary(){
    Token token = this->currentToken;

    if(token.type == TokenType::LITERAL){
        this->eat(TokenType::LITERAL);

        return new ASTNode(token);
    } else if(token.type == TokenType::LPAREN){
        this->eat(TokenType::LPAREN);
        ASTNode* node = this->createExpression();
        this->eat(TokenType::RPAREN);
        return node;
    } else if(token.type == TokenType::IDENTIFIER){
        this->eat(TokenType::IDENTIFIER);
        
        return new ASTNode(token);
    }else if(token.type == TokenType::UNARYOPS){
        this->eat(TokenType::UNARYOPS);
        return new ASTNode(token, this->createPrimary(), nullptr);
    }else{
        cout << "Unexpected token: " << token.value << "with type: " << token.type << endl;
        exit(0);
    }
}

Parser::~Parser(){
    /**
     * @brief Destroy the Parser:: Parser object
     */
    delete this->lexer;
}