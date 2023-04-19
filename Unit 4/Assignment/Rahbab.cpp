#include <iostream>
#include <string>
using namespace std;

int main() {
  
  //general variables
  char symbol;
  int choice;
  bool repeat = true;

  //variables for shape 1
  string symbol1;
  int width1;

  //variables for shape 2
  string symbol2;
  int height2;

  //variables for shape 3
  string symbol3;
  int height3;

  //variables for shape 4
  string symbol4;
  int height4, width4;

  //variables for shape 5
  string symbol5;
  int height5;

  //variables for shape 6
  string symbol6;
  int height6;

  cout << "Welcome to the Shape Generator!" << endl;

  do {
    cout << endl;
    cout << "This program draws the following shapes:" << endl;
    cout << "\n1) Horizontal Line" << endl;
    cout << "2) Vertical Line" << endl;
    cout << "3) Isosceles Triangle" << endl;
    cout << "4) House" << endl;
    cout << "5) Arch" << endl;
    cout << "6) Hourglass" << endl;
    cout << "7) Diamond" << endl;
    cout << "\nEnter your choice (1-7): ";
    cin >> choice;

    //Shape 1
    if (choice == 1){
      //prompt user for dimensions
      cout << "\nEnter your preferred symbol: ";
      cin >> symbol1;
      cout << "Enter the length of your horizontal line (1-20): ";
      cin >> width1; 
      while (width1 < 1 || width1 > 20){ 
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> width1;
      }
      //Code to make the shape using loops
      for (int i = 0; i < width1; i++){
        cout << symbol1;
      } 
    } else if (choice == 2) {
    //Shape 2
    //prompt user for dimensions
      cout << "\nEnter your preferred symbol: ";
      cin >> symbol2;
      cout << "Enter the length of your vertical line (1-20): ";
      cin >> height2; 
      while (height2 < 1 || height2 > 20){
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height2;
      }
      //Code to make the shape using loops
      for (int i = 0; i < height2; i++) {
        cout << symbol2 << endl;
      }
    }else if (choice == 3){
      //Shape 3
      //prompt user for dimensions
      cout << "\nEnter your preferred symbol: ";
      cin >> symbol3;
      cout << "Enter your height of your isosceles triangle (1-20): ";
      cin >> height3;

      while (height3 < 1 || height3 > 20){
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height3;
      }

      //Code to make the shape using loops
      for (int i = 0; i < height3; i++){
        for (int j = 0; j < height3 - i - 1; j++){
          cout << " ";
        }

        for (int j = 0; j < 2 * i + 1; j++){ 
          cout << symbol3;
        }

        cout << endl;
      }
    }else if (choice == 4){
    //Shape 4
    //prompt user for dimensions

      cout << "\nEnter your preferred symbol: ";
      cin >> symbol4;
      cout << "\nEnter the base of house (1-20): ";
      cin >> width4;
      while (width4 < 1 || width4 > 20){ 
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height4;
      }

      cout << "\nEnter the height of the house without a roof (1-20): ";
      cin >> height4;
      while (height4 < 1 || height4 > 20) { 
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height4;
      }

      for (int i = 1; i < height4; i++) {
        for (int j = 1; j <= 3 - i; j++) {
            cout << " ";
        }
        for (int j = 1; j <= i * 2 - 1; j++) {
            cout << symbol4;
        }
        cout << endl;
      }

      for (int i = 1; i <= height4; i++) {
        for (int j = 1; j <= width4; j++) {
            cout << symbol4;
        }
        cout << endl;
      }
    }else if (choice == 5){
    //Shape 5 (add comments for this one)

    //prompt user for dimensions

      cout << "\nEnter your preferred symbol: ";
      cin >> symbol5;
      cout << "\nEnter the height of your arch (1-20): ";
      cin >> height5;
      while (height5 < 1 || height5 > 20){
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height5;
      }

      cout << endl;

      for (int i = height5; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << symbol5;
        }
        for (int j = 1; j <= (height5 - i) * 2; j++) {
            cout << " ";
        }
        for (int j = 1; j <= i; j++) {
            cout << symbol5;
        }
        cout << endl;
      }
    }else if (choice == 6){
    //shape 6
    //prompt user for dimensions

      cout << "\nEnter your preferred symbol: ";
      cin >> symbol6;
      cout << "\nEnter the base of your hourglass (1-20): ";
      cin >> height6;
      while (height6 < 1 || height6 > 20){
        cout << "Invalid dimension! The dimension must be between 1 and 20: ";
        cin >> height6;
      }

      cout << endl;

      for (int i = height6; i >= 1; i--){
        for (int j = 1; j <= height6 - i; j++){
          cout << " ";
        }
        for (int j = 1; j <= 2 * i - 1; j++){
          cout << symbol6;
        }
        cout << endl;
      }
      
      for (int i = 2; i <= height6; i++) {
        for (int j = 1; j <= height6 - i;j++){
          cout << " ";
        }
        for (int j = 1; j <= 2 * i - 1;j++) {
          cout << symbol6;
        }
        cout << endl;
      } 
    }
  } while (repeat);
}
