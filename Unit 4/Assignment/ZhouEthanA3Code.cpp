/*
  Unit 4, Assignment 3, Shape Generator

  Written by: Ethan Zhou
  Written for: Ms.Wun
  Date: April 14th 2023
*/

//include statements
#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

void horizontalLine(int length, char symbol){
  /*
    Method that prints out a horizontal line with a specific symbol character

    Parameters:
      length: integer that stores the length of the line
      symbol: the preferred symbol that the user wants the horizontal line to be made with
  */
  cout << "Here is a horizontal line with the length of " << length << ":\n" << endl;
  for (int i = 0; i < length; i++){
    cout << symbol;
  }
  cout << endl;
}

void verticalLine(int height, char symbol){
  /*
    Method that prints out a vertical line with a specific symbol character

    Parameters:
      height: integer that stores the height of the line
      symbol: the preferred symbol that the user wants the vertical line to be made with
  */
  cout << "Here is vertical line with the height of " << height << ":\n" << endl;
  for (int i = 0; i < height; i++){
    cout << symbol << endl;
  }
}

void isoscelesTriangle(int height, char symbol){
  /*
    Method that prints out an isosceles triangle with a specific symbol character

    Parameters:
      height: integer that stores the height of the triangle
      symbol: the preferred symbol that the user wants the triangle to be made with
  */
  cout << "Here is an isosceles triangle with the height of " << height << ":\n" << endl;

  for (int i = 1; i <= height; i++){
    //Using spaces to indent the symbols to put it in the right place
    for (int j = 0; j < height - i; j++){
      //Printing spaces to indent symbol with
      cout << ' ';
    }
    for (int j = 0; j < i; j++){
      //Printing the symbol and the space after the symbol for correct spacing
      cout << symbol << ' ';
    }
    //Starting a new layer of the triangle
    cout << endl;
  }
}

void house(int heightWithoutRoof, int base ,char symbol){
  /*
    Method that prints out a house with the parameters below:

    Parameters:
      heightWithoutRoof: integer that stores the height of the roof
      base: width of the house
      symbol: the preferred symbol that the user wants the house to be made with
  */
  cout << "Here is a house with the base of " << base << " and the height without the roof of " << heightWithoutRoof << ":\n" << endl;

  //Uses the isoscelesTriangle method to print the roof
  isoscelesTriangle(base, symbol);

  for (int i = 0; i < heightWithoutRoof - 1; i++){
    //Printing the bottom rectangle of the house
    for (int j = 0; j < base; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

void arch(int height, char symbol){
  /*
    Method that prints out an arch with the parameters below:

    Parameters:
      height: integer that stores the height of the arch
      symbol: the preferred symbol that the user wants the arch to be made with
  */
  cout << "Here is arch with the height of " << height << ":\n" << endl;

  for (int i = 0; i <= height; i++){
    //Iterates through the height of the arch
    for (int j = 0; j < height - i; j++){
      //Prints out the first half of the arch
      cout << symbol;
    }
    for (int j = 0; j < i; j++){
      //Prints out the spacing in the middle
      cout << "  ";
    }
    for (int j = 0; j < height - i; j++){
      //Prints out the second half of the arch
      cout << symbol;
    }
    //Starts new layer of the arch
    cout << endl;
  }
}


void hourGlass(int base, char symbol){
  /*
    Method that prints out an hour glass with the parameters below:

    Parameters:
      base: integer that stores the base width of the hour glass
      symbol: the preferred symbol that the user wants the hour glass to be made with
  */
  cout << "Here is an hourglass with the base of " << base << ":\n" << endl;

  if (base % 2 == 1){
    //When the base is an odd number

    //Variable to keep track of the halfway point on an odd number base (I don't really know why this is here anymore but it works so I can't be bothered to change it)
    int halfWay = (base/2) + 1;

    for (int i = base; i > 0; i -= 2){
      //Loop that skips 2 to ensure that the top upside down triangle goes down by 2 every cycle
      for (int j = 1; j < halfWay - i/2; j++){
        //Prints out the spacing
        cout << ' ';
      }
      for (int j = 0; j < i; j++){
        //Prints out the symbol
        cout << symbol;
      }
      //New layer of the hour glass
      cout << endl;
    }

    for (int i = 2; i < base; i += 2){
      //Loop that skips 2 to ensure that the bottom triangle goes down by 2 every cycle, making sure to skip the middle
      for (int j = 1; j < halfWay - i/2; j++){
        //Prints out the spacing
        cout << ' ';
      }
      for (int j = 0; j <= i; j++){
        //Prints out the symbol
        cout << symbol;
      }
      //New layer of the hour glass
      cout << endl;
    }
  } else {
    //Same algorithm as above, except numbers work better with even numbers, so no need to mitigate integer division problems with the halfway variable
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
  /*
    Method that prints out a ring/crooked circle using the mathematical fact that x^2 + y^2 = radius^2

    Parameters:
      radius: integer that stores the radius of the ring/crooked circle
      symbol: the preferred symbol that the user wants the ring/crooked circle to be made with
  */

  cout << "Here is a ring with the radius of " << radius << ":\n" << endl;

  //Number to compare the x and y values to
  int expectedValue = pow(radius, 2);

  for (int y = -radius; y <= radius; y++) {
    //Making sure to iterate through the entire space the circle could take up
    for (int x = -radius; x <= radius; x++) {
      //Same here

      //Variable to check if current coordinate belongs on the circle
      int computedValue = pow(x,2) + pow(y,2);

      if (abs(computedValue - expectedValue) <= radius) {
        //When coordinate is on circle, print symbol, if not, print space
        cout << symbol;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
}

int numberPrompt(string prompt, int lowestValue, int highestValue){
  /*
    Organising the error trapping for all the dimension inputs into one method

    Parameters:
      prompt: a string prompt that gets outputted to get input from
      lowestValue: the lowest number the input can be
      highestValue: the highest number the input can be

    Return value:
      returns an integer that is acceptable
  */

  int inputValue;
  do{
    //Simple do-while operation that keeps looping to get input from user until the input is valid
    cout << prompt;
    cin >> inputValue;

    if (inputValue < lowestValue || inputValue > highestValue){
      cout << "Invalid Dimension! The dimension must be between " << lowestValue << " and " << highestValue << "." << endl;
    }
  } while (inputValue < lowestValue || inputValue > highestValue);

  return inputValue;
}

char symbolPrompt(string prompt){
  /*
    I'm gonna have to do this operation so many times so I decided to cram it into a method

    Parameters:
      prompt: a string prompt that gets outputted to get input from

    Return value:
      returns a char that gets inputted
  */

  //Quite a simple operation down here to get a char input
  char symbol;
  cout << prompt;
  cin >> symbol;
  return symbol;
}

int main(){
  char generateMoreShapes; //A char to keep track if the user wants to continue generating shapes
  int selection; //Integer to keep track which shape user wants to generate

  string shapes[7] = {
    "Horizontal Line",
    "Vertical Line",
    "Isosceles Triangle",
    "House",
    "Arch",
    "Hourglass",
    "Ring"
  }; //An array of all the shape names

  int timesGenerated[7] = {0,0,0,0,0,0,0}; //An array to keep track of how many times each shape has been generated
  
  //Main menu print
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
          numberPrompt("Enter the horizontal line's length: ", 2, 20),
          symbolPrompt("Enter your preferred symbol: ")
        );
        //This line of code adds 1 to the array that keeps track of how many times each shape is generated to the according choice
        timesGenerated[selection - 1] += 1;
        break;
      case 2:
        verticalLine(
          numberPrompt("Enter the vertical line's height: ", 2, 20),
          symbolPrompt("Enter your preferred symbol: ")
        );
        timesGenerated[selection - 1] += 1;
        break;
      case 3:
        isoscelesTriangle(
          numberPrompt("Enter the height of the triangle: ", 2, 20),
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
      //Do while that error traps an input for if the user wants to generate more shapes or not
      cout << "\nDo you wish to generate more shapes? (y/n): ";
      cin >> generateMoreShapes;
      if (tolower(generateMoreShapes) != 'y' && tolower(generateMoreShapes) != 'n'){
        //Takes out case sensitivity with tolower()
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