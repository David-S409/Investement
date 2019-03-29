#ifndef SHAREHOLDER_H

#include <string>

class Shareholder {
	

	int accountID, numberOfShares;
	string customerName, investmentCompany;
	double availableBal, amountInvested;

	//available bal setter
	void setAvailableBal(double bal);

	Shareholder();

	Shareholder(string name, int accountNumber, double staringBal);

	//account id getter-setter
	int getAccountID();
	void setAccountID(int id);

	//number of shares getter-setter
	int getNumberOfShares();
	void setNumberOfShares(int shares);

	//customer name getter-setter
	string getCustomerName();
	void setCutomername(string name);

	//investment company getter-setter
	string getInvestmentCompany();
	void setInvestmentCompany(string ic);

	//avilable bal getter
	double getAvailableBal();

	//amount invested getter-setter
	double getAmountInvested();
	void setAmountInvested(double ai);

	// deposit to account
	double deposit(double amount);
	
	//withdraw from account
	string withdraw(double amount);
		


};
#define SHAREHOLDER_H
#endif // SHAREHOLDER_H