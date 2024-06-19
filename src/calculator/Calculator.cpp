#include "Calculator.hpp"
#include "../parsing/tree_nodes/ASTNode.hpp"
#include <iostream>

/**
 * @brief Construct a new Calculator:: Calculator object
 * 
 * Initializes the result to 0 and sets the values of pi and e in the variables map
 * 
 * @see variables
 */
Calculator::Calculator(){
    result = 0;
    variables["pi"] = 3.14159265359;
    variables["e"] = 2.71828182846;
}

/**
 * @brief Calculate the result of the expression represented by the AST
 * 
 * Calls the `visit` function with the root node of the AST and returns the result
 * 
 * @param[in] root The root node of the AST
 * @return double The result of the expression
 * 
 * @see visit
 */
double Calculator::calculate(ASTNode* root){
    double result = this->visit(root);
    return result;
}

/**
 * @brief Visit a node in the AST and calculate the result
 * 
 * Visits a node in the AST and calculates the result of the expression represented by the AST
 * 
 * @param[in] node The node to visit
 * @return double The result of the expression
 */
double Calculator::visit(ASTNode* node){
    if(node->getLeft() == nullptr && node->getRight() == nullptr){
        result = this->resolveTerminalNode(node);
    } else if(node->getLeft() != nullptr && node->getRight() == nullptr){
        result = this->resolveUnaryNode(node);
    }else {
        if(node->getOp().value == "="){
            result = this->setIdentifier(node->getLeft(), this->visit(node->getRight()));
        }

        double left = this->visit(node->getLeft());
        double right = this->visit(node->getRight());

        if(node->getOp().value == "+"){
            result = left + right;
        } else if(node->getOp().value == "-"){
            result = left - right;
        } else if(node->getOp().value == "*"){
            result = left * right;
        } else if(node->getOp().value == "/"){
            result = left / right;
        } else if(node->getOp().value == "^"){
            result = pow(left, right);
        }
    }
    return result;
}

std::unordered_map<std::string, double> Calculator::getVariables(){
    return variables;
}

/**
 * @brief Sets the value of an identifier in the variables map
 * 
 * Sets the value of an identifier in the variables map
 * 
 * @param[in] left The left side of the assignment
 * @param[in] right The right side of the assignment
 * @return double The value of the right side of the assignment
 */
double Calculator::setIdentifier(ASTNode* left, double right){
    if(left->getOp().type != TokenType::IDENTIFIER){
        std::cout << "Left side of assignment must be an identifier!" << std::endl;
        return 0;
    }

    variables[left->getOp().value] = right;
    return right;
}

/**
 * @brief Resolves a unary node of the AST
 * 
 * Resolves a unary node of the AST by checking if the operator is a unary operator, if it is, it returns the result of the unary operation
 * 
 * @param node 
 * @return double 
 */
double Calculator::resolveUnaryNode(ASTNode* node){
    double left = this->visit(node->getLeft());
    if(node->getOp().value == "sqrt"){

        return sqrt(left);
    }
    return 0;
}

/**
 * @brief Resolves a terminal node of the AST
 * 
 * Resolves a terminal node of the AST by checking if the operator is a LITERAL or IDENTIFIER token,
 * if it is a LITERAL token, it returns the value of the token as a double, if it is an IDENTIFIER token, 
 * 
 * @param node 
 * @return double 
 */
double Calculator::resolveTerminalNode(ASTNode* node){
    if(node->getOp().type == TokenType::LITERAL){
        return stod(node->getOp().value);
    } else if(node->getOp().type == TokenType::IDENTIFIER){
        if(node->getOp().value == "ans"){
            return result;
        }else if(variables.find(node->getOp().value) != variables.end()){
            return variables[node->getOp().value];
        }else{
            std::cout << "Variable " << node->getOp().value << " not found!" << std::endl;
            return 0;
        }
    }
    return 0;
}

