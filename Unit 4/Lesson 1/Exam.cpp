#include <iostream>

using namespace std;

int main(){
  float sum;
  int score;

  while (score != -1) {
    cin >> score;
    if (score != -1){
      sum += score;
    }
  }

  cout << sum / 5 << endl;
}