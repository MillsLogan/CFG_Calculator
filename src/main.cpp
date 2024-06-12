#include <iostream>
#include "parsing/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "calculator/Calculator.hpp"

using namespace std;
int main(){
    Parser parser(new Lexer("1 + 2"));
    Calculator calculator;
    while(true){
        cout << "Welcome to the CFG Calculator!" << endl;
        cout << "Enter an expression: ";
        string expression;
        getline(cin, expression);
        ASTNode* root = parser.parse(expression);
        double result = calculator.calculate(root);
        cout << "Result: " << result << endl;
        cout << "Do you want to continue? (y/n): ";
        char choice;
        cin >> choice;

        if(choice == 'n'){
            break;
        }
        
        cin.ignore();
    }
}



