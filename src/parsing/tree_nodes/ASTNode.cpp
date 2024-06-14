#include "ASTNode.hpp"
#include "../../lexer/tokens/Token.hpp"
#include "../../lexer/tokens/TokenType.hpp"

ASTNode::ASTNode(Token op){
    this->left = nullptr;
    this->right = nullptr;
    this->op = op;
}

ASTNode::ASTNode(Token op, ASTNode* left, ASTNode* right){
    this->left = left;
    this->right = right;
    this->op = op;
}

void ASTNode::addChild(ASTNode* child){
    if(this->left == nullptr){
        this->left = child;
    } else if(this->right == nullptr){
        this->right = child;
    }
}

void ASTNode::setOp(Token op){
    this->op = op;
}

Token ASTNode::getOp(){
    return this->op;
}

ASTNode* ASTNode::getLeft(){
    return this->left;
}

ASTNode* ASTNode::getRight(){
    return this->right;
}

std::string ASTNode::toString(){
    if(this->left == nullptr && this->right == nullptr){
        return this->op.getValue();
    } else {
        return "(" + this->left->toString() + this->op.getValue() + this->right->toString() + ")";
    }
}

ASTNode::~ASTNode(){
    delete this->left;
    delete this->right;
}

