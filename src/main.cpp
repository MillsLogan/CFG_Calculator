#include <iostream>
#include "parsing/Parser.hpp"
#include "lexer/Lexer.hpp"
#include "calculator/Calculator.hpp"

using namespace std;
int main(){
    Parser parser(new Lexer("1+(2+3*4)+5"));
    cout << Calculator().calculate(parser.parse()) << endl;
}



