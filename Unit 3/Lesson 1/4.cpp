#include <iostream>
using namespace std;

int main(){
  int a;

  cin >> a;

  if (a % 5 == 0 && a % 6 == 0){
    cout << "divisible by 5 and 6" << endl;
  } else if (a % 5 == 0 && a % 6 != 0) {
    cout << "divisible by 5" << endl;
  } else if (a % 5 != 0 && a % 6 == 0) {
    cout << "divisible by 6" << endl;
  } else {
    cout << "not divisible by any" << endl;
  }
}