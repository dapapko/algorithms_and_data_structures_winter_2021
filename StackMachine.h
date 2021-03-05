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

    void infixToRPN() {
        map<string, int> ops;
        vector<string> res;
        ops["x"] = 3;
        ops["+"] = 2; ops["-"] = 2;
        ops["("] = 1;
        Stack<string> result;
        Stack<string> operations;
        for (string value : expression) {
            if (!isOperand(value))
            {

                if (value == ")") {
                    while (operations.peek() != "(")
                    {
                        res.push_back(operations.peek());
                        operations.pop();

                    }
                    operations.pop();
                }
                else if (value == ")")
                {
                    operations.push(value);
                }
                else if (operations.empty() || (ops[operations.peek()] < ops[value]))
                {
                    operations.push(value);
                }
                else
                {
                    do
                    {
                        res.push_back(operations.pop());
                    } while (!(operations.empty() || (ops[operations.peek()] < ops[value])));
                    operations.push(value);
                }
            }
            else
            {
                res.push_back(value);
            }
        }
        while (!operations.empty())
        {
            res.push_back(operations.pop());
        }

        expression = res;
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
