/*
  Family Budget Assignment for Unit 2
  Made by: Ethan Zhou
  Made for: Ms.Wun
  Class: ICS3U1
  Purpose: Gathers information about a family's income and expenses and outputs a budget summary
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
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

  float totalGasBill = distanceTravelled / fuelEfficiency * avgGasPrice;

  //Mortgage
  float biWeeklyPayment;
  cout << "\n\nMORTGAGE\n" << endl;
  cout << "> Amount of Bi-Weekly Mortgage Payment: $";
  cin >> biWeeklyPayment;

  float totalMortgage = biWeeklyPayment*26;

  float remainingMoney = parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax - moneyInvested - totalElectricityCost - totalPhoneBill - totalGasBill - totalMortgage;

  //Remaining money calculations
  float groceriesMoney = remainingMoney * 0.6;
  float entertainmentMoney = remainingMoney * 0.25;
  float cashSavings = remainingMoney * 0.15;


  //Outputs
  cout << "\n\n-------------------------INCOME---------------------------------------\n" << endl;

  string prompt = "Income of " + parentOneName + " :";
  int numberWidthInteger = parentOneSalary;
  string numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentOneSalary << endl;

  prompt = "Income of " + parentTwoName + " :";
  numberWidthInteger = parentTwoTotalIncome;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentTwoTotalIncome << endl;

  prompt = "Income of " + childName + " :";
  numberWidthInteger = childTotalIncome;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << childTotalIncome << endl;
  
  cout << endl;


  prompt = "Total Family Income:";
  numberWidthInteger = parentOneSalary + parentTwoTotalIncome + childTotalIncome;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentOneSalary + parentTwoTotalIncome + childTotalIncome << endl;

  prompt = "Average Family Income:";
  numberWidthInteger = (parentOneSalary + parentTwoTotalIncome + childTotalIncome) / 3;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << (parentOneSalary + parentTwoTotalIncome + childTotalIncome) / 3 << endl;

  cout << "\n-------------------------TAX------------------------------------------\n" << endl;

  prompt = "Income of " + parentOneName + " :";
  numberWidthInteger = parentOneTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentOneTax << endl;

  prompt = "Income of " + parentTwoName + " :";
  numberWidthInteger = parentTwoTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentTwoTax << endl;

  prompt = "Income of " + childName + " :";
  numberWidthInteger = childTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << childTax << endl;

  cout << endl;

  prompt = "Total Amount of Tax Paid:";
  numberWidthInteger = totalTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalTax << endl;

  prompt = "Overall Tax Rate:";
  numberWidthInteger = totalTax * 100/(parentOneSalary + parentTwoTotalIncome + childTotalIncome);
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() + 1) << right << fixed << setprecision(1)  << totalTax * 100/(parentOneSalary + parentTwoTotalIncome + childTotalIncome) << '%' <<  endl;

  prompt = "Total Net Income:";
  numberWidthInteger = parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax << endl;

  prompt = "Average Monthly Net Income:";
  numberWidthInteger = (parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax)/12;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << (parentOneSalary + parentTwoTotalIncome + childTotalIncome - totalTax)/12 << endl;

  cout << "\n-------------------------INVESTMENT-----------------------------------\n" << endl;

  prompt = "Price per Share:";
  numberWidthInteger = a + (b / c);
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << a + (b / c) << endl;

  prompt = "Amount of Investment:";
  numberWidthInteger = moneyInvested;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << moneyInvested << endl;

  prompt = "Amount of Investment:";
  numberWidthString = to_string(sharesBought);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() + 4) << right << fixed << sharesBought << endl;

  cout << "\n-------------------------EXPENSES-------------------------------------\n" << endl;

  prompt = "Total Cost of Electricity Bill for the Year:";
  numberWidthInteger = totalElectricityCost;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalElectricityCost << endl;

  prompt = "Total Cost of Phone Bill for the Year:";
  numberWidthInteger = totalPhoneBill;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalPhoneBill << endl;

  prompt = "Total Cost of Gas Bill for the Year:";
  numberWidthInteger = totalGasBill;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalGasBill << endl;

  prompt = "Total Cost of Mortgage Payments for the Year:";
  numberWidthInteger = totalMortgage;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalMortgage << endl;

  cout << endl;

  prompt = "Total Amount for Groceries:";
  numberWidthInteger = groceriesMoney;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << groceriesMoney << endl;

  prompt = "Total Amount for Entertainment:";
  numberWidthInteger = entertainmentMoney;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << entertainmentMoney << endl;

  prompt = "Total Amount of Cash Savings:";
  numberWidthInteger = cashSavings;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << cashSavings << endl;

  cout << "\n-------------------------SUMMARY--------------------------------------\n" << endl;

  prompt = "Total Household Gross Income:";
  numberWidthInteger = parentOneSalary + parentTwoTotalIncome + childTotalIncome;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << parentOneSalary + parentTwoTotalIncome + childTotalIncome << endl;

  prompt = "Total Income Tax Paid:";
  numberWidthInteger = totalTax;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << totalTax << endl;

  prompt = "Total Expenses:";
  numberWidthInteger = totalElectricityCost + totalPhoneBill + totalGasBill + totalMortgage;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 4) << right << fixed << '$' << setprecision(2)  << totalElectricityCost + totalPhoneBill + totalGasBill + totalMortgage + groceriesMoney + entertainmentMoney << endl;

  prompt = "Total Reserve Funds:";
  numberWidthInteger = moneyInvested + cashSavings;
  numberWidthString = to_string(numberWidthInteger);
  cout << prompt << setw(70-prompt.length() - numberWidthString.length() - 3) << right << fixed << '$' << setprecision(2)  << moneyInvested + cashSavings << endl;

  cout << "\nThank you for using this program!\n" << endl;
  return 0;
}