#include <iostream>
#include <string>
using namespace std;

int main(){
    cout << "Please enter your name: ";

    string name;
    getline(cin,name);

    cout << "Welcome " << name << endl;

    return 0;
}
