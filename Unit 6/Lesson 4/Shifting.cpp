#include <iostream>

using namespace std;

void shifting(int (& array)[], int size, int shiftBy, int (& returnArray)[]){

  if (shiftBy > 0){
    for (int i = 0, j = shiftBy; i < size && j < size; i++, j++){
      returnArray[j] = array[i];
    }
    for (int i = 0, j = size-shiftBy; i < size && j < size; i++, j++){
      returnArray[i] = array[j];
    }
  } else {
    //[0,1,2,3,4]
    //[1,2,3,4,0]
    for (int i = 0, j = -1 * shiftBy; i < size && j < size; i++, j++){
      returnArray[i] = array[j];
    }
    for (int i = size + shiftBy, j = 0; i < size && j < size; i++, j++){
      returnArray[i] = array[j];
    }
  }

}

int main(){
  const int size = 10;
  int testArray[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int shiftedArray[size];
  shifting(testArray, size, 6, shiftedArray);

  for (int i = 0; i < size; i++){
    cout << shiftedArray[i] << ' ';
  }
}