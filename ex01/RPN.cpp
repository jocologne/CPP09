
#include "RPN.hpp"

RPN::RPN() : _expression("") {}

RPN::RPN(const std::string& expression) : _expression(expression) {}

RPN::RPN(const RPN& other) : _expression(other._expression) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _expression = other._expression;
    }
    return *this;
}

RPN::~RPN() {}

void RPN::setExpression(const std::string& expression) {
    _expression = expression;
}

static bool isOperator(const std::string& token) {
    if (token == "+" || token == "-" || token == "*" || token == "/")
        return true;
    return false;
}

static bool isNumber(const std::string& token) {
    if (token.length() != 1)
        return false;
    return(isdigit(token[0]));
}

static int performOperation(int a, int b, const std::string& op) {
    if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "*")
        return a * b;
    else if (op == "/") {
        if (b == 0)
            throw std::runtime_error("Error: division by zero");
        return a / b;
    }
    throw std::runtime_error("Error: unknown operator");
}

int RPN::calculate() {
    std::stack<int> stack;
    std::istringstream iss(_expression);
    std::string token;
    while (iss >> token) {
        if (isNumber(token)) {
            int num = std::atoi(token.c_str());
            stack.push(num);
        }
        else if (isOperator(token)) {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            int result = performOperation(a, b, token);
            stack.push(result);
        }
        else {
            throw std::runtime_error("Error");
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
}
