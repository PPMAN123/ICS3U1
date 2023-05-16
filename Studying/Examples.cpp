#include <iostream>

using namespace std;

int addNumbers(int a, int b){
  cout << a + b << endl;
  return a + b;
}

// void addNumbers(int a, long b = 5){
//   cout << a + b << endl;
// }

// void addNumbers(double a, double b){
//   cout << a + b << endl;
// }

// void addNumbers(){
//   cout << "FUCK YOU" << endl;
// }

int main(){
  cout << 10 + addNumbers(5, 200) << endl;
}
