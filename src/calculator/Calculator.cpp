#include "Calculator.hpp"
#include "../parsing/tree_nodes/ASTNode.hpp"
#include <iostream>

Calculator::Calculator(){
    result = 0;
    variables["pi"] = 3.14159265359;
    variables["e"] = 2.71828182846;
}

double Calculator::calculate(ASTNode* root){
    double result = this->visit(root);
    return result;
}

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

double Calculator::setIdentifier(ASTNode* left, double right){
    if(left->getOp().type != TokenType::IDENTIFIER){
        std::cout << "Left side of assignment must be an identifier!" << std::endl;
        return 0;
    }

    variables[left->getOp().value] = right;
    return right;
}

double Calculator::resolveUnaryNode(ASTNode* node){
    double left = this->visit(node->getLeft());
    if(node->getOp().value == "sqrt"){

        return sqrt(left);
    }
    return 0;
}

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