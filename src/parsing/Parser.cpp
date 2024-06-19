#include "Parser.hpp"
#include "../lexer/tokens/Token.hpp"
#include <iostream>
#include "tree_nodes/ASTNode.hpp"

using namespace std;

/**
 * @brief Construct a new Parser:: Parser object
 * 
 * @param `Lexer` lexer 
 * 
 * @see Lexer
 */
Parser::Parser(Lexer* lexer){
    this->lexer = lexer;
}

/**
 * @brief Creates an Abstract Syntax Tree (AST) from `expression` and returns the root node of the AST
 * 
 * Sets the input of the lexer to the expression and gets the first token from the lexer,
 * then calls the `parse` function with no arguments to start the parsing process
 * 
 * @param[in] expression A string expression to parse
 * @return ASTNode* - The root node of the AST
 * 
 * @see parse
 * @see Lexer::setInput
 * @see Lexer::getNextToken
 * @see ASTNode
 * 
 * @note This function is used to parse an expression from the command line
 */
ASTNode* Parser::parse(std::string expression){
    this->lexer->setInput(expression);
    this->currentToken = this->lexer->getNextToken();
    return this->parse();
}

/**
 * @brief Creates an Abstract Syntax Tree (AST) from the input of the lexer and returns the root node of the AST
 * 
 * Calls the `createExpression` function to create the root node of the AST, then recursively creates the rest of the AST
 * until the end of the input is reached, and returns the root node of the AST. The root node is then printed to the console,
 * displaying the parsed expression to the user, with parentheses around each node to show the structure of the AST
 * 
 * @return ASTNode*
 * 
 * @see createExpression
 * @see ASTNode
 * 
 * @note This function is used to parse an expression from the command line
 */
ASTNode* Parser::parse(){
    ASTNode* expression = this->createExpression();
    cout << "Parsed expression: " << expression->toString() << endl;
    return expression;
}

/**
 * @brief Destroys the current token and gets the next token from the lexer, verifying the current token is of the expected type
 * 
 * Destroys the current token and gets the next token from the lexer, then checks if the current token is of the expected type,
 * if it is not, an error message is printed to the console and the program exits. If the current token is of the expected type,
 * the function continues, otherwise, the program exits. This will also set the current token to the end token if there are no more tokens,
 * to signal the end of the input
 * 
 * @param[in] type The expected `TokenType` of the current token
 * 
 * @see TokenType
 * @see Token
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
 * @brief Creates an expression node
 * 
 * Creates an expression node, which will either be a term node or an expression node with an operator,
 * and another expression node, valid operators are ADDOPS and EQUALS, which are used to create the ASTNode
 * 
 * @return ASTNode* 
 * 
 * @see createTerm
 * @see ASTNode
 */
ASTNode* Parser::createExpression(){
    ASTNode* node = this->createTerm();

    while(currentToken.type == TokenType::ADDOPS){
        Token token = this->currentToken;
        this->eat(TokenType::ADDOPS);
        node = new ASTNode(token, node, this->createTerm());
    }

    if(this->currentToken.type == TokenType::EQUALS){
        Token token = this->currentToken;
        this->eat(TokenType::EQUALS);
        node = new ASTNode(token, node, this->createExpression());
    }

    return node;
}

/**
 * @brief Creates a term node, which is a node with a MULOP operator and two factor nodes as children,
 * if no MULOP operator is found, it returns the factor node.
 * 
 * Creates a term node by creating a factor node and then checking if the current token is a MULOPS token
 * If it is, it creates a new ASTNode with the current token as the operator and the left child as the current node
 * and the right child as the result of calling createFactor
 * 
 * This process is repeated until there are no more MULOPS tokens
 * 
 * @return ASTNode*
 * 
 * @see createFactor
 * @see ASTNode
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
 * @brief Create a factor node
 * 
 * Creates a factor node by creating a primary node and then checking if the current token is an EXPONENT token,
 * if it is, it creates a new ASTNode with the current token as the operator and the left child as the current node
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
 * @brief Create a primary node
 * 
 * Creates a primary node by checking the current token type, if it is a LITERAL, LPAREN, or IDENTIFIER token,
 * it creates a new ASTNode with the current token, if it is a UNARYOPS token, it creates a new ASTNode with the current token
 * and the result of calling createPrimary as the left child, and nullptr as the right child. If the current token is a LPAREN,
 * it calls eat with the LPAREN token, then creates a new ASTNode with the result of calling createExpression, if the next token is
 * not a RPAREN an error message will raise in the eat function
 * 
 * @return ASTNode* 
 * 
 * @see eat
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
     * 
     * Deletes the lexer object
     * 
     * @see Lexer
     */
    delete this->lexer;
}