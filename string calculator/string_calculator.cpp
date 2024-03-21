#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    if (!(digit>=48 && digit<=57))
    {
        throw std::invalid_argument("Invalid Argument");
    }
    int decimal = digit - 48;
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (!(decimal<=9)) {
        throw std::invalid_argument("Invalid Argument");
    }
    char digit = decimal + 48;
    return digit;
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    long unsigned int numZeros = 0;
    if (num[0]=='-') {
        numZeros = 0;
        for (long unsigned int i=1; i<num.size(); ++i) {
            if (num[i]=='0') {
                numZeros += 1;
            }
            else {
                break;
            }
        }
        if ((numZeros+1)==num.size()) {
            return "0";
        }
        return "-"+num.substr(numZeros+1, num.size() - numZeros - 1);
    }
    else if (num[0]=='0') {
        numZeros = 0;
        for (long unsigned int i=0; i<num.size(); ++i) {
            if (num[i]=='0') {
                numZeros += 1;
            }
            else {
                break;
            }
        }
        if (numZeros==num.size()) {
            return "0";
        }
    }
    return num.substr(numZeros, num.size() - numZeros);
}

string add(string lhs, string rhs) {
    // TODO(student): implement
    lhs=trim_leading_zeros(lhs);
    rhs=trim_leading_zeros(rhs);
    int digitSum=0;
    string sum="";
    while (lhs.size()!=rhs.size()) { //make lhs and rhs equal lengths
        if (lhs[0]=='-' && rhs[0]=='-') {
            if (lhs.size()>rhs.size()) {
                rhs.insert(1, "0");
            }
            if (rhs.size()>lhs.size()) {
                lhs.insert(1, "0");
            }
        }
        else {
            if (lhs.size()>rhs.size()) {
                rhs.insert(0, "0");
            }
            if (rhs.size()>lhs.size()) {
                lhs.insert(0, "0");
            }
        }
    }
    if (lhs[0]=='-' && rhs[0]=='-') {
        string sum = "-";
        for (int i=(lhs.size()-1); i>=1; --i) { //loop from last index to index 1
            if (digitSum>=10) { //if need to carry over 1
                digitSum=1;
            } 
            else {
                digitSum = 0;
            }
            digitSum += (digit_to_decimal(lhs[i]) + digit_to_decimal(rhs[i])); //add digits 
            if (sum=="-") { //for first iteration
                sum.push_back(decimal_to_digit(digitSum%10));
            }
            else { //after first iteration
                string putIn = "";
                putIn+=decimal_to_digit(digitSum%10); //convert char to string
                sum.insert(1, putIn); //second argument has to be string, not char. 
            }
        }
        if (digitSum>=10) {
            sum.insert(1, "1");
        }
        return sum;
    }
    else if (lhs[0]!='-' && rhs[0]!='-') {
        string sum = "";
        for (int i=(lhs.size()-1); i>=0; --i) {
            if (digitSum>=10) {
                digitSum=1;
            } 
            else {
                digitSum = 0;
            }
            digitSum += (digit_to_decimal(lhs[i]) + digit_to_decimal(rhs[i]));
            if (sum.size()<1) { //for first iteration
                sum.push_back(decimal_to_digit(digitSum%10));
            }
            else { //after first iteration
                string putIn = "";
                putIn+=decimal_to_digit(digitSum%10); 
                sum.insert(0, putIn);  
            }
        }
        if (digitSum>=10) {
            sum.insert(0, "1");
        }
        return sum;
    }
    return sum;
}

string multiply(string lhs, string rhs) {
    // TODO(student): implement
    lhs=trim_leading_zeros(lhs);
    rhs=trim_leading_zeros(rhs);
    string product = "0";
    int digitProduct = 0;
    string level = "";
    string newLhs = lhs;
    string newRhs = rhs;
    if (newLhs[0]=='-') { //takes out negative sign
        newLhs = newLhs.substr(1,lhs.size()-1);
    }
    if (newRhs[0]=='-') {
        newRhs = newRhs.substr(1,rhs.size()-1);
    }

    while (newLhs.size()!=newRhs.size()) { //make newLhs and newRhs equal lengths
        if (newLhs.size()>newRhs.size()) {
            newRhs.insert(0, "0");
        }
        if (newRhs.size()>newLhs.size()) {
            newLhs.insert(0, "0");
        }
    }
    for (int r=(newRhs.size()-1); r>=0; --r) {
        level = "";
        digitProduct = 0;
        for (int l=(newLhs.size()-1); l>=0; --l) {
            if (digitProduct>=10) {
                digitProduct /= 10;
            } 
            else {
                digitProduct = 0;
            }
            digitProduct += (digit_to_decimal(newRhs[r]) * digit_to_decimal(newLhs[l]));
            if (level.size()<1) { //for first iteration
                level.push_back(decimal_to_digit(digitProduct%10));
            }
            else { //after first iteration
                string putIn = "";
                putIn+=decimal_to_digit(digitProduct%10); 
                level.insert(0, putIn);  
            }
        }
        if (digitProduct>=10) {
            string x="";
            x+=decimal_to_digit(digitProduct/10);
            level.insert(0, x);
        }
        for (long unsigned int zeros = 0; zeros<(newRhs.size()-r-1); ++zeros) {
            level.append("0");
        }
        product = add(product, level);
    }
    if ((lhs[0]=='-' && rhs[0]!='-') || (rhs[0]=='-' && lhs[0]!='-')) { //if answer should be negative
        product.insert(0, "-");
    }
    return product;
}
