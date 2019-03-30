//#pragma once
#ifndef SHAREHOLDER_H

#include <string>
using std::string;

class Shareholder {
	
private:
	int accountID, numberOfShares;
	string customerName, investmentCompany;
	double availableBal, amountInvested;

	//available bal setter
	void setAvailableBal(double);
public:
	Shareholder();
	Shareholder(string , int, double);

	//account id getter-setter
	int getAccountID();
	void setAccountID(int );

	//number of shares getter-setter
	int getNumberOfShares();
	void setNumberOfShares(int );

	//customer name getter-setter
	string getCustomerName();
	void setCutomername(string );

	//investment company getter-setter
	string getInvestmentCompany();
	void setInvestmentCompany(string );

	//avilable bal getter
	double getAvailableBal();

	//amount invested getter-setter
	double getAmountInvested();
	void setAmountInvested(double );

	// deposit to account
	double deposit(double );
	
	//withdraw from account
	string withdraw(double );
		


};

#define SHAREHOLDER_H
#endif // SHAREHOLDER_H
