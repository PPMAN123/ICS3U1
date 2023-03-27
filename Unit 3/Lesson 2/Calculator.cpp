#include <iostream>

using namespace std;

int main(){
  char op;
  float a, b;
  cin >> a >> op >> b;

  switch(op){
    case '+': cout << a << " + " << b << " = " << a + b << endl; break;
    case '-': cout << a << " - " << b << " = " << a - b << endl; break;
    case '*': cout << a << " * " << b << " = " << a * b << endl; break;
    case '/': cout << a << " / " << b << " = " << a / b << endl; break;
    default: cout << "input a usable operator please" << endl; break;
  }
}