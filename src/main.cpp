#include <iostream>
#include "parsing/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "calculator/Calculator.hpp"
#include <regex>

using namespace std;
int main(){
    Calculator calculator;
    cout << "Welcome to the CFG Calculator!" << endl;
    cout << "Enter an expression to calculate" << endl;
    cout << "Type 'exit' at any time to quit" << endl;
    Parser parser(new Lexer());
    while(true){
        string expression;
        getline(cin, expression);
        if(expression == "exit"){
            break;
        }else if(expression == "vars"){
            cout << "Variables: " << endl;
            for(auto const& [key, val] : calculator.getVariables()){
                cout << key << " = " << val << endl;
            }
            continue;
        }

        ASTNode* root = parser.parse(expression);
        double result = calculator.calculate(root);
        
        delete root;
        cout << "Result: " << result << endl;
    }
}



