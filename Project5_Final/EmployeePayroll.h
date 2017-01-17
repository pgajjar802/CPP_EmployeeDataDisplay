#ifndef CEmployeePayroll_h
#define CEmployeePayroll_h

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Employee.h"
#include "TimeCard.h"
using namespace std;

class CEmployeePayroll
{
public:
	double workedHours, federal, state, social, health;

	CEmployee Worker;
	CEmployeePayroll();
	CEmployeePayroll(CEmployee emp, double work, double fed, double stat, double soci, double heal);
	CEmployeePayroll(const CEmployeePayroll& emp);

	double getTakeHomePay();
	void setTakeHomePay(double take);
	
	void inputHours(CTimeCard timeCards[], int num_used);

	void CalculateTakeHome();
	void PrintPayStub();

private:
	double takehome;
};

#endif