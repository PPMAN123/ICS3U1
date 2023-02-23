#include <iostream>
using namespace std;

int main(){
  string input;
  cout << "What is your name? ";
  cin >> input;
  cout << "Hello " << input << "!" << endl;

  cin.ignore(256, '\n');

  string fullName;
  cout << "What is your name? \n";
  getline(cin, fullName);
  cout << "Nice to see you, " << fullName << endl;
}