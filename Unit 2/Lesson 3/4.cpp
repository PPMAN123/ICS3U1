#include <iostream>
#include <string>
using namespace std;

int main(){
  int digit1, digit2, digit3, digit4, digit5, digit6;

  cin >> digit1 >> digit2 >> digit3 >> digit4 >> digit5 >> digit6;

  cout << digit1 + digit2 + digit3 + digit4 + digit5 + digit6 << endl;
  cout << to_string(digit1) + to_string(digit2) + to_string(digit3) + to_string(digit4) + to_string(digit5) + to_string(digit6) << endl;
}