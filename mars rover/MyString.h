// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <fstream>
using namespace std;

class MyString {
    private:
        size_t stringSize = 0;
        size_t stringCapacity = 0;
        char* stringList = nullptr;
    public:
        // default constructor, empty string, length 0
        MyString();
        // copy constructor 
        MyString(const MyString& str);
        // constructor from c-string 
        MyString(const char* s);
        // deallocates capacity allocated by string
        ~MyString();
        // resize to length n
        void resize();
        // tracks current size of internal array
        size_t capacity() const;
        // return size of string in bytes
        size_t size() const;
        // return length of string in bytes
        size_t length() const;
        //returns pointer to array that contains chars
        const char* data() const;
        // return whether length is 0
        bool empty() const;
        // return reference to fist char in string
        const char& front() const;
        // check bounds and throw exception if out of bounds
        const char& at(size_t pos) const;
        // erase contents(becomes empty string with length 0)
        void clear();
        // inserts sequence of chars into stream
        friend std::ostream& operator<<(std::ostream& os, const MyString& myStr);
        // copy assignemnt operator 
        MyString& operator=(const MyString& myStr);
        // append chars to end of current string
        MyString& operator+=(const MyString& myStr);
        // returns index of MyString starting at pos
        size_t find(const MyString& str, size_t pos = 0) const;
        // compare lhs and rhs
        friend bool operator==(const MyString& lhs, const MyString& rhs);
        // return newly constructed MyString with concatenation of lhs and rhs
        friend MyString operator+(const MyString& lhs, const MyString& rhs);
        // append
        void push_back(const char letter);
};

#endif