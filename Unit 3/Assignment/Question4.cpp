#include <iostream>
#include <cmath>
using namespace std;

int main(){
  //Tier 4, question 12
  system("clear");

  int selectionNumber;
  cout << "\nGeometry Calculator\n" << endl;
  cout << "\t1. Calculate the area of a Cirlce" << endl;
  cout << "\t2. Calculate the area of a Rectangle" << endl;
  cout << "\t3. Calculate the area of a Triangle" << endl;
  cout << "\t4. Quit" << endl;
  cout << "Enter your choice (1-4): ";
  cin >> selectionNumber;

  switch(selectionNumber){
    case 1: 
      //Area of circle stuff
      float radius;
      cout << "Enter the radius: ";
      cin >> radius;
      if (radius <= 0){
        cout << "ERROR: The radius has to be a positive number" << endl;
        break;
      }
      cout << "The area of the circle is " << M_PI * pow(radius, 2) << endl;
      break;
    case 2:
      //Area of rectangle stuff
      float length, width;
      cout << "Enter the length of the rectangle: ";
      cin >> length;
      cout << "Enter the width of the rectangle: ";
      cin >> width;
      if (length <= 0){
        cout << "ERROR: The length has to be a positive number" << endl;
        break;
      }
      if (width <= 0){
        cout << "ERROR: The width has to be a positive number" << endl;
        break;
      }

      cout << "The area of the rectangle is " << length*width << endl;

      break;
    case 3:
      //Area of triangle stuff
      float base, height;
      cout << "Enter the base length of the triangle: ";
      cin >> base;
      cout << "Enter the height of the triangle: ";
      cin >> height;

      if (base <= 0){
        cout << "ERROR: Enter a valid base length" << endl;
        break;
      }
      if (height <= 0){
        cout << "ERROR: Enter a valid height" << endl;
        break;
      }
      cout << "The area of the triangle is " << (base*height)/2 << endl;
      break;
    case 4:
      cout << "Goodbye" << endl;
      break;
    default:
      cout << "ERROR: Enter a value between 1-4" << endl;
  }
}