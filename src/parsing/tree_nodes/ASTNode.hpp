#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <vector>
#include "../../lexer/tokens/Token.hpp"

class ASTNode {
    private:
        ASTNode *left;
        ASTNode *right;
        Token op;
    public:
        ASTNode(Token op);
        ASTNode(Token op, ASTNode* left, ASTNode* right);
        void addChild(ASTNode* child);
        void setOp(Token op);
        Token getOp();
        ASTNode* getLeft();
        ASTNode* getRight();
        std::string toString();
        ~ASTNode();
};

#endif