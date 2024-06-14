#include <iostream>
#include "parsing/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "calculator/Calculator.hpp"

using namespace std;
int main(){
    Parser parser(new Lexer("1 + 2"));
    Calculator calculator;
    cout << "Welcome to the CFG Calculator!" << endl;
    cout << "Enter an expression to calculate" << endl;
    cout << "Type 'exit' at any time to quit" << endl;
    while(true){
        string expression;
        getline(cin, expression);
        if(expression == "exit"){
            break;
        }

        ASTNode* root = parser.parse(expression);
        double result = calculator.calculate(root);
        
        delete root;
        cout << "Result: " << result << endl;
    }
}



