#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  int counter = 0;
  for (int i = 0; str[i]; ++i) {
    counter++;
  }
  return counter;
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  for (int i = 0; str[i]; ++i) {
    if (character == str[i]) {
      return i;
    }
  }
  return length(str);
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  // if (sizeof(str1)!=sizeof(str2)) {
  //   return false;
  // }
  int counter1 = 0;
  int counter2 = 0;
  for (int i = 0; str1[i]; ++i) {
    counter1 = i;
  }
  for (int i = 0; str2[i]; ++i) {
    counter2 = i;
  }
  if (counter1 != counter2) {
    return false;
  }
  for (int i = 0; str1[i]; ++i) {
    if (str1[i]!=str2[i]) {
      return false;
    }
  }
  return true;
}