#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
  unordered_map<string, unordered_map<int, float>> map = {
    {"balls", {
      {1, 1.5}
    }}
  };

  cout << map["balls"][1] << endl;
}