// TODO: Implement this source file
#include "MyString.h"
#include <iostream>
#include <fstream>
using namespace std;

MyString::MyString() {
    stringSize = 0;
    stringCapacity = 0;
    stringList = new char[1] {'\0'};
}

MyString::MyString(const MyString& str) {
    stringSize = str.size();
    stringCapacity = str.capacity();
    stringList = new char[stringCapacity];
    for (size_t i = 0; i < stringSize; i++) {
        stringList[i] = str.at(i);
    }
    stringList[stringSize] = '\0';
}

MyString::MyString(const char* s) {
    stringSize = 0;
    for (size_t i = 1; s[i-1] != '\0'; i++) {
        stringSize = i;
    }

    stringCapacity = 1;
    while (stringSize > stringCapacity) {
        stringCapacity *= 2;
    }
    stringList = new char[stringCapacity];
    for (size_t i = 0; i < stringSize + 1; i++) {
        stringList[i] = s[i];
    }
}

MyString::~MyString() {
    delete[] stringList;
    stringList = nullptr;
    stringSize = 0;
    stringCapacity = 0;
}

void MyString::resize() {
    // stringSize = n;
    // stringCapacity = 1; 
    // while (stringSize > stringCapacity) {
    //     stringCapacity *= 2;
    // }

    stringCapacity *= 2;
    char* tempList = new char[stringCapacity];
    for (size_t i = 0; i < stringSize; i++) {
        tempList[i] = stringList[i];
    }
    delete[] stringList;
    stringList = tempList;
    tempList = nullptr;

    // char* tempList = stringList;
    // delete[] stringList;
    // stringList = new char[stringCapacity];
    // for (size_t i = 0; i < stringSize; i++) {
    //     stringList[i] = tempList[i];
    // }
}

size_t MyString::capacity() const {
    return stringCapacity;
}

size_t MyString::size() const {
    return stringSize;
}

size_t MyString::length() const {
    return stringSize;
}

const char* MyString::data() const {
    return stringList;
}

bool MyString::empty() const {
    bool is_empty = false;
    if (stringSize == 0) {
        is_empty = true;
    }
    return is_empty;
}

const char& MyString::front() const {
    return stringList[0];
}

const char& MyString::at(size_t pos) const {
    if (pos >= stringSize) {
        throw std::out_of_range("at: out of range");
    }
    return stringList[pos];
}

void MyString::clear() {
    if (stringList != nullptr) {
        delete[] stringList;
    }
    stringList = new char[1] {'\0'};
    stringSize = 0;
    stringCapacity = 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& myStr) {
    for (size_t i = 0; i < myStr.size(); i++) {
        os << myStr.at(i);
    }
    return os;
}

MyString& MyString::operator=(const MyString& myStr) {
    stringSize = myStr.size();
    stringCapacity = myStr.capacity();
    if (stringList != nullptr) {
        delete[] stringList; 
    }
    stringList = new char[stringCapacity];
    for (size_t i = 0; i < stringSize; i++) {
        stringList[i] = myStr.at(i);
    }
    stringList[stringSize] = '\0';
    return *this;
}

MyString& MyString::operator+=(const MyString& myStr) {
    for (size_t i = 0; i < myStr.size(); i++) {
        push_back(myStr.at(i));
    }
    return *this;
}

size_t MyString::find(const MyString& str, size_t pos) const {
    size_t location = -1;
    for (size_t i = pos; i <= stringSize - str.size(); i++) {
        size_t charsCorrect = 0;
        size_t strIdx = i;
        for (size_t j = 0; j < str.size(); j++) {
            if (stringList[strIdx] == str.at(j)) {
                charsCorrect += 1;
            }
            strIdx += 1;
        }
        if (charsCorrect == str.size()) {
            location = i;
            break;
        }
    }
    return location;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    bool equal = true;
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++) {
        if (lhs.at(i) != rhs.at(i)) {
            equal = false;
            break;
        }
    }
    return equal;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString newString;
    newString.stringSize = lhs.size() + rhs.size();

    newString.stringCapacity = 1; 
    while (newString.stringSize > newString.stringCapacity) {
        newString.stringCapacity *= 2;
    }
    if (newString.stringList != nullptr) {
        delete[] newString.stringList;
    }
    newString.stringList = new char[newString.stringCapacity];
    for (size_t i = 0; i < lhs.size(); i++) {
        newString.stringList[i] = lhs.at(i);
    }
    for (size_t i = 0; i < rhs.size(); i++) {
        newString.stringList[lhs.size() + i] = rhs.at(i);
    }
    newString.stringList[lhs.size() + rhs.size()] = '\0';
    return newString;
}

void MyString::push_back(const char letter) {
    if (stringSize == stringCapacity) {
        resize(); //fixes capacity
    }
    stringList[stringSize] = letter;
    stringSize += 1;
}