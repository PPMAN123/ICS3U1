#include <iostream>
using namespace std;

int main(){
  string string1, string2;

  cin >> string1 >> string2;

  if (string1.length() == string2.length()){
    for (int i = 0; i < string1.length(); i++){
      cout << string1[i] << string2[i];
    }
  } else {
    cout << string1 + string2 << endl;
  }

  cout << endl;
}