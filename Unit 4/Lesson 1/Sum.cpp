#include <iostream>

using namespace std;

int main(){
  int i = 1;
  int acc;

  while (i <= 9){
    acc += i;
    i++;
  }
  cout << acc << endl;
}