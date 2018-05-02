#include "Account.h"
#include "Account.h"
#include <iostream>

Account::~Account() {
	;
}
Account::Account() {
	accountID = "00000000";
	accountName = "N/A";
	accountPIN = "888888";
	accountDebts = 0;
	accountOrdersCounter = 1;
}
//Construct Account object BY creating
Account::Account(string id, string pin, string dishName) {
	accountID = id;
	accountPIN = pin;
	accountName = dishName;
	accountDebts = 0;
	accountOrdersCounter = 0;
}

//Construct Account object BY reading history
Account::Account(string id, string pin, string dishName, string gender, string region, string preference, int IDFLAG) {
	accountID = id;
	accountPIN = pin;
	accountName = dishName;
	accountGender = gender;
	accountRegion = region;
	accountPreference = preference;
	accountIDFLAG = IDFLAG;
	accountDebts = 0;
	accountOrdersCounter = 1;
}

Account::Account(string id, string pin, string dishName, string gender, string region, string preference, int debts, int numOfOrders, int IDFLAG) {
	accountID = id;
	accountPIN = pin;
	accountName = dishName;
	accountGender = gender;
	accountRegion = region;
	accountPreference = preference;
	accountDebts = debts;
	accountOrdersCounter = numOfOrders;
	accountIDFLAG = IDFLAG;
}

string Account::getAccountID()const {
	return accountID;
}

string Account::getAccountPIN()const {
	return accountPIN;
}

string Account::getAccountName()const {
	return accountName;
}

int Account::getAccountDebts()const {
	return accountDebts;
}

int Account::getAccountOrderCounter()const {
	return accountOrdersCounter;
}

string Account::getAccountGender()const {
	return accountGender;
}

string Account::getAccountRegion()const {
	return accountRegion;
}

string Account::getAccountPreference()const {
	return accountPreference;
}
int Account::getAccountIDFLAG()const {
	return accountIDFLAG;
}
void Account::setAccountPIN(const string& s) {
	accountPIN = s;
}
void Account::setAccountName(const string& s) {
	accountName = s;
}
void Account::setAccountGender(const string& s) {
	accountGender = s;
}
void Account::setAccountRegion(const string& s) {
	accountRegion = s;
}
void Account::setAccountPreference(const string& s) {
	accountPreference = s;
}
void Account::setAccountDebts(int d) {
	accountDebts = d;
}


void Account::debtsInc(int x) {
	accountDebts -= x;
}

void Account::debtsDec(int x) {
	accountDebts += x;
}

void Account::orderPlaced() {
	accountOrdersCounter++;
}

void showAccount(const Account& a) {
	if(a.accountIDFLAG == manager){
		cout << "# AccountID " << setw(15) << a.getAccountID()<< " # AccountPIN " << setw(23) << a.getAccountPIN() << " #"<< endl ;
		cout << "# ManagerName " << setw(13) << a.getAccountName() << " # Gender " << setw(27) << a.getAccountGender() << " #" << endl;
		cout << "# Region " << setw(18) << a.getAccountRegion() << " # Prefernce " << setw(24) << a.getAccountPreference() << " #" << endl;
	}
	else if (a.accountIDFLAG == chef) {
		cout << "# AccountID " << setw(15) << a.getAccountID() << " # AccountPIN " << setw(23) << a.getAccountPIN() << " #" << endl;
		cout << "# ChefName " << setw(16) << a.getAccountName() << " # Gender " << setw(27) << a.getAccountGender() << " #" << endl;
		cout << "# Region " << setw(18) << a.getAccountRegion() << " # Prefernce " << setw(24) << a.getAccountPreference() << " #" << endl;
	}
	else if (a.accountIDFLAG == customer) {
		cout << "# AccountID " << setw(15) << a.getAccountID() << " # AccountPIN " << setw(23) << a.getAccountPIN() << " #" << endl;
		cout << "# CustomerName " << setw(12) << a.getAccountName() << " # Gender " << setw(27) << a.getAccountGender() << " #" << endl;
		cout << "# Region " << setw(18) << a.getAccountRegion() << " # Prefernce " << setw(24) << a.getAccountPreference() << " #" << endl;
		cout << "# NumberOfOrders " << setw(10) << a.accountOrdersCounter-1 << " # Debts " << setw(28) << a.getAccountDebts() << " #"<< endl;
	}

}