#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int NUM_OF_COMPANIES = 10;

struct Shareholder {
	int accountID, numberOfShares;
	string custumerName, investmentCompany;
	double availableBal, amountInvested;
};

struct Company {
	string name;
	double pricePerShare;
};

void storeCompanyInfo(Company shares[]);

int main() {
	Company shares[NUM_OF_COMPANIES];

	storeCompanyInfo(shares);

	cout << shares[1].name;
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
		co.name = name;

		shares[i] = co;
	}



}

