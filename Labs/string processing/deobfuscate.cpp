#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {
    string sentence;
    string details;
    int spaceLocation=0;
    cout<<"Please enter obfuscated sentence: ";
    cin>>sentence;
    cout<<"Please enter deobfuscation details: ";
    cin>>details;
    for (long unsigned int i=0; i<(details.size()-1);++i) {
        spaceLocation += details[i]-48;
        sentence.insert(spaceLocation, " ");
        spaceLocation += 1;
    }
    cout<<"Deobfuscated sentence: "<<sentence<<endl;
    return 0;
}
