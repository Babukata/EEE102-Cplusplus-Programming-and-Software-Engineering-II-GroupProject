#pragma once
#ifndef _ACCOUNT
#define _ACCOUNT

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

enum {NA = 0, manager = 1, chef = 2, customer =3};

class Account {
	friend void showAccount(const Account& a);
private:
	string accountID;		//use phone number as ID
	string accountPIN;		//personal identification number
	string accountName;		//account's name
	string accountGender = "N/A";	//Gender
	string accountRegion = "N/A";	//Region
	string accountPreference = "N/A";	//account preference of dishes
	int accountIDFLAG = NA;
	int accountDebts = 0;	//account Debts
	int accountOrdersCounter = 1;	// account number of history orders

public:
	~Account();
	Account();
	Account(string id, string pin, string dishName);	//Construct Account object BY creating
	Account(string id, string pin, string dishName, string gender, string region, string preference, int IDFLAG);
	Account(string id, string pin, string dishName, string accountGender, string accountRegion, string accountPreference, int debt, int numOfOrders, int accountIDFLAG);//Construct Account object BY reading history
	string getAccountID()const;
	string getAccountPIN()const;	
	string getAccountName()const;
	string getAccountGender()const;
	string getAccountRegion()const;
	string getAccountPreference()const;
	int getAccountIDFLAG()const;

	void setAccountPIN(const string& s);
	void setAccountName(const string& s);
	void setAccountGender(const string& s);
	void setAccountRegion(const string& s);
	void setAccountPreference(const string& s);
	void setAccountDebts(int d);

	int getAccountDebts()const;
	int getAccountOrderCounter()const;
	void debtsInc(int x);
	void debtsDec(int x);
	void orderPlaced();

};

#endif