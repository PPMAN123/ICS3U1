#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

void printArray(int array[][10], int columnHeight, int rowWidth){
  for (int i = 0; i < columnHeight; i++){
    for (int j = 0; j < rowWidth; j++){
      cout << setw(2) << array[i][j] << ' ';
    }
    cout << endl;
  }
}

void sumsOfRows(int array[][10], int columnHeight, int rowWidth){
  for (int i = 0; i < columnHeight; i++){
    int rowSum = 0;
    for (int j = 0; j < rowWidth; j++){
      rowSum += array[i][j];
    }
    cout << rowSum << endl;
  }
}

void sumOfCols(int array[][10], int columnHeight, int rowWidth){
  int sums[columnHeight] = {0};
  for (int i = 0; i < columnHeight; i++){
    for (int j = 0; j < rowWidth; j++){
      sums[j] += array[i][j];
    }
  }

  for (int i = 0; i < columnHeight; i++){
    cout << sums[i] << endl;
  }
}

int main(){
  const int columnHeight = 10;
  const int rowWidth = 10;
  srand(time(NULL));

  int array[columnHeight][rowWidth];

  for (int i = 0; i < columnHeight; i++){
    for (int j = 0; j < rowWidth; j++){
      array[i][j] = rand() % 100;
    }
  }

  printArray(array, columnHeight, rowWidth);

  // sumsOfRows(array, columnHeight, rowWidth);

  sumOfCols(array, columnHeight, rowWidth);
}