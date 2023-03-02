#include <iostream>
#include <bitset>
using namespace std;

int main(){
  int base = 1234;
  bitset<8> binary(base);

  cout << "Binary: " << binary.to_string() << endl;
  cout << "Octal: " << oct << base << endl;
  cout << "Hexadecimal: " << hex << uppercase << base << endl;
}