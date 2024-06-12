#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "../parsing/tree_nodes/ASTNode.hpp"

class Calculator{
    private:
        double result;
        double visit(ASTNode* node);
    public:
        Calculator();
        double calculate(ASTNode* root);
};


#endif