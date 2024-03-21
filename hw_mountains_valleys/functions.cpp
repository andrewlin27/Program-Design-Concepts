#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if (!(b>=a)) {
		return false;
	}
	if (!(10000>b)) {
		return false;
	}
	if (!(10<=a)) {
		return false;
	}
	return true;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int digit;
	char type='A'; //initialize type
	while (number>=10) { //keep looping until number is a single digit
		digit=number%10; //last digit
		number=number/10; //number without last digit
		if (((number%10) < digit) && (type=='|' || type=='A')) { //if last was '\' and next is '/'
			type='/';
		}
		else if (((number%10) > digit) && (type=='/' || type=='A')) { //if last was '/' and next is '\'
			type='|'; //should be '\'
		}
		else {
			return 'N';
		}

	}
	if (type=='/') { //if first is '/'
		return 'M';
	}
	else if (type=='|') { //if first is '|'
		return 'V';
	}
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int mountains=0;
	int valleys=0;
	for (int i=a; i<=b; ++i) { //iterate through numbers in interval
		if (classify_mv_range_type(i)=='M') {
			mountains+=1;
		}
		else if (classify_mv_range_type(i)=='V') {
			valleys+=1;
		}
	}
	cout<<"There are "<<mountains<<" mountain ranges and "<<valleys<<" valley ranges between "<<a<<" and "<<b<<"."<<endl;
}