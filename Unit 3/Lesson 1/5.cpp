#include <iostream>

using namespace std;

int main(){
  float a, b, c;
  cin >> a >> b >> c;

  float determinant = (b*-1)/(2*a);

  if (determinant < 0){
    cout << "No real roots" << endl;
  } else if (determinant == 0){
    cout << "One real root" << endl;
  } else {
    cout << "Two real roots" << endl;
  }
}