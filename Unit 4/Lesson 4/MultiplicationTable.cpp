#include <iostream>
#include <iomanip>
using namespace std;

int main(){
  int width, length;

  cin >> width >> length;

  for (int i = 1; i <= min(width, length); i++){
    for (int j = 1; j <= max(width, length); j++){
      cout << setw(to_string(width*length).length()) << i*j << ' ';
    }
    cout << endl;
  }
}