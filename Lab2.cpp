#include <iostream>
#include "StackMachine.h"
#include "Binnum.h"
using T = char;

int main(int argc, char* argv[]) {
    string s;
    vector<string> v;
    cout << "Enter expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> s;
        v.push_back(s);
    }
    try {
        auto* machine = new StackMachine<T>(v);
        Binnum<T> result = machine->evaluate();

        cout << "Result: " << result << endl;
        cout << "Result (dec): " << +result.to_dec();

        cout << endl;
    }
    catch (std::exception& e) {
        cout << "Smth is wrong with your expression" << endl;
    }
}
