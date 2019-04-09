#include "Share.h"
#include <string>

using namespace std;


Share::Share() {
	companyName = "TBD";
	pricePerShare = 0;
}

Share::Share(string name, double price) {
	companyName = name;
	pricePerShare = price;
}

string Share::getCompanyName() {
	return companyName;
}

void Share::setCompanyName(string name) {
	companyName = name;
}

double Share::getPricePerShare() {
	return pricePerShare;
}

void Share::setPricePerShare(double price) {
	pricePerShare = price;
}


