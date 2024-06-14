#include "Calculator.hpp"
#include "../parsing/tree_nodes/ASTNode.hpp"

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
    } else {
        double left = this->visit(node->getLeft());
        double right = this->visit(node->getRight());
        if(node->getOp().getValue() == "+"){
            result = left + right;
        } else if(node->getOp().getValue() == "-"){
            result = left - right;
        } else if(node->getOp().getValue() == "*"){
            result = left * right;
        } else if(node->getOp().getValue() == "/"){
            result = left / right;
        }
    }
    return result;
}

double Calculator::resolveTerminalNode(ASTNode* node){
    if(node->getOp().getType() == TokenType::NUMBER){
        return stod(node->getOp().getValue());
    } else if(node->getOp().getType() == TokenType::IDENTIFIER){
        if(node->getOp().getValue() == "pi"){
            return 3.14159265359;
        } else if(node->getOp().getValue() == "e"){
            return 2.71828182846;
        }else if(node->getOp().getValue() == "ans"){
            return result;
        }
    }
    return 0;
}