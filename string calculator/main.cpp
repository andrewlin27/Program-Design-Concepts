#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI
    string lhs;
    string operation;
    string rhs;
    cout << ">> ";
    cin >> lhs;
    if (lhs=="q" || lhs=="quit") {
        cout << "\n" << "farvel!" << endl << "\n";
        return 0;
    }
    cin >> operation >> rhs;
    cout << "\n";
    while (true) {
        cout << "ans =" << endl << "\n    ";
        if (operation=="+") {
            cout<<add(lhs, rhs)<<endl;
        }
        else if (operation=="*") {
            cout<<multiply(lhs, rhs)<<endl; 
        }
        cout<<"\n>> ";
        cin >> lhs;
        if (lhs=="q" || lhs=="quit") {
            cout << "\n" << "farvel!" << endl << "\n";
            return 0;
        }
        cin >> operation >> rhs;
        cout << "\n";
    }
    return 0;
}

