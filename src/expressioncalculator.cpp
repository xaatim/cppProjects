#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <cmath>

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

  char finalChar;
  char tempCharBuff;
  for (int i = 0; i < userInput.length(); i++) {
    if (isdigit(userInput[i]) || userInput[i] == '.') {
      tempNumBuff += userInput[i];
    }
    if (!isdigit(userInput[i]) && userInput[i] != '.') {
      if (!tempNumBuff.empty()) {
        outputQueue.push(tempNumBuff);
        tempNumBuff.clear();
      }

      while (!operatorStack.empty() && checkPrecedence(operatorStack.top()) >=
                                           checkPrecedence(userInput[i])) {
        tempCharBuff = operatorStack.top();
        operatorStack.pop();
        outputQueue.push(std::string(1, tempCharBuff));
      }
      operatorStack.push(userInput[i]);
    }
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
  for (int i = 0; i < userInput.length(); i++) {
    if (userInput[i] == '+' || userInput[i] == '-' || userInput[i] == '/' ||
        userInput[i] == '*' || userInput[i] == '.'|| userInput[i] == '^') {
      continue;
    }

    if (!std::isdigit(userInput[i])) {
      std::cout << "unkown varialbe: " << "\"" << userInput[i] << "\""
                << std::endl;
      return true;
    }
  }
  return false;
}

int main() {
  std::stack<char> operatorStack;
  std::stack<double> solveStack;
  std::queue<std::string> outputQueue;

  double firstOperand = 0;
  double secondOperand = 0;
  double result;
  double tempIntHolder;
  std::string userInput;

  std::cout << "expression calculator: ";
  std::cin >> userInput;

  if (!validateInput(userInput)) {
    expressionChecker(userInput, outputQueue, operatorStack);
    while (!outputQueue.empty()) {
      std::string token = outputQueue.front();
      outputQueue.pop();
      if (isdigit(token[0])) {
        solveStack.push(stod(token));
      } else {
        switch (token[0]) {
          case '+':
            secondOperand = solveStack.top();
            solveStack.pop();
            firstOperand = solveStack.top();
            solveStack.pop();
            result = firstOperand + secondOperand;
            solveStack.push(result);
            break;

          case '-':
            secondOperand = solveStack.top();
            solveStack.pop();
            firstOperand = solveStack.top();
            solveStack.pop();
            result = firstOperand - secondOperand;
            solveStack.push(result);
            break;

          case '/':
            secondOperand = solveStack.top();
            solveStack.pop();
            firstOperand = solveStack.top();
            solveStack.pop();
            result = firstOperand / secondOperand;
            solveStack.push(result);
            break;

          case '*':
            secondOperand = solveStack.top();
            solveStack.pop();
            firstOperand = solveStack.top();
            solveStack.pop();
            result = firstOperand * secondOperand;
            solveStack.push(result);
            break;
          case '^':
            secondOperand = solveStack.top();
            solveStack.pop();
            firstOperand = solveStack.top();
            solveStack.pop();
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
  std::cout << "result: " << solveStack.top()<< std::endl;
  return 0;
}