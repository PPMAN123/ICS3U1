#include <fstream>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

int main(){
  ofstream numbers("numbers.txt");
  srand(time(NULL));

  if (numbers.is_open()){
    for (int i = 0; i < 10; i++){
      numbers << rand() % 101 << endl;
    }
    numbers.close();
  } else {
    cout << "ERROR" << endl;
    return 1;
  }

  ifstream numbersRead("numbers.txt");

  if (numbersRead.is_open()){
    string number;
    int acc = 0;
    while(!numbersRead.eof()){
      getline(numbersRead, number);
      if (number.length() > 0){
        acc += stoi(number);
      }
    }

    cout << acc << endl;
    numbersRead.close();
  } else {
    cout << "ERROR" << endl;
    return 1;
  }
  return 0;
}