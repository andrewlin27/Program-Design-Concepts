#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {
    string password;
    string newPassword = "";
    cout<<"Please enter your text input: ";
    cin>>password;
    cout<<"input: "<<password<<endl;
    for (long unsigned int i = 0; i<password.length();++i) {
        if (password[i]!='a' && password[i]!='e' && password[i]!='i' && password[i]!='o' && password[i]!='u') {
            string s="";
            s+=password[i];
            newPassword.append(s);
        }
        else {
            if (password[i]=='a') {
                newPassword.append("@");
            }
            else if (password[i]=='e') {
                newPassword.append("3");
            }
            else if (password[i]=='i') {
                newPassword.append("!");
            }
            else if (password[i]=='o') {
                newPassword.append("0");
            }
            else if (password[i]=='u') {
                newPassword.append("^");
            }
        }
    }
    string finalPassword = newPassword;
    for (int i = newPassword.size() - 1; i>=0; --i) {
        string t = "";
        t+=newPassword[i];
        finalPassword.append(t);
    }
    cout<<"output: "<<finalPassword<<endl;

    return 0;
}
