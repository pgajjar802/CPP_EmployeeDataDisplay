#ifndef CEmployee_h
#define CEmployee_h

#include <iostream>
#include <string>
using namespace std;

enum MaritalStatus { MARRIED, SINGLE };


class CEmployee
{
public:
	string ID, firstName, lastName;

	CEmployee();
	CEmployee(string IDname, string first, string last, double pay, MaritalStatus marStat);
	CEmployee(const CEmployee& emp);
	~CEmployee();

	// friend function gives access to the private data members.
	friend istream& operator >>(istream& ins, CEmployee& employee);
	friend ostream& operator <<(ostream& outs, const CEmployee& employee);

	double getPayRate() const; // accessor
	void    setPayRate(double P); // mutator

	string getMstatus() const; // accessor
	void setMstatus(char ms); // mutator

	

private:

	double payRate;
	MaritalStatus mStatus;
};
#endif