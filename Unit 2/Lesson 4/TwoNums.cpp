#include <iostream>
using namespace std;

int main(){
  int num1, num2;

  cout << "Input two numbers separated by spaces: " << endl;
  cin >> num1 >> num2;

  cout << "Sum: " << num1 + num2 << endl;
  cout << "Product: " << num1 * num2 << endl;
  cout << "Difference: " << num1 - num2 << endl;
  cout << "Quotient: " << num1 / num2 << endl;
  cout << "Modulus: " << num1 % num2 << endl;
}