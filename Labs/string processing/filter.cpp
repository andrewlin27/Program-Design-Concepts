#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() { //couldn't figure out, gave up
    string sentence;
    string word;
    int index;
    int start = 0;
    string pounds = "";
    cout<<"Please enter the sentence: ";
    cin>>sentence;
    cout<<"Please enter the filter word: ";
    cin>>word;
    for (unsigned long int i = 0; i<word.size(); ++i) {
        pounds.append("#");
    }
    while (sentence.find(word)) {
        index = sentence.find(word, start);
        start+=(index + word.size());
        sentence.replace(index, word.size(), pounds);
    }
    cout<<"Filtered sentence: "<<sentence<<endl;

    return 0;
}
