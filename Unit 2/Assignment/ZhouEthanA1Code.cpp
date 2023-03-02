#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

int main(){
  //Initial print outs
  cout << "FAMILY BUDGET SOFTWARE ver.2023\n" << endl;
  cout << "----------------------------------------------------------------------\n" << endl;
  cout << "Please enter the name of the following family members:\n" << endl;


  //Name gathering
  string parentOneName, parentTwoName, childName;

  cout << "Parent 1: ";
  cin >> parentOneName;
  cout << "Parent 2: ";
  cin >> parentTwoName;
  cout << "Child: ";
  cin >> childName;

  //Income gathering
  cout << "\n----------------------------------------------------------------------\n" << endl;
  float parentOneSalary;
  cout << "Yearly Salary of " << parentOneName << ": $ ";
  cin >> parentOneSalary;
  float parentTwoHouseIncome, parentTwoCarIncome, parentTwoTotalIncome;
  cout << "Amount of House Insurance sold by " << parentTwoName << ": $ ";
  cin >> parentTwoHouseIncome;
  cout << "Amount of Car Insurance sold by " << parentTwoName << ": $ ";
  cin >> parentTwoCarIncome;
  float childWage, childHoursPerWeek, childWeeksPerYear, childTotalIncome;
  cout << "Hourly Rate of " << childName << ": $ ";
  cin >> childWage;
  cout << "Number of Hours Worked Per Week by " << childName << ": ";
  cin >> childHoursPerWeek;
  cout << "Number of Weeks Worked Per Year by " << childName << ": ";
  cin >> childWeeksPerYear;

  //Calculations for total income of child and parent two
  parentTwoTotalIncome = (parentTwoHouseIncome*0.125) + parentTwoCarIncome*0.098;
  childTotalIncome = childWeeksPerYear*childHoursPerWeek*childWage;

  //Calculations for taxes
  float parentOneTax = parentOneSalary*0.2;
  float parentTwoTax = parentTwoTotalIncome*0.15;
  float childTax = childTotalIncome*0.05;
  float totalTax = parentOneTax + parentTwoTax + childTax;

  //Calculate for net income
  float netIncome = parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax;

  //Investments
  cout << "\n----------------------------------------------------------------------\n" << endl;
  cout << "Please enter the following Investment Information:\n" << endl;
  cout << "The price of one share of stock is given as A b/c." << endl;
  float moneyInvested = netIncome * 0.08;
  float a, b, c;
  cout << "Please enter the price as A b c: ";
  cin >> a >> b >> c;

  float sharePrice = a + (b/c);
  int sharesBought = moneyInvested / sharePrice;

  //Expenses
  cout << "\n----------------------------------------------------------------------\n" << endl;
  cout << "Please enter the following Expenses Information:\n" << endl;

  //Electricity
  cout << "ELECTRICITY\n" << endl;
  float units;
  int monthsOfDiscount;
  cout << "> Units of Electricity Over the Year (kWh): ";
  cin >> units;
  cout << "> Number of Months of Discount: ";
  cin >> monthsOfDiscount;

  float utilityTax = (units*0.18 - 50) * 0.02;
  float totalElectricityCost = ((units*0.18) / 12 * monthsOfDiscount * 0.9) + ((units*0.18) / 12 * (12-monthsOfDiscount)) - 50 + utilityTax;

  //Phone Bill
  cout << "\n\nPHONE BILL\n" << endl;
  int minutesSpent, minutesPerBlock;
  float blockPrice;
  cout << "> Number of Minutes Spent Over the Year: ";
  cin >> minutesSpent;
  cout << "> Number of Minutes in a Block of Time: ";
  cin >> minutesPerBlock;
  cout << "> Cost for Each Block of Time: $";
  cin >> blockPrice;

  float totalPhoneBill = minutesSpent/minutesPerBlock * blockPrice;

  //Gas bill
  cout << "\n\nGAS BILL\n" << endl;
  string uselessVariable;
  cout << "> Brand and Type of Vehicle: ";
  getline(cin, uselessVariable);
  cin.ignore(256, '\n');
  float distanceTravelled, fuelEfficiency, avgGasPrice;
  cout << "> Distance travelled over the Year (km): ";
  cin >> distanceTravelled;
  cout << "> Fuel Efficiency (km/L): ";
  cin >> fuelEfficiency;
  cout << "> Average gas price ($/L): ";
  cin >> avgGasPrice;

  float totalGasBill = distanceTravelled * fuelEfficiency * avgGasPrice;

  //Mortgage
  float biWeeklyPayment;
  cout << "\n\nMORTGAGE\n" << endl;
  cout << "> Amount of Bi-Weekly Mortgage Payment: $";
  cin >> biWeeklyPayment;

  float totalMortgage = biWeeklyPayment*21;
}