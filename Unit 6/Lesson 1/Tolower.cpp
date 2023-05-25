#include <iostream>
#include <cctype>
using namespace std;

string stringToLower(string word, int start, int end, string acc = ""){
  if (start == end){
    return acc;
  }
  return stringToLower(word, start + 1, end, (acc + tolower(word[start])));
}

int main(){
  string x = "ASDFASDFASDFASDF";
  cout << stringToLower(x, 0, x.length()) << endl;
}