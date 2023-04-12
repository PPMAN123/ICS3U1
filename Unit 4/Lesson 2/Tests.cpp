#include <iostream>
using namespace std;

int main(){
  int numOfStudents, numOfTests;
  int i = 0;

  cin >> numOfStudents;
  cin >> numOfTests;

  while (i < numOfStudents){
    float acc = 0;
    int j = 0;
    cout << "Student " << i + 1 << endl;
    while (j < numOfTests){
      int inputValue;
      cin >> inputValue;
      while (inputValue < 0){
        cout << "ERROR: Enter a valid mark" << endl;
        cin >> inputValue;
        if (inputValue > 0){
          break;
        }
      }
      acc += inputValue;
      j++;
    }
    cout << "Student " << i+1 << "'s average is " << acc/numOfTests << endl;
    i++;
  }
}