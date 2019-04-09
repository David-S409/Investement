#ifndef SHARE_H

#include <string>
using std::string;

class Share {
	string companyName;
	double pricePerShare;

public:
	Share();
	Share(string, double);

	void setCompanyName(string);
	string getCompanyName();

	void setPricePerShare(double);
	double getPricePerShare();

};

#define SHARE_H
#endif

