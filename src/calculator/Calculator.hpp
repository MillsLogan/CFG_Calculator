#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "../parsing/tree_nodes/ASTNode.hpp"
#include <unordered_map>

class Calculator{
    private:
        double result;
        std::unordered_map<std::string, double> variables;
        double visit(ASTNode* node);
        double resolveTerminalNode(ASTNode* node);
        double resolveUnaryNode(ASTNode* node);
        double setIdentifier(ASTNode*, double right);
    public:
        Calculator();
        double calculate(ASTNode* root);
        std::unordered_map<std::string, double> getVariables();
};


#endif