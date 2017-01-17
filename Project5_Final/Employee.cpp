#include "Employee.h"
#include <string>
#include <iostream>
using namespace std;

CEmployee::CEmployee()
{
	ID = "0000";
	firstName = "NONE";
	lastName = "NONE";
	payRate = 0.0;
	mStatus = SINGLE;
}

CEmployee::CEmployee(string IDname, string first, string last, double pay, MaritalStatus marStat)
{
	ID = IDname;
	firstName = first;
	lastName = last;
	payRate = pay;
	mStatus = marStat;
}

CEmployee::CEmployee(const CEmployee& emp)
{
	ID = emp.ID;
	firstName = emp.firstName;
	lastName = emp.lastName;
	payRate = emp.payRate;
	mStatus = emp.mStatus;
}

CEmployee::~CEmployee()
{
	// destructor
}

istream& operator >>(istream& ins, CEmployee& employee)
{
	cout << "Enter ID: ";
	ins >> employee.ID;
	cout << "Enter First Name: ";
	ins >> employee.firstName;
	cout << "Enter Last Name: ";
	ins >> employee.lastName;
	cout << "Enter Pay Rate: ";
	ins >> employee.payRate;

	char response;
	cout << "Enter Marriage Status (S/M): ";
	ins >> response;

	// call the setMstatus() to display S/M
	employee.setMstatus(response);

	return ins;
}

ostream& operator <<(ostream& outs, const CEmployee& employee)
{
	// create new variables in order to access private data members
	string Status = employee.getMstatus();
	double rate = employee.getPayRate();

	outs << "ID: " << employee.ID << endl;
	outs << "First Name: " << employee.firstName << endl;
	outs << "First Name: " << employee.lastName << endl;

	// now private data members now accessible
	outs << "Pay Rate: $ " << rate << endl;
	outs << "Marital Status: " << Status << endl;

	return outs;
}

double CEmployee::getPayRate() const
{
	return payRate;
}

void CEmployee::setPayRate(double P)
{
	payRate = P;
}

string CEmployee::getMstatus() const
{
	if (mStatus == 1)
	{
		return "MARRIED";
	}
	else if (mStatus == 0)
	{
		return "SINGLE";
	}
	else
	{
		return "Not a valid Marriage Status";
	}
}

void    CEmployee::setMstatus(char ms)
{
	// create do-while loop to get correct user-input
	do
	{
		if ((ms == 'M') || (ms == 'm'))
		{
			mStatus = MARRIED;
		}
		else if ((ms == 'S') || (ms == 's'))
		{
			mStatus = SINGLE;

		}
		else
		{
			cout << "Invalid. Enter valid marriage status: ";
			cin >> ms;
		}

	} while (!((ms == 'M') || (ms == 'm')) && (!((ms == 'S') || (ms == 's'))));
}