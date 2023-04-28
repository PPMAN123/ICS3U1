#include <iostream>

using namespace std;

void specialMessage(string message){
  cout << "**" << message << "**" << endl;
}

void specialMessage(string message, string border){
  cout << border << message << border << endl;
}

int main(){
  specialMessage("Hello World");
}