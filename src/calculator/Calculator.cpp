#include "Calculator.hpp"
#include "../parsing/tree_nodes/ASTNode.hpp"

Calculator::Calculator(){
    result = 0;
}

double Calculator::calculate(ASTNode* root){
    return this->visit(root);
}

double Calculator::visit(ASTNode* node){
    if(node->getLeft() == nullptr && node->getRight() == nullptr){
        result = stod(node->getOp().getValue()); // Convert string to double
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