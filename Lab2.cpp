#include <iostream>
#include "StackMachine.h"
#include "Binnum.h"
using T = char;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "You should specify infix (i) or prefix (p) notation" << endl;
        exit(1);
    }
    char notation = *argv[1];
    string s;
    vector<string> v;
    cout << "Enter expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> s;
        v.push_back(s);
    }
    try {
        auto* machine = new StackMachine<T>(v);
        if (notation == 'i') machine->infixToRPN();
        Binnum<T> result = machine->evaluate();

        cout << "Result: " << result << endl;
        cout << "Result (dec): " << +result.to_dec();

        cout << endl;
    }
    catch (std::exception& e) {
        cout << "Smth is wrong with your expression" << endl;
    }
}