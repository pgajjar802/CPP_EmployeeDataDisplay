//Filename: Project 5 -- Employee Data Display
//Programmer:  Pooja Gajjar                                        CSCI 123
//Project #5                                                       Instructor:  Timothy Mai

// Program Description: This program has a list of options ranging from 1 to 11.
//                      The program manages to read from several files and displays    
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Employee.h"
#include "Timecard.h"
#include "EmployeePayroll.h"
using namespace std;

int menu();
void getEmployeeInfo(CEmployee employee[]);
void getTimeCards(CTimeCard tcard[]);
// void getPayrollInfo(CEmployee employee[], CEmployeePayroll payroll[], int empCount);
void ListAllEmployees(CEmployee employees[], CTimeCard timeCards[], int& employeeCount);
void ListEmployeeInfo(int& employeeCount, CEmployee employees[], CTimeCard timeCards[]);
void ListEmployeeOvertime(CEmployee employees[], CTimeCard timeCards[], int& employeeCount);
void ListHighPayrate(CEmployee employees[], int& employeeCount);
void AddEmployee(int& employeeCount, CEmployee employee[]);
void RemoveEmployee(int& employeeCount, CEmployee employee[], CEmployeePayroll payroll[]);
void UpdatePayRate(int& employeeCount, CEmployee employee[], CTimeCard tcard[]);
void UpdateWorkedHours();
void PrintPayStub(CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[]);
void AllEmployeePayroll(int& empCount, CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[]);
void Quit(CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[], int& empCount);
int searchId(string first, string last, CEmployee employees[], CTimeCard timeCards[], int& employeeCount);
int searchOvertimeHours(CEmployee employees[], CTimeCard timeCards[], int& employeeCount);
double searchHighPayRate(CEmployee employee[], int& employeeCount);
void getMStatus(CEmployee employees[], int& employeeCount);
void getWage();
double generatePercentage();
double generateMeritRate(void);
double generateOT(void);


const int MAX_LIST_SIZE = 20;
CEmployee emp[MAX_LIST_SIZE];
CTimeCard timeCards[MAX_LIST_SIZE];
CEmployeePayroll payroll[MAX_LIST_SIZE];

// === main function ==============================================
int main()
{
	int employeeCount = 8;

	for (int i = 0; i < MAX_LIST_SIZE; i++)
	{
		if (emp[i].firstName != "NONE")
		{
			employeeCount++;
		}
	}

	getEmployeeInfo(emp);
	getTimeCards(timeCards);
	// getPayrollInfo(emp, payroll, employeeCount);

	int choice;
	do {
		system("CLS");
		choice = menu();
		switch (choice) {
		case 1:
			ListAllEmployees(emp, timeCards, employeeCount);
			break;
		case 2:
			ListEmployeeInfo(employeeCount, emp, timeCards);
			break;
		case 3:
			ListEmployeeOvertime(emp, timeCards, employeeCount);
			break;
		case 4:
			ListHighPayrate(emp, employeeCount);
			break;
		case 5:
			AddEmployee(employeeCount, emp);
			break;
		case 6:
			RemoveEmployee(employeeCount, emp, payroll);

			break;
		case 7:
			UpdatePayRate(employeeCount, emp, timeCards);
			break;
		case 8:
			UpdateWorkedHours();
			break;
		case 9:
			PrintPayStub(emp, timeCards, payroll);
			break;
		case 10:
			AllEmployeePayroll(employeeCount, emp, timeCards, payroll);
			break;
		case 11:
			Quit(emp, timeCards, payroll, employeeCount);
			break;
		default:
			std::cout << "Error 3456: That was an invalid choice, try again! \n";
		}
		system("PAUSE");
	} while (choice > 0 && choice < 11);
	return 0;
}

int menu() {
	int option;
	std::cout << "           EMPLOYEE DATABASE APPLICATION \n\n";
	std::cout << "1. List All Employees. \n";
	std::cout << "2. List Employee Information. \n";
	std::cout << "3. List Employees Working Overtime. \n";
	std::cout << "4. List Employees with High Pay Rate.\n";
	std::cout << "5. Add an Employee.\n";
	std::cout << "6. Remove an Employee. \n";
	std::cout << "7. Update Pay Rate for All Employees. \n";
	std::cout << "8. Update Hours Worked for All Employees. \n";
	std::cout << "9. Print Paystub for Specific Employee (Based on ID). \n";
	std::cout << "10. Calculate Payroll for All Employees. \n";
	std::cout << "11. Quit. \n\n";
	std::cout << "Please select your option: ";
	cin >> option;
	while (option < 1 || option > 11)
	{
		std::cout << "Error 9250: Invalid option! Please select valid option: ";
		cin >> option;
	}
	return option;
}

void getEmployeeInfo(CEmployee employeeInfo[])
{
	string id, fn, ln, pr, ms;
	ifstream ifile;
	int i = 0;
	ifile.open("Employees.txt");
	if (ifile.fail())
	{
		cout << "Failed to open input file.\n";
		exit(1);
	}
	while (!ifile.eof())
	{
		ifile >> id >> fn >> ln >> pr >> ms;

		if (ms == "M")
		{
			CEmployee n = { id, fn, ln, stof(pr), MARRIED };
			employeeInfo[i] = n;
		}
		else if (ms == "S")
		{
			CEmployee n = { id, fn, ln, stof(pr), SINGLE };
			employeeInfo[i] = n;
		}
		else
		{
			cout << "Error: invalid format for marital status for "
				<< employeeInfo[i].firstName << employeeInfo[i].lastName << endl;
		}
		i++;
	}
	ifile.close();
}

/* void getPayrollInfo(CEmployee employee[], CEmployeePayroll payroll[], int empCount)
{
	ofstream OutputFile;
	double total, fedTax, stateTax, ssTax, healthInsurance, netEarnings;
	OutputFile.open("PayRollRecords.txt");

	//CHECK FOR FAILURE
	if (OutputFile.fail())	{
		cout << "Output file opening failed.\n";
		exit(1);
	}
	OutputFile << setfill(' ') << setw(12) << left << "ID";
	OutputFile << setfill(' ') << setw(12) << left << "First";
	OutputFile << setfill(' ') << setw(12) << left << "Last";
	OutputFile << setfill(' ') << setw(12) << left << "Rate";
	OutputFile << setfill(' ') << setw(12) << left << "Hours";
	OutputFile << setfill(' ') << setw(12) << left << "MStatus";
	OutputFile << setfill(' ') << setw(12) << left << "Gross Earnings";
	OutputFile << setfill(' ') << setw(12) << left << "FTax";
	OutputFile << setfill(' ') << setw(12) << left << "STax";
	OutputFile << setfill(' ') << setw(12) << left << "SSTax";
	OutputFile << setfill(' ') << setw(12) << left << "Insurance";
	OutputFile << setfill(' ') << setw(12) << left << "NetEarnings";
	OutputFile << endl;
	for (int i = 0; i < MAX_LIST_SIZE + 1; i++)
	{
		// calculate gross payment
		total = ((employee[i].getPayRate() * 40) + ((timeCards[i].getHours() - 40) * employee[i].getPayRate() * 1.5));

		// calculate taxes
		if (total > 1000) {
			fedTax = total * 0.10;
			stateTax = total * 0.04;
			ssTax = total * 0.06;
		}
		else
		{
			fedTax = total * 0.07;
			stateTax = total * 0.03;
			ssTax = total * 0.06;
		}

		// calculate health insurance
		if ((employee[i].getMstatus() == "MARRIED"))		{
			healthInsurance = 50;
		}

		else if (employee[i].getMstatus() == "SINGLE")	{
			healthInsurance = 0;
		}

		// calculate net earnings
		netEarnings = (total - (fedTax + stateTax + ssTax + healthInsurance));
		OutputFile << setfill(' ') << setw(12) << left << employee[i].ID;
		OutputFile << setfill(' ') << setw(12) << left << employee[i].firstName;
		OutputFile << setfill(' ') << setw(12) << left << employee[i].lastName;
		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << employee[i].getPayRate();
		OutputFile << setfill(' ') << setw(12) << left << fixed << setprecision(0) << timeCards[i].getHours();
		if ((employee[i].getMstatus() == "MARRIED"))		{
			OutputFile << setfill(' ') << setw(12) << left << "MARRIED";
		}
		else if (employee[i].getMstatus() == "SINGLE")	{
			OutputFile << setfill(' ') << setw(12) << left << "SINGLE";
		}

		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << total;
		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << fedTax;
		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << stateTax;
		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << ssTax;
		OutputFile << "$" << setfill(' ') << setw(12) << left << fixed << setprecision(2) << healthInsurance;
		OutputFile << endl;
	}
	OutputFile.close();
} */

void getTimeCards(CTimeCard timeCards[])
{
	string id, hours;
	int i = 0;
	ifstream ifile;

	ifile.open("WeeklyPayroll.txt");

	if (ifile.fail())
	{
		cout << "Failed to open input file.\n";
		exit(1);
	}

	while (ifile >> id >> hours)
	{
		CTimeCard n = { id, stof(hours) };
		timeCards[i] = n;
		i++;
	}

	ifile.close();
}

void ListAllEmployees(CEmployee employees[], CTimeCard timeCards[], int& employeeCount)
{
	std::cout << endl;
	std::cout << "Listing Data For All Employees: \n \n";

	std::cout << setfill(' ') << setw(12) << left << "ID";
	std::cout << setfill(' ') << setw(12) << left << "First Name";
	std::cout << setfill(' ') << setw(12) << left << "Last Name";
	std::cout << setfill(' ') << setw(12) << left << "Pay Rate";
	std::cout << setfill(' ') << setw(12) << left << "Marriage Status";
	std::cout << setfill(' ') << setw(15) << left << " Hours Worked";
	std::cout << endl;

	for (int i = 0; i < 8; i++)
	{
		std::cout << setfill(' ') << setw(12) << left << employees[i].ID;
		std::cout << setfill(' ') << setw(12) << left << employees[i].firstName;
		std::cout << setfill(' ') << setw(12) << left << employees[i].lastName;
		std::cout << setfill(' ') << setw(12) << left << employees[i].getPayRate();
		if (employees[i].getMstatus() == "MARRIED")
		{
			std::cout << setfill(' ') << setw(12) << left << "M";
		}
		if (employees[i].getMstatus() == "SINGLE")
		{
			std::cout << setfill(' ') << setw(12) << left << "S";
		}
		std::cout << setfill(' ') << setw(6) << right << timeCards[i].getHours();
		std::cout << endl;
	}
	cout << endl;
}

int searchId(string first, string last, CEmployee employees[], CTimeCard timeCards[], int& employeeCount)
{
	cout << "Enter First Name: ";
	cin >> first;
	cout << "Enter Last Name: ";
	cin >> last;
	cout << endl;
	cout << "The employee you searched for: \n\n";

	cout << setfill(' ') << setw(12) << left << "ID";
	cout << setfill(' ') << setw(12) << left << "First Name";
	cout << setfill(' ') << setw(12) << left << "Last Name";
	cout << setfill(' ') << setw(12) << left << "Pay Rate";
	cout << setfill(' ') << setw(12) << left << "Marriage Status";
	cout << setfill(' ') << setw(15) << left << " Hours Worked";
	cout << endl;

	for (int i = 0; i < employeeCount; i++)
	{
		if ((first == employees[i].firstName) && (last == employees[i].lastName))
		{
			cout << setfill(' ') << setw(12) << left << employees[i].ID;
			cout << setfill(' ') << setw(12) << left << employees[i].firstName;
			cout << setfill(' ') << setw(12) << left << employees[i].lastName;
			cout << setfill(' ') << setw(12) << left << employees[i].getPayRate();
			if (employees[i].getMstatus() == "MARRIED")
			{
				std::cout << setfill(' ') << setw(12) << left << "M";
			}
			if (employees[i].getMstatus() == "SINGLE")
			{
				std::cout << setfill(' ') << setw(12) << left << "S";
			}
			cout << setfill(' ') << setw(6) << right << timeCards[i].getHours();
			cout << endl;
		}
	}
	return 0;
}

void ListEmployeeInfo(int& employeeCount, CEmployee employees[], CTimeCard timeCards[])
{
	string first, last;
	cout << "List Employee Information: \n";
	cout << "Enter the <first name> and <last name> for the employee you would like to search below. \n";
	searchId(first, last, employees, timeCards, employeeCount);
	cout << endl;
}

int searchOvertimeHours(CEmployee employees[], CTimeCard timeCards[], int& employeeCount)
{
	int overtime;
	cout << "Enter target overtime hours: ";
	cin >> overtime;

	cout << setfill(' ') << setw(12) << left << "ID";
	cout << setfill(' ') << setw(12) << left << "First";
	cout << setfill(' ') << setw(12) << left << "Last";
	cout << setfill(' ') << setw(12) << left << "Hours Worked";
	cout << endl;

	for (int i = 0; i < employeeCount; i++)
	{
		if ((timeCards[i].getHours() >= overtime))
		{
			cout << setfill(' ') << setw(12) << left << employees[i].ID;
			cout << setfill(' ') << setw(12) << left << employees[i].firstName;
			cout << setfill(' ') << setw(12) << left << employees[i].lastName;
			if ((employees[i].ID == timeCards[i].ID))
			{
				cout << setfill(' ') << setw(12) << left << timeCards[i].getHours();
			}
			else {
				cout << "N/A";
			}
			cout << endl;
		}
	}
	return 0;
}

void ListEmployeeOvertime(CEmployee employees[], CTimeCard timeCards[], int& employeeCount)
{
	cout << endl;
	cout << "List Employee Overtime: \n";
	searchOvertimeHours(employees, timeCards, employeeCount);
	cout << endl;
}

double searchHighPayRate(CEmployee employee[], int& employeeCount) 
{
	double target_payRate;
	cout << "Enter target pay rate: $";
	cin >> target_payRate;

	cout << setfill(' ') << setw(12) << left << "ID";
	cout << setfill(' ') << setw(12) << left << "First";
	cout << setfill(' ') << setw(12) << left << "Last";
	cout << setfill(' ') << setw(12) << left << "Pay Rate";
	cout << endl;

	for (int i = 0; i < employeeCount; i++)
	{
		if ((employee[i].getPayRate() >= target_payRate))
		{
			cout << setfill(' ') << setw(12) << left << employee[i].ID;
			cout << setfill(' ') << setw(12) << left << employee[i].firstName;
			cout << setfill(' ') << setw(12) << left << employee[i].lastName;
			cout << setfill(' ') << setw(12) << left << employee[i].getPayRate();
			cout << endl;
		}
	}
	return 0;
}

void ListHighPayrate(CEmployee employees[], int& employeeCount)
{
	cout << endl;
	cout << "Listing of Employees with High Pay Rate: ";
	searchHighPayRate(employees, employeeCount);
	cout << endl;
}

void getMStatus(CEmployee employees[], int& employeeCount)
{
	char mStatus;
	cout << "Enter Marriage Status: (m/s)";
	cin >> mStatus;
	if (mStatus == 'S' || mStatus == 's')
	{
		employees[employeeCount].getMstatus() == "SINGLE";
	}
	if (mStatus == 'M' || mStatus == 'm')
	{
		employees[employeeCount].getMstatus() == "MARRIED";
	}
}

void AddEmployee(int& employeeCount, CEmployee employee[])
{

	//double rate;
	//totEmployee = totEmployee + employeeCount;
	//  int i = totEmployee - 1;
	int i = 0;
	cout << endl;
	// double rate = GetWage();
	cout << "Adding an Employee: \n";
	cout << "Enter the information before the employee you would like to add: \n";

	cout << "Employee ID: ";
	cin >> employee[employeeCount +1].ID;
	cout << "First Name: ";
	cin >> employee[employeeCount+ 1].firstName;
	cout << "Last Name: ";
	cin >> employee[employeeCount + 1].lastName;
	cout << employee[i].getPayRate();
	cout << employee[i].getMstatus();

	employeeCount++; // increment size of the list
	cout << endl << endl;
	cout << "This employee has been successfully added.";
}

void RemoveEmployee(int& employeeCount, CEmployee employee[], CEmployeePayroll payroll[])
{
	string first, last;
	int x = 0;
	cout << "Please enter name of employee to be removed: ";
	cin >> first >> last;

	cout << "The employee you searched for: \n\n";

	cout << setfill(' ') << setw(12) << left << "ID";
	cout << setfill(' ') << setw(12) << left << "First Name";
	cout << setfill(' ') << setw(12) << left << "Last Name";
	cout << setfill(' ') << setw(12) << left << "Pay Rate";
	cout << setfill(' ') << setw(12) << left << "Marriage Status";
	cout << endl;
	for (int i = 0; i < employeeCount; i++)
	{
		if ((employee[i].firstName == first) && (employee[i].lastName == last))
		{
			cout << setfill(' ') << setw(12) << left << employee[i].ID;
			cout << setfill(' ') << setw(12) << left << employee[i].firstName;
			cout << setfill(' ') << setw(12) << left << employee[i].lastName;
			cout << setfill(' ') << setw(12) << left << employee[i].getPayRate();
			if (employee[i].getMstatus() == "MARRIED")
			{
				cout << setfill(' ') << setw(12) << left << "MARRIED";
			}
			if (employee[i].getMstatus() == "SINGLE")
			{
				cout << setfill(' ') << setw(12) << left << "SINGLE";
			}

			for (int b = i; b < employeeCount; b++)
			{
				int a = b;
				employee[b] = employee[++a];
				timeCards[b] = timeCards[a];
				payroll[b] = payroll[a];
			}

			cout << "Employee's information has now been removed.\n";
			employeeCount--;
			x = 1;
		}
	}
	if (!x)
		cout << "Employee not found.\n\n";
}

void UpdatePayRate(int& employeeCount, CEmployee employee[], CTimeCard tcard[])
{
	cout << "The information of the employee is: \n";
	ListAllEmployees(employee, tcard, employeeCount);
	for (int i = 0; i < employeeCount; i++)
	{
		employee[i].setPayRate((employee[i].getPayRate() + employee[i].getPayRate()*generateMeritRate()));
	}
	cout << "The information has been updated.\n";
	ListAllEmployees(employee, tcard, employeeCount);
	// ListAllEmployees(CEmployee employees[], CTimeCard timeCards[], int& employeeCount);
}

void UpdateWorkedHours()
{

}

void PrintPayStub(CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[])
{
	string idNum;
	double total, federal, state, social, health, netEarnings;
	cout << endl;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "Print Pay Stub: \n";
	cout << "Enter the <ID> of employee to print Pay Stub: ";
	cin >> idNum;

	cout << " ================================================== \n";
	cout << " PAY STUB OF EMPLOYEE \n";
	cout << " ================================================== \n";

	for (int i = 0; i < MAX_LIST_SIZE; i++)
	{
		if ((employee[i].ID == idNum))
		{
			// 1. calculate the total
			total = ((employee[i].getPayRate() * 40) + ((timeCards[i].getHours() - 40) * employee[i].getPayRate() * 1.5));
			// 2. calculate the taxes
			if (total > 1000) {
				federal = total *0.10;
				state = total * 0.04;
				social = total * 0.07;
			}
			else {
				federal = total * 0.07;
				state = total * 0.03;
				social = total * 0.07;
			}
			// 3. calculate health insurance
			if (employee[i].getMstatus() == "MARRIED") {
				health = 50.00;
			}
			else {
				health = 0;
			}
			// 4. calculate net earnings
			netEarnings = (total - (federal + state + social + health));
			cout << endl;
			cout << "Employee ID: \t\t" << employee[i].ID << endl;
			cout << "First Name: \t\t" << employee[i].firstName << endl;
			cout << "Last Name: \t\t" << employee[i].lastName << endl;
			cout << "Pay Rate:  \t\t" <<  "$" << employee[i].getPayRate() << endl;
			cout << "Hours Worked: \t\t" << timeCards[i].getHours() << endl;
			cout << "Marriage Status: \t";
			if (employee[i].getMstatus() == "MARRIED")
			{
				cout << setfill(' ') << setw(12) << left << "MARRIED" << endl;
			}
			if (employee[i].getMstatus() == "SINGLE")
			{
				cout << setfill(' ') << setw(12) << left << "SINGLE" << endl;
			}
			cout << " \n ================================================== \n\n";
			cout << "Federal Taxes: \t\t" << "$" << federal << endl;
			cout << "State Taxes: \t\t" << "$" << state << endl;
			cout << "Social Security Taxes: \t" << "$" << social << endl;
			cout << "Health Insurance: \t" << "$" << health << endl;
			cout << "Take Home Pay: \t\t" << "$" << netEarnings << endl;
		}
	}
}

void AllEmployeePayroll(int& empCount, CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[])
{
	string idNum;
	double total;
	double federal;
	double state;
	double social;
	double health;
	double netEarnings;

	cout << endl;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << endl;
	cout << "Listing the Payroll Data for All Employees: \n";
	cout << " ================================================== \n";
	cout << setfill(' ') << setw(10) << left << "ID";
	cout << setfill(' ') << setw(10) << left << "First";
	cout << setfill(' ') << setw(10) << left << "Last";
	cout << setfill(' ') << setw(10) << left << "Rate";
	cout << setfill(' ') << setw(10) << left << "Marital ";
	cout << setfill(' ') << setw(12) << left << " Hours ";
	// DO NOT FORGET TO INCLUDE OVERTIME  HOURS !!!!
	cout << setfill(' ') << setw(10) << left << "Federal";
	cout << setfill(' ') << setw(10) << left << "State";
	cout << setfill(' ') << setw(10) << left << "Social Security";
	cout << setfill(' ') << setw(10) << left << "Insurance";
	cout << setfill(' ') << setw(10) << left << "Take Home Pay";
	cout << endl << endl;
	for (int i = 0; i < empCount; i++)
	{
		// 1. calculate the total
		total = ((employee[i].getPayRate() * 40) + ((timeCards[i].getHours() - 40) * employee[i].getPayRate() * 1.5));
		// 2. calculate the taxes
		if (total > 1000)  {
			federal = total * 0.10;
			state = total * 0.04;
			social = total * 0.06;
		}
		else  {
			federal = total * 0.07;
			state = total * 0.03;
			social = total * 0.06;
		}
		// 3. calculate health insurance
		if (employee[i].getMstatus() == "MARRIED")   {
			health = 50.00;
		}
		else     {
			health = 0;
		}
		// 4. calculate net earnings
		netEarnings = (total - (federal + state + social + health));
		cout << setfill(' ') << setw(10) << left << employee[i].ID;
		cout << setfill(' ') << setw(10) << left << employee[i].firstName;
		cout << setfill(' ') << setw(10) << left << employee[i].lastName;
		cout << setfill(' ') << setw(10) << left << employee[i].getPayRate();
		if (employee[i].getMstatus() == "MARRIED")
		{
			cout << setfill(' ') << setw(10) << left << "MARRIED";
		}
		if (employee[i].getMstatus() == "SINGLE")
		{
			cout << setfill(' ') << setw(10) << left << "SINGLE";
		}
		cout << setfill(' ') << setw(10) << right << timeCards[i].getHours();
		cout << setfill(' ') << setw(10) << right << federal;
		cout << setfill(' ') << setw(10) << right << state;
		cout << setfill(' ') << setw(10) << right << social;
		cout << setfill(' ') << setw(10) << right << health;
		cout << setfill(' ') << setw(10) << right << total;
		cout << endl;
	}
	cout << endl;
}

void Quit(CEmployee employee[], CTimeCard timeCards[], CEmployeePayroll payroll[], int& empCount)
{
	cout << "All data has been updated.\n";
	// write information of all 3 arrays into their associated files

	ofstream outStream;

	// === payrollrecords.txt =================================
	outStream.open("PayRollRecords.txt");
	if (outStream.fail())
	{
		cout << "Output file opening failed. \n";
		exit(1);
	}
	else
	{
		for (int i = 0; i < empCount; i++)
		{
			if (employee[i].firstName != "None")
			{
				payroll[i].inputHours(timeCards, i);
				payroll[i].Worker = employee[i];
				payroll[i].CalculateTakeHome();
				payroll[i].PrintPayStub();
			}
		}
	}
	outStream.close();

	// === employees.txt =====================================
	outStream.open("Employees.txt");
	if (outStream.fail())
	{
		cout << "Output file opening failed. \n";
		exit(1);
	}
	else
	{
		for (int i = 0; i < empCount; i++)
		{
			outStream << employee[i].ID << employee[i].firstName << employee[i].lastName << employee[i].getMstatus();
		}
	}
	outStream.close();

	// === weeklypayroll.txt =================================
	outStream.open("WeeklyPayroll.txt");
	if (outStream.fail())
	{
		cout << "Output file opening failed. \n";
		exit(1);
	}
	else
	{
		for (int i = 0; i < empCount; i++)
		{
			cout << setw(4) << employee[i].ID << setw(10) << timeCards[i].getHours() << endl;
		}
	}
	outStream.close();

	cout << "Have a nice day.\n";
}

double generateMeritRate(void)
{
	/* pick a random number from 0 to 500 and
	get the percentage between 0.0 – 5.0 */
	return (((rand() % 501)) / 100.00);
}

double generateOT(void)
{
	/* pick and return a random number from 1 to 60 */
	int ot = (rand() % 60);
	/* return the OT if the number > 40 */
	if (ot > 40)
	{
		return ot - 40;
	}
	return 0;
}

double generatePercentage()
{
	return (generateMeritRate() / 100.00);
}

