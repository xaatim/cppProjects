#include <cstdlib>
#include <iostream>
#include <stack>
#include <tuple>

std::tuple<char, int> expressionChecker(std::string userInput) {
  if (userInput.find('+',1) < userInput.length()) {
    return std::make_tuple('+', userInput.find('+',1));
  }
  if (userInput.find('-',1) < userInput.length()) {
    return std::make_tuple('-', userInput.find('-',1));
  }
  if (userInput.find('/',1) < userInput.length()) {
    return std::make_tuple('/', userInput.find('/',1));
  }
  if (userInput.find('*',1) < userInput.length()) {
    return std::make_tuple('*', userInput.find('*',1));
  }
  return std::make_tuple(' ', -1);
}

bool validateInput(std::string userInput) {
  for (int i = 0; i < userInput.length(); i++) {
    if (userInput[i] == '+' || userInput[i] == '-' || userInput[i] == '/' ||
        userInput[i] == '*' || userInput[i]=='.') {
      continue;
    }

    // if (atoi(userInput[i]) == 0) {
    // std::cout << "unkown varialbe: " << "\"" << userInput[i]<< "\"" <<
    // std::endl; return true;

    // }
    if (!std::isdigit(userInput[i])) {
      std::cout << "unkown varialbe: " << "\"" << userInput[i] << "\""
                << std::endl;
      return true;
    }
  }
  return false;
}

int main() {
  std::stack<double> numSt;
  double firstOperand = 0;
  double secondOperand = 0;
  double result;

  int expressionDigit;
  char expressionType;

  std::string charsBeforeOperator;
  std::string charsAfterOperator;
  std::string userInput;

  std::cout << "expression calculator: ";
  std::cin >> userInput;

  if (!validateInput(userInput)) {
    std::tie(expressionType, expressionDigit) = expressionChecker(userInput);
    std::cout << "expressionDigit: " << expressionDigit << std::endl;
    std::cout << "expressionType : " << expressionType << std::endl;

    if (expressionDigit == -1) {
      result = stod(userInput);
      std::cout << "restult: " << result << std::endl;
      return 0;
    }
    for (int i = 0; i < expressionDigit; i++) {
      charsBeforeOperator += userInput[i];
    }
    numSt.push(std::stod(charsBeforeOperator));

    std::cout << "charsBeforeOperator: " << charsBeforeOperator << std::endl;

    for (int i = expressionDigit + 1; i < userInput.length(); i++) {
      charsAfterOperator += userInput[i];
    }

    numSt.push(std::stod(charsAfterOperator));
    std::cout << "charsAfterOperator: " << charsAfterOperator << std::endl;

    switch (expressionType) {
      case '+':
        secondOperand = numSt.top();
        numSt.pop();
        firstOperand = numSt.top();
        result = firstOperand + secondOperand;
        std::cout << "restult: " << result << std::endl;
        break;

      case '-':
        secondOperand = numSt.top();
        numSt.pop();
        firstOperand = numSt.top();
        result = firstOperand - secondOperand;
        std::cout << "restult: " << result << std::endl;
        break;

      case '/':
        secondOperand = numSt.top();
        numSt.pop();
        firstOperand = numSt.top();
        result = firstOperand / secondOperand;
        std::cout << "restult: " << result << std::endl;
        break;

      case '*':
        secondOperand = numSt.top();
        numSt.pop();
        firstOperand = numSt.top();
        result = firstOperand * secondOperand;
        std::cout << "restult: " << result << std::endl;
        break;

      default:
        std::cout << "unkown variable:" << std::endl;
        break;
    }
    return 0;
  }
}