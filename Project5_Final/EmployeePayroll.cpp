#include "EmployeePayroll.h"
#include "TimeCard.h"
#include "Employee.h"

#include <string>
#include <iostream>
using namespace std;

CEmployeePayroll::CEmployeePayroll()
{
	workedHours = 0.0;
	federal = 0.0;
	state = 0.0;
	social = 0.0;
	health = 0.0;
}

CEmployeePayroll::CEmployeePayroll(CEmployee emp, double work, double fed, double stat, double soci, double heal)
{
	Worker = emp;
	workedHours = work;
	federal = fed;
	state = stat;
	social = soci;
	health = heal;
}

CEmployeePayroll::CEmployeePayroll(const CEmployeePayroll& employee)
{
	workedHours = employee.workedHours;
	federal = employee.state;
	state = employee.state;
	social = employee.social;
	health = employee.health;
}

void CEmployeePayroll::setTakeHomePay(double take)
{
	takehome = take;
}

double CEmployeePayroll::getTakeHomePay()
{
	return takehome;
}

void CEmployeePayroll::inputHours(CTimeCard timeCards[], int num_used)
{
	workedHours = timeCards[num_used].getHours();
}

void CEmployeePayroll::CalculateTakeHome()
{
	double overtime, pay, total;
	double rate = 1.5;
	pay = Worker.getPayRate();
	if (workedHours > 40)
	{
		overtime = workedHours - 40;
		total = ((40 * pay) + (rate * (overtime* (pay))));
		takehome = ((total * federal) + (total * state) + (total * social) + (total * health)) - total;
	}
	else
	{
		overtime = 0;
		total = (workedHours * pay);
		takehome = ((total * federal) + (total * state) + (total * social) + (total * health)) - total;
	}
}

void CEmployeePayroll::PrintPayStub()
{
	double overtime, pay, total;
	double rate = 1.5;
	pay = Worker.getPayRate();
	cout << "Paystub " << endl << endl;
	cout << "Total HOurs: " << workedHours << endl;

	if (workedHours > 40)
	{
		overtime = workedHours - 40;
		total = ((40 * pay) + (rate * (overtime * pay)));
		takehome = ((total * federal) + (total * state) + (total * social) + (total * health)) - total;

		cout << "Overtime: " << overtime << endl << endl;
		cout << "Hourly Rate: " << Worker.getPayRate() << endl << endl;
		cout << "Total Earned: " << total << endl << endl;
		cout << "Social Security Tax: " << (social * total) << endl;
		cout << "Federal Income Tax: " << (federal * total) << endl;
		cout << "State Income Tax: " << (state * total) << endl;
		cout << " ------------------------------------- " << endl;
		cout << "Take Home Pay: " << takehome << endl;
	}

	else
	{
		overtime = 0;
		total = ((40 * pay) + (rate * (overtime * pay)));
		takehome = ((total * federal) + (total * state) + (total * social) + (total * health)) - total;

		cout << "Overtime: " << 0 << endl << endl;
		cout << "Hourly Rate: " << Worker.getPayRate() << endl << endl;
		cout << "Total Earned: " << total << endl << endl;
		cout << "Social Security Tax: " << (social * total) << endl;
		cout << "Federal Income Tax: " << (federal * total) << endl;
		cout << "State Income Tax: " << (state * total) << endl;
		cout << " ------------------------------------- " << endl;
		cout << "Take Home Pay: " << takehome << endl;
	}

}