
#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <exception>
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>

class RPN {
private:
    std::string _expression;
public:
    RPN();
    RPN(const std::string& expression);
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    void setExpression(const std::string& expression);
    int calculate();
};

#endif