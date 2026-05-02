#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>

int checkPrecedence(char op) {
  switch (op) {
    case '-':
      return 1;
      break;

    case '+':
      return 1;
      break;

    case '*':
      return 2;
      break;

    case '/':
      return 2;
      break;

    case '^':
      return 3;
      break;

    default:
      break;
  }
  return 0;
}

void expressionChecker(std::string userInput,
                       std::queue<std::string>& outputQueue,
                       std::stack<char>& operatorStack) {
  std::string tempNumBuff;
  char tempCharBuff;
  char prevChar = '\0';

  for (long unsigned int i = 0; i < userInput.length(); i++) {
    if (isdigit(userInput[i]) || userInput[i] == '.') {
      tempNumBuff += userInput[i];
    }
    if (!isdigit(userInput[i]) && userInput[i] != '.') {
      if (prevChar == '\0' && !isdigit(userInput[i])) {
        tempNumBuff += userInput[i];
        continue;
      }

      if (!tempNumBuff.empty()) {
        outputQueue.push(tempNumBuff);
        tempNumBuff.clear();
      }

      while (!operatorStack.empty() && checkPrecedence(operatorStack.top()) >=
                                           checkPrecedence(userInput[i])) {
        // if (prevChar == '\0'){
        //   operatorStack.push(userInput[i]);
        // }

        if ((userInput[i] == operatorStack.top()) ||
            (std::string(1, userInput[i]) == outputQueue.front() &&
             userInput[i] != '^')) {
          std::cout << "2 similar operators" << std::endl;
          break;
        }

        tempCharBuff = operatorStack.top();
        operatorStack.pop();
        outputQueue.push(std::string(1, tempCharBuff));
      }

      operatorStack.push(userInput[i]);
    }
    prevChar = userInput[i];
  }
  if (!tempNumBuff.empty()) {
    outputQueue.push(tempNumBuff);
    tempNumBuff.clear();
  }

  while (!operatorStack.empty()) {
    outputQueue.push(std::string(1, operatorStack.top()));
    operatorStack.pop();
  }
}

bool validateInput(std::string userInput) {
  for (long unsigned int i = 0; i < userInput.length(); i++) {
    if (userInput[i] == '+' || userInput[i] == '-' || userInput[i] == '/' ||
        userInput[i] == '*' || userInput[i] == '.' || userInput[i] == '^') {
      continue;
    }

    if (!std::isdigit(userInput[i])) {
      std::cout << "unkown varialbe: " << "\"" << userInput[i] << "\""
                << std::endl;
      return false;
    }
  }
  return true;
}

int main() {
  std::stack<char> operatorStack;
  std::stack<double> solveStack;
  std::queue<std::string> outputQueue;
  std::string userInput;

  std::cout << "expression calculator: ";
  std::cin >> userInput;

  if (validateInput(userInput)) {
    expressionChecker(userInput, outputQueue, operatorStack);
    while (!outputQueue.empty()) {
      std::string token = outputQueue.front();
      outputQueue.pop();
      if (isdigit(token[0]) ||
          ((token[0] == '-' || token[0] == '+') && token.length() > 1)) {
        solveStack.push(stod(token));
      } else {
        if (!solveStack.empty()) {
          double secondOperand = solveStack.top();
          solveStack.pop();
          double firstOperand = solveStack.top();
          solveStack.pop();
          double result;

          switch (token[0]) {
            case '+':
              result = firstOperand + secondOperand;
              solveStack.push(result);
              break;

            case '-':
              result = firstOperand - secondOperand;
              solveStack.push(result);
              break;

            case '/':
              if (secondOperand == 0) {
                std::cout << "Division by zero is undefined" << std::endl;
                return 0;
              }
              result = firstOperand / secondOperand;
              solveStack.push(result);
              break;

            case '*':
              result = firstOperand * secondOperand;
              solveStack.push(result);
              break;

            case '^':
              result = pow(firstOperand, secondOperand);
              solveStack.push(result);
              break;

            default:
              std::cout << "unkown variable:" << std::endl;
              break;
          }
        }
      }
    }
  }
  if (!solveStack.empty()) {
    std::cout << "result: " << solveStack.top() << std::endl;
  }
  return 0;
}