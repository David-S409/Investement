#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Shareholder.h"
#include "Share.h"

using namespace std;

const int NUM_OF_COMPANIES = 10;


void storeCompanyInfo(Share shares[]), showMenu(int choice, vector<Shareholder> customers, Share[]), showShares(Share shares[]);
void buyShares(vector<Shareholder>& customers, Shareholder customer, Share coBuying, int numOfSharesBuying, int index);
string removeEnter(string str1);
Shareholder getData(), findPerson(vector<Shareholder>& customers, string, int& index);
Share findCompany(string name, Share shares[]);
void showCustomer(Shareholder), restart(vector<Shareholder>& customers, Share shares[]), showOptions();

int main() {
	Share shares[NUM_OF_COMPANIES];

	Share *shares2 = new Share[NUM_OF_COMPANIES];


	vector<Shareholder> customers;
	int userChoice;

	

	// Store shares into shares array
	storeCompanyInfo(shares2);

	// Init's NULL USER
	const Shareholder NULL_USER = Shareholder("NULL_USER", 0, 10000);
	customers.push_back(NULL_USER);

	// Init Test User
	customers.push_back(Shareholder("David Santana", 1, 10000));

	// Displays start menu
	cout << "Investment Virtual Assistant! ALL USER INFORMATION MUST BE EXACT!\n";
	showOptions();
	cin >> userChoice;
	showMenu(userChoice, customers, shares);

	system("pause>nul");
}

void storeCompanyInfo(Share shares2[]) {
	ifstream inputFile;
	inputFile.open("stockDataCPSC121.txt");

	if (!inputFile) {
		cout << "File not found!";
		exit(0);
	}

	for (int i = 0; i < NUM_OF_COMPANIES; i++) {
		string price, name;
		getline(inputFile, name, ',');

		getline(inputFile, price, ',');
		Share co = Share(removeEnter(name), stod(price));
		

		shares2[i] = co;
	}

}


Shareholder getData() {
	string name;
	int accountNum;

	cout << "Please enter the name of the customer: ";
	cin.ignore();
	getline(cin, name);

	cout << endl << "Enter account number: ";
	cin >> accountNum;

	cout << endl << "Default starting balance: $10,000\n";

	return Shareholder(name, accountNum, 10000);
}

string removeEnter(string name) {
	string str(name);
	if (str.find('\n') != string::npos) {
		str.erase(str.begin());
	}

	return str;
}

void showMenu(int choice, vector<Shareholder> customers, Share shares[]) {
	string name, companyBuyingFrom, userName;
	int numOfSharesBuying, index, dollarAmount;
	Share coBuying;
	Shareholder selectedCustomer;

	switch (choice) {
	case 1:
		cout << "\n\nAdding user!" << endl;
		customers.push_back(getData());
		restart(customers, shares);
		break;
	case 2:
		cout << "\n\nDisplaying all shares.";
		showShares(shares);
		restart(customers, shares);
		break;
	case 3:
		cout << "Please specify name of customer buying shares: ";
		cin.ignore();
		getline(cin, name);

		cout << "What company shares is customer buying? : ";
		getline(cin, companyBuyingFrom);

		for (int i = 0; i < NUM_OF_COMPANIES; i++) {
			coBuying = shares[i];

			int found = coBuying.getCompanyName().find(companyBuyingFrom);
			if (found != string::npos) {
				break;
			}
		}


		cout << coBuying.getCompanyName() << " : " << coBuying.getPricePerShare() << ". How many shares is the customer purchasing?: ";
		cin >> numOfSharesBuying;

		selectedCustomer = findPerson(customers, name, index);

		buyShares(customers, selectedCustomer, findCompany(companyBuyingFrom, shares), numOfSharesBuying, index);
		restart(customers, shares);
		break;
	case 4:
		cout << "Specify the user to look up: ";
		cin.ignore();
		getline(cin, userName);

		showCustomer(findPerson(customers, userName, index));

		restart(customers, shares);
		break;
	case 5:
		cout << "Enter customer name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter amount being deposited: ";
		cin >> dollarAmount;

		selectedCustomer = findPerson(customers, name, index);
		selectedCustomer.deposit(dollarAmount);
		cout << "Curent balance now is of: " << selectedCustomer.getAvailableBal() << endl;
		restart(customers, shares);
		break;
	case 6:
		cout << "Enter customer name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter amount being withdrawn: ";
		cin >> dollarAmount;

		selectedCustomer = findPerson(customers, name, index);
		cout << selectedCustomer.withdraw(dollarAmount);
		cout << "Curent balance now is of: " << selectedCustomer.getAvailableBal() << endl;
		restart(customers, shares);
		break;
	default:
		break;
	}
}

void showShares(Share shares[]) {
	for (int i = 0; i < NUM_OF_COMPANIES; i++) {
		cout << "\n\n\n " << i + 1 << ". Company: " << shares[i].getCompanyName();
		cout << "\n\n     Price Per Share: $" << shares[i].getPricePerShare();
	}
}


Shareholder findPerson(vector<Shareholder>& customers, string nameOfPerson, int& index) {
	Shareholder c;
	if (customers.size() < 1) {
		cout << "No useers are stored. Please create a new customer first!\n";
		return customers[0];
	}
	for (int i = 0; i < customers.size(); i++) {
		c = customers[i];
		if (c.getCustomerName() == nameOfPerson) {
			index = i;
			return customers[i];
		}
	}

	return customers[0];
}


void buyShares(vector<Shareholder>& customers, Shareholder customer, Share coBuying, int numOfSharesBuying, int index) {

	double transationTotal;

	if (customer.getCustomerName() == "NULL_USER") {
		cout << "User does not exist in database. Make sure it spelled correctly!\n";
		return;
	}

	transationTotal = (coBuying.getPricePerShare() * numOfSharesBuying);

	if (customer.getAvailableBal() < transationTotal) {
		cout << "You do not have enough funds to purchase disired stock.\n";
		exit(0);
	}
	else {

		customers[index].setInvestmentCompany(coBuying.getCompanyName());
		customers[index].setAmountInvested(transationTotal);
		cout << customers[index].withdraw(transationTotal);
		customers[index].setNumberOfShares(numOfSharesBuying);

		cout << "\nBought " << numOfSharesBuying << " shares from " << coBuying.getCompanyName() << " for $" << coBuying.getPricePerShare() << " each.\n";
	}

}

Share findCompany(string name, Share shares[]) {
	int found;
	string companyName;

	for (int i = 0; i < NUM_OF_COMPANIES; i++) {

		companyName = shares[i].getCompanyName();
		found = companyName.find(name);

		if (found != string::npos) {
			return shares[i];
		}

	}

	cout << "Company not found. ERROR!\n";
	exit(0);
}

void showCustomer(Shareholder customer) {
	cout << "\nName: " << customer.getCustomerName();
	cout << "\n  ID: " << customer.getAccountID();
	cout << "\n  Company Invested In: " << customer.getInvestmentCompany();
	cout << "\n    Number of Shares: " << customer.getNumberOfShares();
	cout << "\n  Available Balance: " << customer.getAvailableBal();
	cout << "\n  Amount Invested: " << customer.getAmountInvested() << endl;
}
void showOptions() {
	cout << "\n 1. Add new customer. \n 2. View shares.\n 3. Buy Stock\n 4. Display a customer's information. (Must have at least one customer made!) \n 5. Deposit Funds To Account.\n 6. Withdraw Funds From Account.\n Your Choice: ";
}

void restart(vector<Shareholder>& customers, Share shares[]) {
	int userChoice;
	showOptions();
	cin.ignore();
	cin >> userChoice;

	showMenu(userChoice, customers, shares);
}
