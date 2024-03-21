#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node() 
	: data(TemperatureData()), next(nullptr)
{} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature) 
	: data(TemperatureData(id, year, month, temperature)), next(nullptr)
{}
// remember to initialize next to nullptr

bool Node::operator<(const Node& b) {
	// by location
	//assumes both strings are same size
	if (this->data.id < b.data.id) {
		return true;
	}
	else if (this->data.id > b.data.id) {
		return false;
	}
	
	// by year
	if (this->data.year < b.data.year) {
		return true;
	}
	else if (this->data.year > b.data.year) {
		return false;
	}

	// by month
	if (this->data.month < b.data.month) {
		return true;
	}
	else if (this->data.month > b.data.month) {
		return false;
	}
	return false;
}
