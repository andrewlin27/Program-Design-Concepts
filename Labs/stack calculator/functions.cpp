#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
  // TODO: implement push function for stack
  INFO_STRUCT(stack);
  INFO(number);
  if (stack.count == stack.capacity) {
    int* tempAry = stack.numbers; //create temporary arrays
    stack.capacity = stack.capacity * 2; //update dimension sizes
    stack.numbers = new int[stack.capacity] {}; //update original 2d array to new size
    for (int i = 0; i < stack.count; i++) { //fill in data
      stack.numbers[i] = tempAry[i];
    }
    delete [] tempAry; //delete temporary arrays
  }
  stack.numbers[stack.count] = number;
  stack.count++;
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  // TODO: implement pop function for stack
  INFO_STRUCT(stack);
  if (stack.count == 0) {
    return INT32_MAX;
  }
  else {
    int returnVal = stack.numbers[stack.count - 1];
    stack.numbers[stack.count - 1] = 0;
    stack.count--;
    return returnVal;
  }
  return 0;
}

/**
 * ----- OPTIONAL -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  // TODO (optional): implement peek function for stack
  INFO_STRUCT(stack);
  if (stack.count == 0) {
    return INT32_MAX;
  }
  return stack.numbers[stack.count - 1];
}
