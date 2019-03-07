#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const int NUM_OF_COMPANIES = 10;

struct Shareholder {
	int accountID, numberOfShares = 0;
	string customerName, investmentCompany = "";
	double availableBal, amountInvested = 0;
};

struct Company {
	string name;
	double pricePerShare;
};


void storeCompanyInfo(Company shares[]), showMenu(int choice, vector<Shareholder> customers, Company[]), showShares(Company shares[]);
void buyShares(vector<Shareholder>& customers, Shareholder customer, Company coBuying, int numOfSharesBuying, int index);
string removeEnter(string str1);
Shareholder createCustomer(string name, int accountNumber, double staringBal = 10000);
Shareholder getData(), findPerson(vector<Shareholder>& customers, string, int& index), createTestUser();
Company findCompany(string name, Company shares[]);
void showCustomer(Shareholder), restart(vector<Shareholder>& customers, Company shares[]);

int main() {
	Company shares[NUM_OF_COMPANIES];
	vector<Shareholder> customers;
	int userChoice;

	// Store shares into shares array
	storeCompanyInfo(shares);

	// Init's NULL USER
	Shareholder NULL_USER;
	NULL_USER.customerName = "NULL_USER";
	customers.push_back(NULL_USER);

	// Init Test User
	customers.push_back(createTestUser());


	// Displays start menu
	cout << "Investment Virtual Assistant! ALL USER INFORMATION MUST BE EXACT!\n";
	cout << " 1. Add new customer. \n 2. View shares.\n 3. Buy Stock\n 4. Display a customer's information. (Must have at least one customer made!) \n Your Choice: ";
	cin >> userChoice;
	showMenu(userChoice, customers, shares);




	system("pause>nul");
}

void storeCompanyInfo(Company shares[]) {
	ifstream inputFile;
	inputFile.open("stockDataCPSC121.txt");

	if (!inputFile) {
		cout << "File not found!";
		exit(0);
	}

	for (int i = 0; i < NUM_OF_COMPANIES; i++) {
		Company co;
		string price, name;
		getline(inputFile, name, ',');

		getline(inputFile, price, ',');
		co.pricePerShare = stod(price);
		co.name = removeEnter(name);

		shares[i] = co;
	}



}

Shareholder createCustomer(string name, int accountNumber, double staringBal) {
	Shareholder person;

	person.customerName = name;
	person.accountID = accountNumber;
	person.availableBal = staringBal;

	return person;
}
Shareholder getData() {
	string name;
	int accountNum;

	cout << "Please enter the name of the customer: ";
	cin.ignore();
	getline(cin, name);

	cout << endl << "Enter account number: ";
	cin >> accountNum;

	cout << endl << "Default starting balance: $10,000";

	return createCustomer(name, accountNum, 10000);
}

string removeEnter(string name) {
	string str(name);
	if (str.find('\n') != string::npos) {
		str.erase(str.begin());
	}

	return str;
}
Shareholder createTestUser() {
	Shareholder test = createCustomer("David Santana", 1);
	return test;
}
void showMenu(int choice, vector<Shareholder> customers, Company shares[]) {
	string name, companyBuyingFrom, userName;
	int numOfSharesBuying, index;
	Company coBuying;
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

			if (companyBuyingFrom == coBuying.name) {
				cout << coBuying.name;
				break;
			}
		}

		cout << "How many shares is the customer purchasing? : ";
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
	default:
		break;
	}
}

void showShares(Company shares[]) {
	for (int i = 0; i < NUM_OF_COMPANIES; i++) {
		cout << "\n\n\n " << i + 1 << ". Company: " << shares[i].name;
		cout << "\n\n     Price Per Share: $" << shares[i].pricePerShare;
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
		if (c.customerName == nameOfPerson) {
			index = i;
			return customers[i];
		}
	}

	return customers[0];
}


void buyShares(vector<Shareholder>& customers, Shareholder customer, Company coBuying, int numOfSharesBuying, int index) {
	
	double transationTotal;

	if (customer.customerName == "NULL_USER") {
		cout << "User does not exist in database. Make sure it spelled correctly!";
		return;
	}

	transationTotal = (coBuying.pricePerShare * numOfSharesBuying);

	if (customer.availableBal < transationTotal) {
		cout << "You do not have enough funds to purchase disired stock.";
		exit(0);
	}
	else {

		customers[index].investmentCompany = coBuying.name;
		customers[index].amountInvested += transationTotal;
		customers[index].availableBal -= transationTotal;
		customers[index].numberOfShares += numOfSharesBuying;

		cout << "\nBought " << numOfSharesBuying << " shares from " << coBuying.name << " for $" << coBuying.pricePerShare << " each.";
	}
	
}

Company findCompany(string name, Company shares[]) {
	int found;
	string companyName;

	for (int i = 0; i < NUM_OF_COMPANIES; i++) {

		companyName = shares[i].name;
		found = companyName.find(name);

		if (found != string::npos) {
			return shares[i];
		}

	}

	cout << "Company not found. ERROR!";
	exit(0);
}

void showCustomer(Shareholder customer) {
	cout << "\nName: " << customer.customerName;
	cout << "\n  ID: " << customer.accountID;
	cout << "\n  Company Invested In: " << customer.investmentCompany;
	cout << "\n    Number of Shares: " << customer.numberOfShares;
	cout << "\n  Available Balance: " << customer.availableBal;
	cout << "\n  Amount Invested: " << customer.amountInvested;
}

void restart(vector<Shareholder>& customers, Company shares[]) {
	int userChoice;
	cout << "\n\n 1. Add new customer. \n 2. View shares.\n 3. Buy Stock\n 4. Display a customer's information. (Must have at least one customer made!) \n Your Choice: ";
	cin.ignore();
	cin >> userChoice;
	showMenu(userChoice, customers, shares);
}