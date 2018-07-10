#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

using std::cout;
using std::cin;
using std::stack;
using std::string;

/*
 * enter a string of arithemetic operation
 * print its result
 */
double toDouble(string srcStr);
double calculate(stack<double>& operands, stack<char>& operators);

int main() {
  string srcString;
  cout << "Please enter a string: ";
  std::getline(std::cin, srcString);
  double result = toDouble(srcString);
  cout << "\"" << srcString << "\" = " << result << std::endl;
}


double toDouble(string srcStr) {
  //double result = 0.0;
  stack<double> stackOfOperand;
  stack<char> stackOfOperator;
  std::stringstream ss(srcStr);
  while(!ss.eof()) {
    char c = ss.peek();
    if(isdigit(c)) {
      double operand = 0.0;
      ss >> operand;
      stackOfOperand.push(operand);
    } else {
      /*
       * if c is a right parenthesis, we pop stackOfOperator once
       * and stackOfOperand twice
       */
      if(c == ')') {
        calculate(stackOfOperand, stackOfOperator);
        //cout << "The result is " << result << std::endl;
      } else {
        if( !isspace(c) && c != '(')
          stackOfOperator.push(c);
      }
      ss.get();
    }
  }
  return stackOfOperand.top();
}

double calculate(stack<double>& operands, stack<char>& operators) {
  double rightOperand = operands.top();
  //cout << "The right operand is " << rightOperand << std::endl;
  operands.pop();
  double leftOperand = operands.top();
  //cout << "The left operand is " << leftOperand << std::endl;
  operands.pop();

  char c = operators.top();
  operators.pop();

  switch(c) {
    case '+': operands.push(leftOperand + rightOperand); return leftOperand + rightOperand;
    case '-': operands.push(leftOperand - rightOperand); return leftOperand - rightOperand;
    case '*': operands.push(leftOperand * rightOperand); return leftOperand * rightOperand;
    case '/': operands.push(leftOperand / rightOperand); return leftOperand / rightOperand;
    default: cout << "Something went wrong when calculate \"" << leftOperand << " "
                  << c << " " << rightOperand << "\"" << std::endl;
            return 0.0;
  }
}