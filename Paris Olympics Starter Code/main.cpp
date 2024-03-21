/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.text
content: The text file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include "parallel_tracks.h"
#include <fstream>

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    
    // good_data01.txt
    

    // TODO: create arrays needed
    double time[SIZE];
    string country[SIZE];
    unsigned int number[SIZE];
    string lastname[SIZE];
    unsigned int rank[SIZE];
    // TOTO: prep all arrays
	prep_double_array(time);
    prep_string_array(country);
    prep_unsigned_int_array(number);
    prep_string_array(lastname);
    prep_unsigned_int_array(rank);
    // TODO: prompt until both the file and the contained data are valid
    cout << "Enter file name: ";
    string file1 = "";
    cin >> file1; 
    std::ifstream content;
    content.open(file1);
	while (!content) {
		cout << "Invalid File: Cannot open file\nEnter file name: ";
        file1 = "";
        cin >> file1;
        content.open(file1);
	}
    content.close();
    
    //try using if stream to read data instead of .open. above is all good. 
    // string line; 
    // bool missing = false;
    // bool test = true;
    // for (int i = 0; i<9; ++i) {
	// 	getline(content, line); //not hitting this
	// 	if (line == "") {
	// 		missing = true;
    //         content.close();
    //         break;
    //     }
    // }
    // while (missing) {
    //     cout << "Invalid File: File missing data\nEnter file name: ";
    //     file1 = "";
    //     cin >> file1;
    //     content.open(file1);
    //     for (int i = 0; i<9; ++i) {
    //         getline(content, line);
    //         if (line == "") {
    //             test = false;
    //             break;
    //         }
    //     }
    //     if (test) {
    //         break;
    //     }
    // }         
    
    
    // TODO: determine ranking, notice the rank array receives the results
    get_runner_data(file1, time, country, number, lastname);
    get_ranking(time, rank);
    // TODO: Output results
    print_results(time, country, lastname, rank);
    return 0;
}

