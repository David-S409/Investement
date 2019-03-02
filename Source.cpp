#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const int NUM_OF_COMPANIES = 10;

struct Shareholder {
	int accountID, numberOfShares = 0;
	string custumerName, investmentCompany = "";
	double availableBal, amountInvested = 0;
};

struct Company {
	string name;
	double pricePerShare;
};


void storeCompanyInfo(Company shares[]);
string removeEnter(string str1);
Shareholder createCustomer(string name, int accountNumber, double staringBal = 10000);
Shareholder getData();


int main() {
	Company shares[NUM_OF_COMPANIES];
	vector<Shareholder> customers;

	storeCompanyInfo(shares);

	
	customers.push_back(getData());



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

	person.custumerName = name;
	person.accountID = accountNumber;
	person.availableBal = staringBal;

	return person;
}
Shareholder getData() {
	string name;
	cout << "Please enter the name of the customer: ";
	getline(cin, name);
	//cin.ignore();

	int accountNum;
	cout << endl << "Enter account number: ";
	cin >> accountNum;

	
	cout << endl << "Default starting balance is of $10,000";

	return createCustomer(name, accountNum, 10000);
}

string removeEnter(string name) {
	string str(name);
	if (str.find('\n') != string::npos) {
		str.erase(str.begin());
	}
	
		return str;
}

