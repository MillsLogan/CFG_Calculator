#include "Calculator.hpp"
#include "../parsing/tree_nodes/ASTNode.hpp"
#include <iostream>

Calculator::Calculator(){
    result = 0;
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
        if(node->getOp().value == "pi"){
            return 3.14159265359;
        } else if(node->getOp().value == "e"){
            return 2.71828182846;
        }else if(node->getOp().value == "ans"){
            return result;
        }
    }
    return 0;
}