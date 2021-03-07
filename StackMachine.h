#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Binnum.h"
#include "Stack.h"
using namespace std;

template <typename T>
class StackMachine {
    vector<string> expression;
public:

    StackMachine(vector<string> expr) {
        expression = expr;
    }

    bool isOperator(string& exp) {
        return (exp == "+" || exp == "-" || exp == "x");
    }

    bool isOperand(string s) {
        try {
            stoi(s);
            return true;
        }
        catch (std::exception& e) {
            return false;
        }
    }

    Binnum<T> evaluate() {
        auto* stack = new Stack<Binnum<T>>();
        for (string e : expression) {
            if (!isOperator(e)) {
                try {
                    Binnum<T> num = Binnum<T>(stoi(e));
                    cout << "Binary representation of operand: " << num;
                    cout << endl;
                    stack->push(num);
                }
                catch (std::invalid_argument& exc) {
                    throw std::invalid_argument("Invalid symbol in expression");
                }
            }
            else {
                Binnum<T> a = stack->pop();
                Binnum<T> b = stack->pop();
                Binnum<T> r;
                if (e == "+") r = a + b;
                else if (e == "-") r = b - a;
                else if (e == "x") r = a * b;
                stack->push(r);
            }

        }
        Binnum<T> result = stack->pop();
        if (!stack->empty()) {
            throw std::invalid_argument("Invalid expression");
        }
        return result;
    }
};
