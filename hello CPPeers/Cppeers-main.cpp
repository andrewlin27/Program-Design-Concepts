/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Network.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
  // TODO(student): implement
  string processUser;
  cout << "Enter username: ";
  cin >> processUser;
  vector<Post*> processPosts = cppeers.getPostsByUser(processUser);
  for (unsigned int i = 0; i < processPosts.size(); i++) {
    cout << (*processPosts[i]).getPostText() << endl;
  }
}

void processPostsWithHashtags(Network& cppeers) {
  // TODO(student): implement
  string processTag;
  cout << "Enter tagname: ";
  cin >> processTag;
  vector<Post*> postPointers = cppeers.getPostsWithTag(processTag);
  for (unsigned int i = 0; i < postPointers.size(); i++) {
    cout << (*postPointers[i]).getPostText() << endl;
  }
}

void processMostPopularHashtag(Network& cppeers) {
  // TODO(student): implement
  vector<string> popTags = cppeers.getMostPopularHashtag();
  for (unsigned int i = 0; i < popTags.size() - 1; i++) {
    cout << popTags[i] << " ";
  }
  cout << popTags.back() << endl;
}

int main() {

  try {
    Network cppeers;

    int choice = 0;

    // present menu
    do {
      printMenu();
      cin >> choice;
      switch(choice) {
        case 1: {
          processLoad(cppeers);
          break;
        }
        case 2: {
          processPostsByUser(cppeers);
          break;
        }
        case 3: {
          processPostsWithHashtags(cppeers);
          break;
        }
        case 4: {
          processMostPopularHashtag(cppeers);
          break;
        }
      }
    } while (choice != 9);
  } catch (std::exception& exc) {
    std::cout << exc.what() << endl;
  }

  return 0;
}
