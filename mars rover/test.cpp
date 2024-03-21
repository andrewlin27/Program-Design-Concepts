#include <iostream>
#include "MyString.h"
using namespace std;

int main() {
    char* firstName = new char[4] {'J','o','e','\0'};
    char* lastName = new char[3] {'S','m','\0'};
    MyString one(firstName);
    MyString two(lastName);
    one += two;
    cout << one << one.size() << endl;
    return 0;
}