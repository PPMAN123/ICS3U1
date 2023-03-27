#include <iostream>
#include <cmath>
using namespace std;

int main(){
  float heightFeet, heightInches, bodyweight;

  cin >> heightFeet >> heightInches >> bodyweight;

  float bmi = bodyweight * (703/pow((heightFeet * 12 + heightInches), 2));

  if (bmi < 18.5){
    cout << "Underweight" << endl;
  } else if (bmi < 24.9){
    cout << "Healthy" << endl;
  } else if (bmi < 29.9) {
    cout << "Overweight" << endl;
  } else {
    cout << "Obese" << endl;
  }
}