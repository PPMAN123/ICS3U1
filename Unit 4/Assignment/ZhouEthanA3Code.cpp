#include <iostream>
using namespace std;

void horizontalLine(char symbol, int length){
  for (int i = 0; i < length; i++){
    cout << symbol;
  }
  cout << endl;
}

void verticalLine(char symbol, int height){
  for (int i = 0; i < height; i++){
    cout << symbol << endl;
  }
}

void isoscelesTriangle(char symbol, int height){
  for (int i = 1; i <= height; i++){
    for (int j = 0; j < height - i; j++){
      cout << ' ';
    }
    for (int j = 0; j < i; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

void arch(char symbol, int height){
  for (int i = 0; i <= height; i++){
    for (int j = 0; j < height - i; j++){
      cout << symbol;
    }
    for (int j = 0; j < i; j++){
      cout << "  ";
    }
    for (int j = 0; j < height - i; j++){
      cout << symbol;
    }
    cout << endl;
  }
}


void hourGlass(char symbol, int base){
  if (base % 2 == 1){
    int halfWay = (base/2) + 1;

    for (int i = base; i > 0; i -= 2){
      for (int j = 1; j < halfWay - i/2; j++){
        cout << ' ';
      }
      for (int j = 0; j < i; j++){
        cout << symbol;
      }
      cout << endl;
    }

    for (int i = 2; i < base; i += 2){
      for (int j = 1; j < halfWay - i/2; j++){
        cout << ' ';
      }
      for (int j = 0; j <= i; j++){
        cout << symbol;
      }
      cout << endl;
    }
  } else {

  }
}

void house(char symbol, int base, int heightWithoutRoof){
  isoscelesTriangle(symbol, base);
  for (int i = 0; i < heightWithoutRoof - 1; i++){
    for (int j = 0; j < base; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

int main(){
  arch('*', 6);
}