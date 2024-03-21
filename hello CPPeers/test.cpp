#include<iostream>
#include<fstream>
#include<stdexcept>
using std::string;
using std::cout;
using std::endl;

int main() {
    string userOrPost;
    string nameFromFile;
    unsigned int idFromFile;
    string postInfo;
    std::ifstream fin("TAMU-csce121-small.txt");
    if (!fin.good()) {
    throw std::invalid_argument("loadFromFile: invalid parameter values");
    }
    fin >> userOrPost;
    while (true) {
        cout << "userOrPost: " << userOrPost << endl;
        if (userOrPost == "User") {
            getline(fin, nameFromFile);
            // (*this).addUser(nameFromFile);
            nameFromFile.erase(0,1);
            cout << "nameFromFile: '" << nameFromFile << "'"<< endl;
        }
        else if (userOrPost == "Post") {
            fin >> idFromFile >> nameFromFile;
            getline(fin, postInfo);
            postInfo.erase(0,1);
            cout << "idFromFile: " << idFromFile << endl;
            cout << "nameFromFile: " << nameFromFile << endl;
            cout << "postInfo: '" << postInfo << "'" << endl;
            // (*this).addPost(idFromFile, nameFromFile, postInfo);
        }
        else {
            throw std::runtime_error("loadFromFile: unknown entry (neither User nor Post)");
        }
         fin >> userOrPost;
        if (fin.eof()) {
            break;
        }
    }
    return 0;
}