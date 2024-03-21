#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a;
	int b;
	// TODO(student): print prompt for input
	cout<<"Enter numbers 10 <= a <= b < 10000: ";
	
	// TODO(student): read the numbers from standard input
	cin>>a;
	cin>>b;

	// TODO(student): validate input (and reprompt on invalid input)
	while (!(is_valid_range(a, b))) { //while invalid input
		cout<<"Invalid Input"<<endl;
		cout<<"Enter numbers 10 <= a <= b < 10000: ";
		cin>>a;
		cin>>b;
	}
	
	// TODO(student): compute and display solution
	count_valid_mv_numbers(a, b);

	return 0;
}