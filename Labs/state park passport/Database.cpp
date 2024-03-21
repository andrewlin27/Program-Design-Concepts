// Class file for Database class

#include "Database.h"

using std::string, std::vector;

// Constructor
// Constructor for Database class
// TODO(student): implement constructor using member initializer list
Database::Database() 
: stateParkList({}), camperList({}) {
}

// Destructor
// DO NOT CHANGE, ALREADY IMPLEMENTED
Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

// Mandatory
// Dynamically creates a new state park and adds it to stateParkList
void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)
	// TODO(student): implement function
	StatePark* newStatePark = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(newStatePark);
	return;
}

// Mandatory
// Dynamically creates a new passport and adds it to camperList
void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)
	// TODO(student): implement function
	Passport* newPassport = new Passport(camperName, isJuniorPassport);\
	camperList.push_back(newPassport);
	return;
}

// Mandatory
// Searches for a passport and state park whose name matches the given parameters and
// adds the park to the passport
void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)
	// TODO(student): implement function
	int camperIdx = -1;
	int parkNameIdx = -1;
	for (unsigned int i = 0; i < camperList.size(); i++) {
		if (camperName == (*camperList[i]).getCamperName()) {
			camperIdx = i;
		}
	}
	for (unsigned int i = 0; i < stateParkList.size(); i++) {
		if (parkName == (*stateParkList[i]).getParkName()) {
			parkNameIdx = i;
		}
	}
	if (camperIdx == -1 || parkNameIdx == -1) {
		return;
	}
	(*camperList[camperIdx]).addParkVisited(stateParkList[parkNameIdx]);
	return;
}

// Option A
// Returns a vector of the names of all the parks whose revenue is between the parameters
// given (including the boundaries)
vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)
	// TODO(student): implement function
	return {};
}

// Option B
// Returns a vector of the names of all the campers who have reached at least the hiking
// level given by the parameter
vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)
	// TODO(student): implement function
	return {};
}