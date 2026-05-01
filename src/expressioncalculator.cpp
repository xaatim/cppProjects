  #include <iostream>
  #include <stack>

  char expressionChecker(std::string usrInput) {
    if (usrInput.find('+') < usrInput.length()) {
      return '+';
    }
    if (usrInput.find('-') < usrInput.length()) {
      return '-';
    }
    if (usrInput.find('/') < usrInput.length()) {
      return '/';
    }
    if (usrInput.find('*') < usrInput.length()) {
      return '*';
    }
    return ' ';
  }
  int main() {
    std::stack<int> numSt;
    int firstOperand = 0;
    int secondOperand = 0;
    double result = 0.0;

    // stack<std::string> cars;
    std::string userInput;
    std::cout << "expression calculator: ";
    std::cin >> userInput;

    for (int i = 0; i < userInput.length(); i++) {
      // std::cout << "expression: " << userInput[i] << ' ';
      if (userInput[i] != '+' && userInput[i] != '-' && userInput[i] != '/' &&
          userInput[i] != '*') {
        numSt.push(userInput[i] - 48);
      }
    }
    char expressionType = expressionChecker(userInput);
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