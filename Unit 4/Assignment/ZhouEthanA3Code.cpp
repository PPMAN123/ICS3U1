#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

void horizontalLine(int length, char symbol){
  cout << "Here is a horizontal line with the length of " << length << ":\n" << endl;
  for (int i = 0; i < length; i++){
    cout << symbol;
  }
  cout << endl;
}

void verticalLine(int height, char symbol){
  cout << "Here is vertical line with the height of " << height << ":\n" << endl;
  for (int i = 0; i < height; i++){
    cout << symbol << endl;
  }
}

void isoscelesTriangle(int height, char symbol){
  cout << "Here is an isosceles triangle with the height of " << height << ":\n" << endl;
  for (int i = 1; i <= height; i++){
    for (int j = 0; j < height - i; j++){
      cout << ' ';
    }
    for (int j = 0; j < i; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

void house(int heightWithoutRoof, int base ,char symbol){
  cout << "Here is a house with the base of " << base << " and the height without the roof of " << heightWithoutRoof << ":\n" << endl;
  isoscelesTriangle(base, symbol);
  for (int i = 0; i < heightWithoutRoof - 1; i++){
    for (int j = 0; j < base; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

void arch(int height, char symbol){
  cout << "Here is arch with the height of " << height << ":\n" << endl;
  for (int i = 0; i <= height; i++){
    for (int j = 0; j < height - i; j++){
      cout << symbol;
    }
    for (int j = 0; j < i; j++){
      cout << "  ";
    }
    for (int j = 0; j < height - i; j++){
      cout << symbol;
    }
    cout << endl;
  }
}


void hourGlass(int base, char symbol){
  cout << "Here is an hourglass with the base of " << base << ":\n" << endl;
  if (base % 2 == 1){
    int halfWay = (base/2) + 1;

    for (int i = base; i > 0; i -= 2){
      for (int j = 1; j < halfWay - i/2; j++){
        cout << ' ';
      }
      for (int j = 0; j < i; j++){
        cout << symbol;
      }
      cout << endl;
    }

    for (int i = 2; i < base; i += 2){
      for (int j = 1; j < halfWay - i/2; j++){
        cout << ' ';
      }
      for (int j = 0; j <= i; j++){
        cout << symbol;
      }
      cout << endl;
    }
  } else {
    for (int i = base; i >= 2; i -= 2){
      for (int j = 0; j < (base - i)/2; j ++){
        cout << ' ';
      }
      for (int j = 0; j < i; j++){
        cout << symbol;
      }
      cout << endl;
    }
    for (int i = 4; i <= base; i += 2){
      for (int j = (base - i)/2; j > 0; j--){
        cout << ' ';
      }
      for (int j = 0; j < i; j++){
        cout << symbol;
      }
      cout << endl;
    }
  }
}


void ring(int radius, char symbol){
  //uses the mathematical fact that x^2 + y^2 = radius^2
  cout << "Here is a ring with the radius of " << radius << ":\n" << endl;
  int expectedValue = pow(radius, 2);
  for (int y = -radius; y <= radius; y++) {
    for (int x = -radius; x <= radius; x++) {
      int computedValue = pow(x,2) + pow(y,2);
      if (abs(computedValue - expectedValue) <= radius) {
        cout << symbol;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
}

int numberPrompt(string prompt, int lowestValue, int highestValue){
  int inputValue;
  do{
    cout << prompt;
    cin >> inputValue;

    if (inputValue < lowestValue || inputValue > highestValue){
      cout << "Invalid Dimension! The dimension must be between " << lowestValue << " and " << highestValue << "." << endl;
    }
  } while (inputValue < lowestValue || inputValue > highestValue);

  return inputValue;
}

char symbolPrompt(string prompt){
  char symbol;
  cout << prompt;
  cin >> symbol;
  return symbol;
}

int main(){
  char generateMoreShapes;
  int selection;
  string shapes[7] = {
    "Horizontal Line",
    "Vertical Line",
    "Isosceles Triangle",
    "House",
    "Arch",
    "Hourglass",
    "Ring"
  };

  int timesGenerated[7] = {0,0,0,0,0,0,0};
  

  cout << "Welcome to the Shape Generator!\n" << endl;
  cout << "This program draws the following shapes:\n" << endl;
  for (int i = 0; i < 7; i++){
    cout << "\t" << i + 1 << ") " << shapes[i] << endl;
  }
  cout << endl;

  do{
    //First do loop to repeat if user wants to generate more shapes
    do{
      //Do loop that error traps invalid choice inputs
      cout << "Enter your choice (1-7): ";
      cin >> selection;
      if (selection < 0 || selection > 7){
        //Prints error message when selection is invalid
        cout << "\nInvalid input! Enter a number between 1 to 7 please: ";
        cin >> selection;
      }
    } while (selection < 0 || selection > 7);
    switch(selection){
      //Switch statement that handles selections
      case 1:
        //Using functions to save some variable declarations
        horizontalLine(
          numberPrompt("Enter the horizontal line's length: ", 1, 20),
          symbolPrompt("Enter your preferred symbol: ")
        );
        //This line of code adds 1 to the array that keeps track of how many times each shape is generated to the according choice
        timesGenerated[selection - 1] += 1;
        break;
      case 2:
        verticalLine(
          numberPrompt("Enter the vertical line's height: ", 1, 20),
          symbolPrompt("Enter your preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 3:
        isoscelesTriangle(
          numberPrompt("Enter the height of the triangle: ", 1, 20),
          symbolPrompt("Enter your preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 4:
        house(
          numberPrompt("Enter the height of the house without the roof: ", 1, 20),
          numberPrompt("Enter the width of the house: ", 3, 20),
          symbolPrompt("Enter the preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 5:
        arch(
          numberPrompt("Enter the height of the arch: ", 3, 20),
          symbolPrompt("Enter the preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 6:
        hourGlass(
          numberPrompt("Enter the height of the hourglass: ", 3, 20),
          symbolPrompt("Enter the preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 7:
        ring(
          numberPrompt("Enter the radius of the ring: ", 3, 20),
          symbolPrompt("Enter the preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
    }
    do{
      cout << "\nDo you wish to generate more shapes? (y/n): ";
      cin >> generateMoreShapes;
      if (tolower(generateMoreShapes) != 'y' && tolower(generateMoreShapes) != 'n'){
        cout << "\nInvalid input! Your input must be 'y' or 'n'." << endl;
      }
    } while (tolower(generateMoreShapes) != 'y' && tolower(generateMoreShapes) != 'n');
  } while (tolower(generateMoreShapes) == 'y');

  //Summary
  cout << "Here is a summary of the shapes that were drawn:\n" << endl;
  for (int i = 0; i < 7; i++){
    //Using arrays to automate the print out process
    cout << setw(25) << left << shapes[i] << right << timesGenerated[i] << endl;
  }
  cout << "\nThank you for using the Shape Generator!" << endl;

}