#ifndef CTimeCard_h
#define CTimeCard_h

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class CTimeCard
{
public:
	string ID;
	CTimeCard();
	CTimeCard(string idName, double inputHrs);
	CTimeCard(const CTimeCard& CT);
	~CTimeCard();

	double getHours(); // accessor
	void    setHours(double h); //mutator

	// friend function gives access to the private data members.
	friend istream& operator >> (istream& is, CTimeCard& CCard);
	friend ostream& operator << (ostream& os, const CTimeCard& CCard);

private:
	double hours;
	double GetHoursWorked(double hoursWorked);
};

#endif