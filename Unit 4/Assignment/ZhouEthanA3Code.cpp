#include <iostream>
#include <cctype>
using namespace std;

void horizontalLine(int length, char symbol){
  for (int i = 0; i < length; i++){
    cout << symbol;
  }
  cout << endl;
}

void verticalLine(int height, char symbol){
  for (int i = 0; i < height; i++){
    cout << symbol << endl;
  }
}

void isoscelesTriangle(int height, char symbol){
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

void arch(int height, char symbol){
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

void house(int heightWithoutRoof, int base ,char symbol){
  isoscelesTriangle(base, symbol);
  for (int i = 0; i < heightWithoutRoof - 1; i++){
    for (int j = 0; j < base; j++){
      cout << symbol << ' ';
    }
    cout << endl;
  }
}

void diamond(int width, char symbol){
  isoscelesTriangle(width, symbol);
  for (int i = width - 1; i >= 0; i--){
    for (int j = 0; j < width - i; j++){
      cout << ' ';
    }
    for (int j = 0; j < i; j++){
      cout << symbol << ' ';
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
  cout << "Welcome to the Shape Generator!\n" << endl;
  cout << "This program draws the following shapes:\n" << endl;
  cout << "\t1) Horizontal Line" << endl;
  cout << "\t2) Vertical Line" << endl;
  cout << "\t3) Isosceles Triangle" << endl;
  cout << "\t4) House" << endl;
  cout << "\t5) Arch" << endl;
  cout << "\t6) Hourglass" << endl;
  cout << "\t7) Diamond" << endl;
  cout << endl;

  char generateMoreShapes;
  do{
    int selection;
    do{
      cout << "Enter your choice (1-7): ";
      cin >> selection;
      switch(selection){
        case 1:
          horizontalLine(
            numberPrompt("Enter the horizontal line's length: ", 1, 20),
            symbolPrompt("Enter your preferred symbol: ")
          );
          break;
        case 2:
          verticalLine(
            numberPrompt("Enter the vertical line's height: ", 1, 20),
            symbolPrompt("Enter your preferred symbol: ")
          );
          break;
        case 3:
          isoscelesTriangle(
            numberPrompt("Enter the height of the triangle: ", 1, 20),
            symbolPrompt("Enter your preferred symbol: ")
          );
          break;
        case 4:
          house(
            numberPrompt("Enter the height of the house without the roof: ", 1, 20),
            numberPrompt("Enter the width of the house: ", 1, 20),
            symbolPrompt("Enter the preferred symbol: ")
          );
          break;
        case 5:
          arch(
            numberPrompt("Enter the height of the arch: ", 2, 20),
            symbolPrompt("Enter the preferred symbol: ")
          );
          break;
        case 6:
          hourGlass(
            numberPrompt("Enter the height of the hourglass: ", 3, 20),
            symbolPrompt("Enter the preferred symbol: ")
          );
          break;
        case 7:
          diamond(
            numberPrompt("Enter the width of the diamond: ", 3, 20),
            symbolPrompt("Enter the preferred symbol: ")
          );
          break;
        default:
          cout << "Invalid input! Enter a number between 1 to 7 please" << endl;
          break;
      }
    } while (selection < 0 || selection > 7);
    do{
      cout << "Do you wish to generate more shapes? (y/n): ";
      cin >> generateMoreShapes;
      if (tolower(generateMoreShapes) != 'y' && tolower(generateMoreShapes) != 'n'){
        cout << "Invalid input! Your input must be 'y' or 'n'." << endl;
      }
    } while (tolower(generateMoreShapes) != 'y' && tolower(generateMoreShapes) != 'n');
  } while (tolower(generateMoreShapes) == 'y');
}