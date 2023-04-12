#include <iostream>
using namespace std;

int main(){
  int inputNum;
  do {
    cin >> inputNum;
  } while (inputNum < 0);

  for (int i = 1; i <= inputNum; i++){
    if (i % 5 == 0 && i % 7 == 0){
      cout << i << endl;
    }
  }
}