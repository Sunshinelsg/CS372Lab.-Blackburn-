#include <iostream>
#include <cctype>     // Provides isdigit()
#include <cstring>    // For strchr()
#include <stack>      // Let's use the STL stack

using namespace std;
double readAndEvaluate(istream &ins);
void evaluateStackTops(stack<double> &numbers,
                       stack<char>  &ops);
int main() {
  double answer = 0;
    cout << "Type a fully parenthsized expression" << endl;
    answer = readAndEvaluate(cin);
    cout << "That evaluates to " << answer << endl;
    return 0;
}

double readAndEvaluate(istream &ins) {
 const char DECIMAL = '.';
 const char RIGHTPAREN = ')';
 stack<double> numbers;
 stack<char> operations;
 double number;
 char symbol;
 while (ins && ins.peek() != '\n') {
  if (isdigit(ins.peek()) || (ins.peek() == DECIMAL)) {
    ins >> number;
    numbers.push(number);
  }
  else if (strchr("+-*/", ins.peek()) != NULL) {
    ins >> symbol;
    operations.push(symbol);
  }
  else if (ins.peek() == RIGHTPAREN) {
    ins.ignore();
    evaluateStackTops(numbers, operations);
  }
  else {
    ins.ignore();
  }
 }
 return numbers.top();
}

void evaluateStackTops(stack<double>& numbers, 
                       stack<char>& operations) {
  double op1, op2;
  op2 = numbers.top();
  numbers.pop();
  op1 = numbers.top();
  numbers.pop();
  switch (operations.top()) {
      case '+': numbers.push(op1 + op2);
                break;
      case '-': numbers.push(op1 - op2);
                break;
      case '*': numbers.push(op1 * op2);
                break;
      case '/': numbers.push(op1 / op2);
                break;
  }
  operations.pop();
}
