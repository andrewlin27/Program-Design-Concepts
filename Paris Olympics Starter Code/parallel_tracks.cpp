#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <fstream>
#include <sstream>

using std::string;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
	// //TODO
	std::ifstream data(file);
	if (!data.is_open()) {
		throw std::invalid_argument("Cannot open file");
	}
	string lineData;
	for (int i = 0; i<9; ++i) {
		getline(data, lineData);
		if (lineData=="") {
			throw std::domain_error("File missing data");
		}
		std::istringstream line(lineData);
		line>>timeArray[i];
		if (line.fail()) {
			throw std::domain_error("File contains invalid data (time)");
		}
		line>>countryArray[i];
		line>>numberArray[i];
		if (line.fail()) {
			throw std::domain_error("File contains invalid data (number)");
		}
		getline(line, lastnameArray[i]);
		lastnameArray[i] = trim(lastnameArray[i]);
	}
	
	for (int i=0; i<9; ++i) {
		if (timeArray[i]<=0) {
			throw std::domain_error("File contains invalid data (time)"); 
		}
		if (countryArray[i].size()!=3 || !isupper(countryArray[i][0]) || !isupper(countryArray[i][1]) || !isupper(countryArray[i][2])) {
			throw std::domain_error("File contains invalid data (country)");
		}
		if (numberArray[i]>99) {
			throw std::domain_error("File contains invalid data (number)");
		}
		if (!(lastnameArray[i].size()>1)) {
			throw std::domain_error("File contains invalid data (name)");
		}
		for (int j = 0; lastnameArray[i][j]; j++) {
			if (!isalpha(lastnameArray[i][j]) && lastnameArray[i][j]!=' ') {
				throw std::domain_error("File contains invalid data (name)");
			}
		}
	}
	data.close();
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	//TODO
	for (unsigned int i = 0; i < 9; ++i) {
		if (ary[i] != 0) {
			ary[i] = 0;
		}
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	for (unsigned int i = 0; i < 9; ++i) {
		if (ary[i] != 0) {
			ary[i] = 0;
		}
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	for (unsigned int i = 0; i < 9; ++i) {
		if (ary[i] != "N/A") {
			ary[i] = "N/A";
		}
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	unsigned int rank = 0;
	int min = 0;
	double replicate[9];
	for (int i = 0; i < 9; i++) { //create replication of timeArray
		replicate[i] = timeArray[i];
	}
	for (int do9 = 0; do9 < 9; do9++) {
		min = 0;
		for (int i = 0; i < 9; i++) {
			if (replicate[i] < replicate[min]) {
				min = i;
			}
		}
		rank++;
		rankArray[min] = rank;
		replicate[min] *= 100;
	}
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}