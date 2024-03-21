#include <iostream>
#include <stdexcept>

int Largest(int a, int b, int c) {
  int d=a;
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  if((a+b)%2!=0){
    return false;
  }else{
    return true;
  }
}

int BoxesNeeded(int apples) {
  if (apples<=0) {
    return 0;
  }
  else if (apples%20==0) {
    return apples/20;
  }
  else {
    return (1+apples/20);
  }
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if (A_correct<0 || A_total<=0 || B_correct<0 || B_total<=0 || A_correct>A_total || B_correct>B_total) {
    throw std::invalid_argument("Invalid argument");
  }
  return (A_correct*10000/A_total > B_correct*10000/B_total);  
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 && pizzas <= 20) {
    return true;
  }
  if (is_weekend && pizzas >= 10) {
    return true;
  }
  return false;
}

int SumBetween(int low, int high) {
  int value = 0;
  if (low>high) {
    throw std::invalid_argument("Invalid argument");
  }
  if (low<=0 && high>=0) { //positive high, negative low
    if (-1*high<low) { //high > absolute value low
      for (int i=abs(low)+1; i<high; ++i) {
        if (i>(INT32_MAX-value)) { //max = 2,147,483,647
          throw std::overflow_error("Overflow error");
        }
        value+=i;
      }
      value+=high;
    }
    else if (-1*high>low) { //high < absolute value low
      for (int i=(-1*high)-1; i>low; --i) {
        if ((INT32_MIN-value)>i) { //min = -2,147,483,648
          throw std::overflow_error("Overflow error");
        }
        value+=i;
      }
      value+=low;
    }
    else if (-1*high==low) { //high = absolute value low
      return 0;
    }
   }

  else if (low>=0 && high>=0) { //both positive
    for (int i=low; i<high; ++i) {
      if (i>(INT32_MAX-value)) {
        throw std::overflow_error("Overflow error");
      }
      value+=i;
    }
    value+=high;
  }

  else if (low<=0 && high<=0) { //both negative
    for (int i=high; i>low; --i) {
      if ((INT32_MIN-value)>i) {
        throw std::overflow_error("Overflow error");
      }
      value+=i;
    }
    value+=low;
  }
  return value;
}

int Product(int a, int b) {
  if (a==0 || b==0) {
    return 0;
  }
  if ((a>0 && b>0) && (b > static_cast<double>(INT32_MAX) / static_cast<double>(a))) { //both positive and overflow
    throw std::overflow_error("Overflow error");
  }
  if ((a<0 && b<0) && (b < static_cast<double>(INT32_MAX) / static_cast<double>(a))) { //both negative and overflow
    throw std::overflow_error("Overflow error");
  }
  if ((a>0 && b<0) && (b < static_cast<double>(INT32_MIN) / static_cast<double>(a))) { //a positive, b negative and overflow
    throw std::overflow_error("Overflow error");
  }
  if ((a<0 && b>0) && (b > static_cast<double>(INT32_MIN) / static_cast<double>(a))) { //a negative, b positive and overflow
    throw std::overflow_error("Overflow error");
  }
  return a * b;
}