/**
 * @file ZhouEthanA5Code.cpp
 * @author Ethan Zhou
 * @class ICS3U1 (Ms. Wun)
 * @brief A banking app that registers and accesses different accounts and handles transactions. Data is all stored into a text file.
 * @date 2023-05-27
 */

// Basic packages
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iomanip>

// These are all used for locking user out or getting password
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

using namespace std;

// Namespace for time tools
using namespace std::chrono;

struct Account{
  // Struct that keeps track of all the information an account would have
  string password;
  double chequing; // Chequing account balance
  double savings; // Savings account balance
};

int getch() {
    /*
      I have somewhat of a clue of what this does, not really, but it's a helper function for the method that hides passwords.

      Source: https://cplusplus.com/forum/general/88853/
    */
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getpass(string prompt, bool show_asterisk=true){
  /*
    Function for masking input while getting password. No clue how it works, sourced from online.

    This function also sometimes prints stars, sometimes prints nothing, no clue why, but it hides the password

    Source: https://cplusplus.com/forum/general/88853/
  */
  const char BACKSPACE = 127;
  const char RETURN = 10;

  string password;
  unsigned char ch = 0;

  cout << prompt;

  while((ch = getch()) != RETURN){
    if(ch == BACKSPACE){
      if(password.length() != 0){
        if(show_asterisk)
        cout << "\b \b";
        password.resize(password.length() - 1);
      }
    }
    else{
      password += ch;
      if(show_asterisk)
        cout << '*';
    }
  }
  cout << endl;
  return password;
}

bool validPassword(string password) {
  /**
   * @brief Helper function that checks if a password the user wants to use is valid
   * @params: password - the password that needs to be validated
   * @return A boolean that is true when the password is valid, and a false when it's not
   */

  int specialCharCount, upperCases, lowerCases, numbers;
  specialCharCount = upperCases = lowerCases = numbers = 0;

  string specialChars = "!@#$%^&*";

  if (password.length() >= 6 && password.length() <= 15){
    // Making sure the password is 6-15 characters long
    for (int i = 0; i < password.length(); i++){
      if (specialChars.find(password[i]) != -1){
        specialCharCount++;
      }
      if (isupper(password[i])){
        upperCases++;
      } else {
        lowerCases++;
      }
      if (isdigit(password[i])){
        numbers++;
      }
    }
  }

  return (
    specialCharCount > 0 &&
    upperCases > 0 &&
    lowerCases > 0 &&
    numbers > 0
  );

}

string getValidPassword(string prompt){
  string password;

  do {
      // Do-while loop to get a valid password from the user
      password = getpass(prompt);

      if (!validPassword(password)){
        cout << "\nA valid password must contain must be a length of 6 - 15 characters, with at least one uppercase letter, one lowercase letter, one number, and one of the following special characters: !@#$%^&*" << endl;
      }

  } while (!validPassword(password));

  return password;
}

void changePassword(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  /**
   * @brief A method that carries out the logic for changing the password
   * @params: accountData - unorderd map that maps usernames to account data passed by reference
   * @params: currentUsername - current username of the user
   */

  // Input variables
  string oldPassword, newPassword, confirmPassword;

  cout << "\n--UPDATE PASSWORD--\n" << endl;

  do {
    // Error trapping do-loop that makes sure the user enters their own password before changing to new password
    oldPassword = getpass("Enter your current password: ");

    if (oldPassword != accountData[currentUsername].password){
      cout << "\nHOW DO YOU NOT REMEMBER YOUR OWN PASSWORD IDIOT\n" << endl;
    }
  } while (oldPassword != accountData[currentUsername].password);

  do {
    // Do-while loop that makes sure the user enters the same password twice
    newPassword = getValidPassword("\nEnter your new password: ");
    confirmPassword = getValidPassword("\nConfirm your password: ");

    if (newPassword != confirmPassword){
      cout << "\nPlease make sure your passwords match" << endl;
    }

  } while (newPassword != confirmPassword);

  // Assign the new password to the accountData map
  accountData[currentUsername].password = newPassword; 

  cout << "\nYour password has been updated!\n" << endl;
}

void getAccountData(
  unordered_map<string, Account> &accountData
){
  /**
   * @brief Gets account data from the text file to the unordered map accountData
   * @params: accountData - unorderd map that maps usernames to account data passed by reference
   */

  string line, currentUser; // Input variables
  int lineNum = 0; // Counter that keeps track of the line number
  ifstream data ("Data.txt"); // Variable that reads the text file

  if (data.is_open()){
    // Check if the text file can be opened
    while(!data.eof()){
      // Reads every line in the text file until the end of file
      getline(data,line);

      if (line.length() > 0){
        // Checks if the current line is empty
        switch(lineNum % 4){
          // Switch that assigns data to the accountData map according to its remainder divided by 4
          case 0: 
            // First line in a 4 line split
            // Inputs user name
            currentUser = line;
            break;
          case 1: 
            // Second line in a 4 line split
            // Inputs password
            accountData[currentUser].password = line; 
            break;
          case 2: 
            // Third line in a 4 line split
            // Inputs chequing account balance
            accountData[currentUser].chequing = stod(line);
            break;
          case 3: 
            // Fourth line in a 4 line split
            // Inputs savings account balance
            accountData[currentUser].savings = stod(line); 
            break;
        }
        lineNum++; // Incrementing the line number
      }
    }
    data.close();
  } else {
    // Runs when the file cannot open
    cout << "\nCANNOT OPEN FILE" << endl;
  }
}

bool accountExists(
  string username,
  unordered_map<string, Account> &accountData
){
  /**
   * @brief Checks if a username exists
   * @params: username - the username that needs to verify if it exists or not
   * @params: accountData - unorderd map that maps usernames to account data passed by reference
   *  
   * @return a boolean that is true when the account exists, and false when it does not
   */
  auto it = accountData.find(username);

  if (it != accountData.end()){
    return true;
  } else {
    return false;
  }
}

void checkBalance(
  unordered_map<string, Account> &accountData,
  string currentUsername,
  bool fromMenu = true
){
  /**
   * @brief Checks balance of a user
   * @params: accountData - unorderd map that maps usernames to account data passed by reference
   * @params: currentUsername - current username of the user
   * @params: fromMenu - boolean that says whether or not user comes from menu or not, printing different things
   */

  if (fromMenu) {
    // If function is called from menu
    cout << "\n--CHECK BALANCE--" << endl;
  } else {
    cout << "\nYour current balance:\n" << endl;
  }

  // Printing out the account information
  cout << "Chequing Account: $" << fixed << setprecision(2) << accountData[currentUsername].chequing << endl;
  cout << "Savings Account: $" << fixed << setprecision(2) << accountData[currentUsername].savings << endl;
}

void depositMoney(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  /**
   * @brief Method that deposits money into an account
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: username - the username that needs to verify if it exists or not
   */

  char accountName, confirm;
  double depositAmount;

  cout << "\n--DEPOSIT MONEY--\n" << endl;
  cout << "C - Chequing" << endl;
  cout << "S - Savings" << endl;

  do{
    // Do-while loop that lets user choose which account to deposit into with error trapping
    cout << "\nAccount to deposit to: ";
    cin >> accountName;

    if (tolower(accountName) != 'c' && tolower(accountName) != 's'){
      cout << "\nPlease input c or s for chequing or savings account\n" << endl;
    }

  } while (tolower(accountName) != 'c' && tolower(accountName) != 's');

  do{
    // Do-while loop that asks user how much money to deposit, with error trapping
    cout << "Enter amount of money to deposit: $";
    cin >> depositAmount;

    if (depositAmount <= 0){
      cout << "\nError: Insufficient funds!\n" << endl;
    }

  } while (depositAmount <= 0);


  if (tolower(accountName) == 'c'){
    // If user is depositing into chequing account
    do {
      // Do-while loop to confirm deposit amount with user
      cout << "\n$" << fixed << setprecision(2) << depositAmount << " to deposit into chequing account (y/n): ";
      cin >> confirm;

      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }

    } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');

    if (tolower(confirm) == 'y'){
      // Handles the transaction
      accountData[currentUsername].chequing += depositAmount;

      cout << "\n$" << fixed << setprecision(2) << depositAmount << " deposited into chequing account" << endl;

      checkBalance(accountData, currentUsername, false); // Shows balance again
    } else {
      // Scream at the indecisive user
      cout << "\nMAKE UP YOUR MIND NEXT TIME" << endl;
    }
  } else {
    // Same logic as above, except for savings account
    do {
      cout << "\n$" << fixed << setprecision(2) << depositAmount << " to deposit into savings account (y/n): ";
      cin >> confirm;

      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }

    } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');

    if (tolower(confirm) == 'y'){
      accountData[currentUsername].savings += depositAmount;

      cout << "\n$" << fixed << setprecision(2) << depositAmount << " deposited into savings account" << endl;

      checkBalance(accountData, currentUsername, false);
    } else {
      // Scream at the indecisive user again
      cout << "\nMAKE UP YOUR MIND NEXT TIME" << endl;
    }
  }
}

void withdrawMoney(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  /**
   * @brief Method that handles logic to withdraw money from account
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: currentUsername - current username of the user
   */

  double withdrawAmount;
  char confirm;

  cout << "\n--WITHDRAW MONEY--\n" << endl;

  do {
    // Asking user amount of money to withdraw from chequing account with error trapping
    cout << "Enter amount of money to withdraw: ";
    cin >> withdrawAmount;

    if (withdrawAmount > accountData[currentUsername].chequing){
      // If insufficient funds
      cout << "\nERROR: Insufficient funds!" << endl;
    } else if (withdrawAmount < 0){
      // If withdrawing negative amounts of money
      cout << "\nERROR: Cannot withdraw negative amounts" << endl;
    }
  } while (
    withdrawAmount > accountData[currentUsername].chequing || 
    withdrawAmount < 0
  );

  do{
    // Do-while loop to confirm if the user wants to withdraw this amount of money, with error trapping
    cout << "\n$" << fixed << setprecision(2) << withdrawAmount << " to withdraw from chequing account (y/n): ";
    cin >> confirm;

    if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
      cout << "\nPlease type y or n for yes or no\n" << endl;
    }

  } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');

  if (tolower(confirm) == 'y'){
    // Handles the transaction
    accountData[currentUsername].chequing -= withdrawAmount;

    cout << "\n$" << fixed << setprecision(2) << withdrawAmount << " withdrawn from chequing account" << endl;
  } else {
    // Sream at the indecisive user
    cout << "\nMAKE UP YOUR MIND NEXT TIME" << endl;
  }
}

void transferMoney(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  /**
   * @brief Method that transfers money between chequing and savings accounts
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: currentUsername - current username of the user
   */

  char from, to, confirm;
  double transferAmount;

  cout << "\n--TRANSFER MONEY--\n" << endl;
  cout << "C - Chequing" << endl;
  cout << "S - Savings" << endl;

  do{
    // Letting the user select account to transfer from with error trapping
    cout << "\nAccount to transfer from: ";
    cin >> from;

    if (tolower(from) != 'c' && tolower(from) != 's'){
      cout << "\nPlease input c or s for chequing or savings account\n" << endl;
    }

  } while (tolower(from) != 'c' && tolower(from) != 's');

  do{
    // Letting the user select account to transfer to with error trapping
    cout << "\nAccount to transfer to: ";
    cin >> to;

    if (tolower(to) != 'c' && tolower(to) != 's'){
      // Invalid account input
      cout << "\nPlease input c or s for chequing or savings account" << endl;
    } else if (tolower(from) == tolower(to)){
      // Invalid account to transfer to
      cout << "\nERROR: You cannot transfer to the same account" << endl;
    }
  } while (
    (
      tolower(to) != 'c' && 
      tolower(to) != 's' 
    ) || (
      tolower(from) == tolower(to)
    )
  );

  if (tolower(from) == 'c'){
    // If user is transferring to savings
    do{
      // Entering amount to transfer with error trapping
      cout << "\nEnter transfer amount: ";
      cin >> transferAmount;

      if (transferAmount > accountData[currentUsername].chequing){
        // Insufficient funds
        cout << "\nERROR: Insufficient funds!" << endl;
      } else if (transferAmount < 0){
        // Transferring negative money
        cout << "\nERROR: Cannot transfer negative amounts" << endl;
      }
    } while (
      transferAmount > accountData[currentUsername].chequing ||
      transferAmount < 0
    );

    do{
      // Confirming transaction with user with error trapping
      cout << "\n$" << fixed << setprecision(2) << transferAmount << " to be transferred from chequing to savings? (y/n): ";
      cin >> confirm;

      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }

    } while (
      tolower(confirm) != 'y' &&
      tolower(confirm) != 'n'
    );

    if (tolower(confirm) == 'y'){
      // Handling transaction
      accountData[currentUsername].savings += accountData[currentUsername].chequing;

      cout << "\n$" << fixed << setprecision(2) << transferAmount << " transferred from chequing account to savings" << endl;
    } else {
      // Scream at the indecisive user
      cout << "\nMAKE UP YOUR MIND NEXT TIME" << endl;
    }
  } else {
    // Same logic as above, except transferring from savings to chequing
    do{
      cout << "\nEnter transfer amount: ";
      cin >> transferAmount;
      if (transferAmount > accountData[currentUsername].savings){
        cout << "\nERROR: Insufficient funds!" << endl;
      } else if (transferAmount < 0){
        cout << "\nERROR: Cannot transfer negative amounts" << endl;
      }
    } while (
      transferAmount > accountData[currentUsername].savings ||
      transferAmount < 0
    );

    do{
      cout << "\n$" << fixed << setprecision(2) << transferAmount << " to be transferred from savings to chequing? (y/n): ";
      cin >> confirm;
      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }
    } while (
      tolower(confirm) != 'y' &&
      tolower(confirm) != 'n'
    );

    if (tolower(confirm) == 'y'){
      accountData[currentUsername].chequing += accountData[currentUsername].savings;
      cout << "\n$" << fixed << setprecision(2) << transferAmount << " transferred from savings account to chequing" << endl;
    } else {
      cout << "\nMAKE UP YOUR MIND NEXT TIME" << endl;
    }
  }
}

void writeToTextFile(
  unordered_map<string, Account> &accountData
){
  /**
   * @brief Writing all the data stored in accountData to the text file
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   */
  ofstream data ("Data.txt");

  if (data.is_open()){
    // If text file opens
    for (const auto& account : accountData){
      // Iterating through the unordered map and inserting according values into the text file
      data << account.first << endl;
      data << account.second.password << endl;
      data << account.second.chequing << endl;
      data << account.second.savings << endl;
    }
    data.close();
  } else {
    // File cannot be opened
    cout << "\nERROR: CANNOT OPEN FILE" << endl;
  }
}

void logIn(
  unordered_map<string, Account> &accountData,
  string &currentUsername,
  string &currentPassword
){
  /**
   * @brief Method that handles logging into a bank account
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: currentUsername - current username of the user
   * @params: currentPassword - current password of the user
   */
  int passwordTries = 5; // Number of tries user gets to log in

  do{
    // Gets username from user, with error trapping to see if account exists
    cout << "\nUsername: ";
    cin >> currentUsername;

    if (!accountExists(currentUsername, accountData)){
      cout << "\nERROR: Non-Existent account, try again" << endl;
    }

  } while (!accountExists(currentUsername, accountData));

  do{
    // Do-while loop to get password from user, with error trapping and locking out user
    currentPassword = getpass("\nPassword: ");

    if (currentPassword != accountData[currentUsername].password){
      // If password is wrong
      passwordTries--; // Decrement number of tries
      if (passwordTries > 0){
        // Gives a message to tell user how many tries they have left
        cout << "\nERROR: Wrong password, you have " << passwordTries << " tr" << (passwordTries > 1 ? "ies" : "y") << " left." << endl;
      }
    }
    if (passwordTries == 0){
      // When the user is out of tries
      cout << "\nERROR: Too many tries, you will be locked for 30 seconds" << endl;
      passwordTries = 5;
      this_thread::sleep_for(seconds(30)); // Sleep program for 30 seconds
    }
  } while (currentPassword != accountData[currentUsername].password);
}

void signUp(
  unordered_map<string, Account> &accountData,
  string &currentUsername,
  bool &loggedIn
){
  /**
   * @brief Sign up for a new bank account
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: currentUsername - current username of the user
   * @params: loggedIn - current log in status of the program
   */

  string newUsername, newPassword, confirmPassword;
  char confirm;

  cout << "\n--SIGN UP--" << endl;

  do {
    // Do-while loop to get new username, and checks for username overlaps
    cout << "\nEnter your username: ";
    cin >> newUsername;

    if (accountExists(newUsername, accountData)){
      cout << "\nAccount exists, pick another username" << endl;
    }

  } while (accountExists(newUsername, accountData));

  do {
    // Do-while loop to make sure the password is confirmed properly
    newPassword = getValidPassword("\nEnter your new password: ");
    confirmPassword = getValidPassword("\nConfirm your password: ");

    if (newPassword != confirmPassword){
      cout << "\nPlease make sure your passwords match" << endl;
    }

  } while (newPassword != confirmPassword);

  do {
    // Do-while loop to ask if user wants to be logged into their account
    cout << "\nDo you wish to be logged into your new account? (y/n): ";
    cin >> confirm;

    if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
    }

  } while (
    tolower(confirm) != 'y' &&
    tolower(confirm) != 'n'
  );

  // Add information to the map
  currentUsername = newUsername;
  accountData[currentUsername].password = newPassword;
  accountData[currentUsername].chequing = 0;
  accountData[currentUsername].savings = 0;

  // Change the log in status according to whether or not user wants to log in
  loggedIn = (tolower(confirm) == 'y'); 

  writeToTextFile(accountData); // Write the map into the text file
}

void toContinue(){
  /**
   * @brief Asks the user to input a character to continue with the program
   */
  char inputChar;

  cout << "\nType any character to continue: ";
  cin >> inputChar;
}

int printMenu(
  string &currentUsername,
  unordered_map<string, Account> &accountData
){
  /**
   * @brief Prints out the bank dashboard/menu for operations
   * @params: accountData - unorderd map that maps usernames to account data passed by reference 
   * @params: currentUsername - current username of the user
   * @return integer representing the choice the user inputted
   */
  int option; // Keeps track of user's choice

  cout << "\n***\nHello " << currentUsername << endl;
  cout << "\n1) Update Your Password" << endl;
  cout << "2) Check Your Balance" << endl;
  cout << "3) Deposit Money" << endl;
  cout << "4) Withdraw Money" << endl;
  cout << "5) Transfer Money" << endl;
  cout << "6) Sign Out" << endl;

  do{
    //Do-while loop to get the option from the user with error trapping
    cout << "\nEnter your option (1-6): ";
    cin >> option;

    if (option < 1 && option > 6){
      cout << "\nInvalid option! Your choice must be between 1 and 6." << endl;
    }

  } while (option < 1 && option > 6);

  return option;
}

int main(){
  // Star of the show, unordered map that maps usernames to their information
  unordered_map<string, Account> accountData;
  // Strings that keep track of current username and password
  string currentUsername, currentPassword;

  while(true){
    // Continues program until user stops
    bool loggedIn = true; // Variable to track current login status
    int menuChoice; // First mini menu choice

    cout << "\n$$$ BANK OF HAIG $$$" << endl;

    getAccountData(accountData); // Get the data from the text file

    do {
      // Do-while loop that gets user's choice on the first menu
      cout << "\n1) Log In" << endl;
      cout << "2) Sign Up" << endl;
      cout << "\nType 1 to log in and 2 to sign up: ";
      cin >> menuChoice;

      if (menuChoice < 1 && menuChoice > 2){
        cout << "\nErorr: Invalid option" << endl;
      }

    } while (menuChoice < 1 && menuChoice > 2);

    if (menuChoice == 1){
      // Log in
      logIn(accountData, currentUsername, currentPassword);
    } else {
      // Sign up for new account
      signUp(accountData, currentUsername, loggedIn);
    }

    while (loggedIn){
      // While the user is logged in
      switch(printMenu(currentUsername, accountData)){ // Get choice from menu
        case 1:
          // Change password
          changePassword(accountData, currentUsername); 
          toContinue();
          break;
        case 2:
          // Check balance
          checkBalance(accountData, currentUsername);
          toContinue();
          break;
        case 3:
          // Deposit money
          depositMoney(accountData, currentUsername);
          toContinue();
          break;
        case 4:
          // Withdraw money
          withdrawMoney(accountData, currentUsername);
          toContinue();
          break;
        case 5:
          // Transfer money
          transferMoney(accountData, currentUsername);
          toContinue();
          break;
        case 6:
          // Sign out
          system("clear"); // Clear console
          loggedIn = false;
          writeToTextFile(accountData); // Write all data to text file
          break;
      }
    }
  }

  return 0;
}