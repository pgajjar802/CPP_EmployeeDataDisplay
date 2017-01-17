#include "TimeCard.h"
#include <string>
#include <iostream>
#include <fstream>

CTimeCard::CTimeCard()
{
	ID = "0000";
	hours = 0.0;
}

CTimeCard::CTimeCard(string idName, double inputHrs)
{
	ID = idName;
	hours = inputHrs;
}

CTimeCard::CTimeCard(const CTimeCard& CT){
	ID = CT.ID;
	hours = CT.hours;
}

CTimeCard::~CTimeCard()
{
	// destructor
}

double CTimeCard::getHours()
{
	return hours;
}

void    CTimeCard::setHours(double h)
{
	hours = h;
}

istream& operator >>(istream& is, CTimeCard& CCard)
{
	is >> CCard.ID;
	is >> CCard.hours;
	return is;
}

ostream& operator <<(ostream& os, const CTimeCard& CCard)
{
	os << "ID Name: " << CCard.ID << endl;
	os << "Hours: " << CCard.hours << endl;

	return os;
}

double CTimeCard::GetHoursWorked(double hoursWorked)
{
	hoursWorked = hours;
	return hoursWorked;
}