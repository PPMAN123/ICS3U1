#include <iostream>
#include <cctype>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

bool shouldContinue(){
  char continuationInput;
  bool shouldContinue = true;
  cout << "Do you wish to continue the program? (y/n): ";
  cin >> continuationInput;
  return (tolower(continuationInput) == 'y');
}

int main(){
  // Tier 1, question 1
  system("clear");
  float num1, num2;
  cout << "\nThis is a program to compare two numbers you input\n" << endl;
  cout << "Enter your first number: ";
  cin >> num1;
  cout << "Enter your second number: ";
  cin >> num2;

  if (num1 > num2) cout << num1 << " is greater than " << num2 << endl;
  else if (num2 > num1) cout << num2 << " is greater than " << num1 << endl;
  else cout << num1 << " is equal to " << num2 << endl;

  //Prompts the user to continue the program
  if (!shouldContinue()){
    return 0;
  }
  //Tier 2, question 6
  system("clear");

  float xValue, yValue;
  string outputString;

  cout << "\nThis program will give you what quadrant your co-ordinate is by inputting on the x and y values\n" << endl;
  cout << "Enter your x-value: ";
  cin >> xValue;
  cout << "Enter your y-value: ";
  cin >> yValue;

  cout << (xValue > 0 ? (yValue > 0 ? "This co-ordinate is in Quadrant I" : "This co-ordinate is in Quadrant IV") : (yValue > 0 ? "This co-ordinate is in Quadrant II" : "This co-ordinate is in Quadrant III")) << endl;

  //Prompts the user to continue the program
  if (!shouldContinue()){
    return 0;
  }
  //Tier 3, question 7
  system("clear");

  int numOfPennies, numOfNickels, numOfDimes, numOfQuarters, amountOfCents;
  cout << "\nMake a dollar using coins game\n" << endl;
  cout << "Enter the amount of pennies: ";
  cin >> numOfPennies;
  cout << "Enter the amount of nickels: ";
  cin >> numOfNickels;
  cout << "Enter the amount of dimes: ";
  cin >> numOfDimes;
  cout << "Enter the amount of quarters: ";
  cin >> numOfQuarters;

  amountOfCents = numOfPennies * 1 + numOfNickels * 5 + numOfDimes * 10 + numOfQuarters * 25;

  if (numOfPennies < 0 || numOfNickels < 0 || numOfDimes < 0 || numOfQuarters < 0){
    cout << "Enter proper values please" << endl;
  } else {
    switch(amountOfCents){
      case 100: cout << "CONGRATULATIONS YOU WIN!!!" << endl; break;
      case INT_MIN ... 99: cout << "That is less than a dollar, try again next time." << endl; break;
      default: cout << "That is more than a dollar, try again next time." << endl; break;
    }
  }

  //Prompts the user to continue the program
  if (!shouldContinue()){
    return 0;
  }

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
      cout << "The area of the circle is " << pow(M_PI * radius, 2) << endl;
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

  cout << "Thank you for using my program! :)" << endl;
}