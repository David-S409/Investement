#include "Shareholder.h"

using namespace std;


Shareholder::Shareholder() {
	customerName = "unknown";
	availableBal = 0;
	amountInvested = 0;
	numberOfShares = 0;
	investmentCompany = "NULL";

}

Shareholder::Shareholder(string name, int accountNumber, double staringBal) {
	customerName = name;
	availableBal = staringBal;
	accountID = accountNumber;
	amountInvested = 0;
	numberOfShares = 0;
	investmentCompany = "NULL";
}

// available balance
void Shareholder::setAvailableBal(double bal) { availableBal = bal; }
double Shareholder::getAvailableBal() { return availableBal; }

// account id
void Shareholder::setAccountID(int id) { accountID = id; }
int Shareholder::getAccountID() { return accountID; }

// amount invested
void Shareholder::setAmountInvested(double ai) { amountInvested += ai; }
double Shareholder::getAmountInvested() { return amountInvested; }

// investment company
void Shareholder::setInvestmentCompany(string ic) { investmentCompany = ic; }
string Shareholder::getInvestmentCompany() { return investmentCompany; }

// customer name
void Shareholder::setCutomername(string name) { customerName = name; }
string Shareholder::getCustomerName() { return customerName; }

// number of shares
void Shareholder::setNumberOfShares(int shares) { numberOfShares += shares; }
int Shareholder::getNumberOfShares() { return numberOfShares; }

// deposit
double Shareholder::deposit(double amount) {
	availableBal += amount;
	return availableBal;
}

// withdraw
string Shareholder::withdraw(double amount) {
	if (availableBal > amount && availableBal > 0) {

		availableBal -= amount;
		return "Withdraw successful.\n";
	}
	return "Not enough funds!";
}
