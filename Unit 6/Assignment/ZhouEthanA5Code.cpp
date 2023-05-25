#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <thread>

using namespace std;
using namespace std::chrono;

struct Account{
  string password;
  double chequing;
  double savings;
};

int getch() {
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
  const int numOfSpecialChars = 8;

  char specialChars[numOfSpecialChars] = {'!', '@', '#', '$', '%', '^', '&', '*'};
  if (password.length() >= 6 && password.length() <= 15){
    for (int i = 0; i < numOfSpecialChars; i++){
      if (password.find(specialChars[i]) != -1){
        return true;
      }
    }
  }

  return false;
}

void changePassword(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  string oldPassword, newPassword;
  cout << "\n--UPDATE PASSWORD--\n" << endl;

  do {
    oldPassword = getpass("Enter your current password: ");
    if (oldPassword != accountData[currentUsername].password){
      cout << "\nHOW DO YOU NOT REMEMBER YOUR OWN PASSWORD IDIOT\n" << endl;
    }
  } while (oldPassword != accountData[currentUsername].password);

  do {
    newPassword = getpass("\nEnter your new password: ");

    if (!validPassword(newPassword)){
      cout << "\nA valid password must contain must be a length of 6 - 15 characters, with at least one uppercase letter, one lowercase letter, one number, and one of the following special characters: !@#$%^&*\n" << endl;
    }
  } while (!validPassword(newPassword));

  accountData[currentUsername].password = newPassword;
}

void getAccountData(unordered_map<string, Account> &accountData){
  string line;
  string currentUser;
  int lineNum = 0;
  ifstream data ("Data.txt");

  if (data.is_open()){
    while(!data.eof()){
      getline(data,line);
      switch(lineNum % 4){
        case 0: currentUser = line; break;
        case 1: accountData[currentUser].password = line; break;
        case 2: accountData[currentUser].chequing = stod(line); break;
        case 3: accountData[currentUser].savings = stod(line); break;
      }
      lineNum++;
    }
    data.close();
  } else {
    cout << "CANNOT OPEN FILE" << endl;
  }
}

bool accountExists(string accountName, unordered_map<string, Account> &accountData){
  auto it = accountData.find(accountName);
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
  if(fromMenu){
    cout << "\n--CHECK BALANCE--\n" << endl;
  } else {
    cout << "\nYour current balance:\n" << endl;
  }
  cout << "Chequing Account: $" << fixed << setprecision(2) << accountData[currentUsername].chequing << endl;
  cout << "Savings Account: $" << fixed << setprecision(2) << accountData[currentUsername].savings << endl;
}

void depositMoney(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  char accountName;
  double depositAmount;

  cout << "\n--DEPOSIT MONEY--\n" << endl;
  cout << "C - Chequing" << endl;
  cout << "S - Savings" << endl;

  do{
    cout << "\nAccount to deposit to: ";
    cin >> accountName;
    if (tolower(accountName) != 'c' && tolower(accountName) != 's'){
      cout << "\nPlease input c or s for chequing or savings account\n" << endl;
    }
  } while (tolower(accountName) != 'c' && tolower(accountName) != 's');

  do{
    cout << "Enter amount of money to deposit: $";
    cin >> depositAmount;
    if (depositAmount <= 0){
      cout << "\nError: Insufficient funds!\n" << endl;
    }
  } while (depositAmount <= 0);

  char confirm;

  if (tolower(accountName) == 'c'){
    do {
      cout << "\n$" << fixed << setprecision(2) << depositAmount << " to deposit into chequing account (y/n): ";
      cin >> confirm;
      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }
    } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');

    if (tolower(confirm) == 'y'){
      accountData[currentUsername].chequing += depositAmount;
      cout << "\n$" << fixed << setprecision(2) << depositAmount << " deposited into chequing account" << endl;
      checkBalance(accountData, currentUsername, false);
    } else {
      cout << "\nMAKE UP YOUR MIND NEXT TIME\n" << endl;
    }
  } else {
    do {
      cout << '$' << fixed << setprecision(2) << depositAmount << " to deposit into savings account (y/n): ";
      cin >> confirm;
      if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
        cout << "\nPlease type y or n for yes or no\n" << endl;
      }
    } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');
    if (tolower(confirm) == 'y'){
      accountData[currentUsername].savings += depositAmount;
      cout << '$' << fixed << setprecision(2) << depositAmount << " deposited into savings account" << endl;
      checkBalance(accountData, currentUsername, false);
    } else {
      cout << "\nMAKE UP YOUR MIND NEXT TIME\n" << endl;
    }
  }
}

void withdrawMoney(
  unordered_map<string, Account> &accountData,
  string currentUsername
){
  //error check for negatives
  double withdrawAmount;
  cout << "\n--WITHDRAW MONEY--\n" << endl;
  do {
    cout << "Enter amount of money to withdraw: ";
    cin >> withdrawAmount;
    if (withdrawAmount > accountData[currentUsername].chequing){
      cout << "\nERROR: Insufficient funds!\n" << endl;
    } else if (withdrawAmount < 0){
      cout << "\nError: Cannot withdraw negative amounts\n" << endl;
    }
  } while (withdrawAmount > accountData[currentUsername].chequing || withdrawAmount < 0);

  char confirm;
  do{
    cout << '$' << fixed << setprecision(2) << withdrawAmount << " to withdraw from chequing account (y/n): ";
    cin >> confirm;
    if (tolower(confirm) != 'y' && tolower(confirm) != 'n'){
      cout << "\nPlease type y or n for yes or no\n" << endl;
    }
  } while (tolower(confirm) != 'y' && tolower(confirm) != 'n');

  if (tolower(confirm) == 'y'){
    accountData[currentUsername].chequing -= withdrawAmount;
    cout << '$' << fixed << setprecision(2) << withdrawAmount << " withdrawn from chequing account" << endl;
  } else {
    cout << "\nMAKE UP YOUR MIND NEXT TIME\n" << endl;
  }
}

void logIn(
  unordered_map<string, Account> &accountData,
  string &currentUsername,
  string &currentPassword
){
  int passwordTries = 5;
  cout << "$$$ BANK OF HAIG $$$" << endl;

  do{
    cout << "\nUsername: ";
    cin >> currentUsername;
    if (!accountExists(currentUsername, accountData)){
      cout << "\nERROR: Non-Existent account, try again" << endl;
    }
  } while (!accountExists(currentUsername, accountData));

  do{
    currentPassword = getpass("\nPassword: ");
    if (currentPassword != accountData[currentUsername].password){
      passwordTries--;
      if (passwordTries > 0){
        cout << "\nERROR: Wrong password, you have " << passwordTries << " tr" << (passwordTries > 1 ? "ies" : "y") << " left." << endl;
      }
    }
    if (passwordTries == 0){
      cout << "\nERROR: Too many tries, you will be locked for 30 seconds" << endl;
      passwordTries = 5;
      this_thread::sleep_for(seconds(30));
    }
  } while (currentPassword != accountData[currentUsername].password);
}

int printMenu(
  string &currentUsername,
  unordered_map<string, Account> &accountData
){
  int option;

  do{
    cout << "\nHello " << currentUsername << endl;
    cout << "\n1) Update Your Password" << endl;
    cout << "2) Check Your Balance" << endl;
    cout << "3) Deposit Money" << endl;
    cout << "4) Withdraw Money" << endl;
    cout << "5) Transfer Money" << endl;
    cout << "6) Sign Out" << endl;
    cout << "\nEnter your option (1-6): ";
    cin >> option;
    if (option < 1 && option > 6){
      cout << "\nInvalid option! Your choice must be between 1 and 6.\n" << endl;
    }
  } while (option < 1 && option > 6);

  return option;
}

int main(){
  unordered_map<string, Account> accountData;
  string currentUsername, currentPassword;

  while(true){
    bool loggedIn = false;
    getAccountData(accountData);
    logIn(accountData, currentUsername, currentPassword);
    loggedIn = true;

    while (loggedIn){
      switch(printMenu(currentUsername, accountData)){
        case 1:
          changePassword(accountData, currentUsername); 
          break;
        case 2:
          checkBalance(accountData, currentUsername);
          break;
        case 3:
          depositMoney(accountData, currentUsername);
          break;
        case 4:
          withdrawMoney(accountData, currentUsername);
          break;
        case 6:
          system("clear");
          loggedIn = false;
          break;
      }
    }
  }

  return 0;
}