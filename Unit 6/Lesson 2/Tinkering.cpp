#include <fstream>
#include <iostream>

using namespace std;

int main(){
  ofstream testFile("test.txt");

  if (testFile.is_open()){
    testFile << "My balls" << endl;
    cout << "i did something" << endl;
    testFile.close();
  } else {
    cout << "ERROR" << endl;
    return 1;
  }

  return 0;
}