#include "TemperatureDatabase.h"

#include <fstream>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase()
	: records(LinkedList()) //**
{}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Implement this function for part 1
	string newLocation;
	int newYear;
	int newMonth;
	double newTemp; 

	string line;
	stringstream ss;

	ifstream fin(filename);
	if (!fin.is_open()) {
        cout << "Error: Unable to open " << filename << endl;
		return;
    }
	while (!fin.eof()) {
		getline(fin, line);
		//convert string to string stream
		ss.str(line);
		ss >> newLocation >> newYear >> newMonth;
		if (ss.rdbuf()->in_avail() == 0) {
			cout << "Error: Other invalid input" << endl;
			line = "";
			ss.clear();
			continue;;
		}
		ss >> newTemp;
		//check if valid data
		if (newTemp == -99.99) {
			line = "";
			ss.clear();
			continue;
		}
		else if (newYear < 1800 || newYear > 2022) {
			cout << "Error: Invalid year " << newYear << endl;
			line = "";
			ss.clear();
			continue;
		}
		else if (newMonth < 1 || newMonth > 12) {
			cout << "Error: Invalid month " << newMonth << endl;
			line = "";
			ss.clear();
			continue;
		}
		else if (newTemp < -50.0 || newTemp > 50.0) { 
			cout << "Error: Invalid temperature " << newTemp << endl;
			line = "";
			ss.clear();
			continue;
		}
		records.insert(newLocation, newYear, newMonth, newTemp); 
		line = "";
		ss.clear();
	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

// void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	//ifstream fin(filename);
	//  Leave it blank for part 1
// }
