#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int randomNum = rand() % 100;

  cout << randomNum << endl;
}