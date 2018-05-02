#pragma once
#include <ctime>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#define TIME_MAX 32
using namespace std;

class ConsumptionRecordTuple {
private:
	string accountID;		//use phone number as ID
	string accountName;		//account's name
	int accountOrderCounter;
	string dishID;
	string dishName;
	int dishPrice;
	time_t recordTime = 0;
public:
	ConsumptionRecordTuple();
	ConsumptionRecordTuple(string accountid, string accountname, int accountOrderCounter, string dishid, string dishname, int dishprice);
	ConsumptionRecordTuple(string accountid, string accountname, int accountOrderCounter, string dishid, string dishname, int dishprice, time_t recordtime);
	
	string getAccountID()const;		//use phone number as ID
	string getAccountName()const;		//account's name
	int getAccountOrderCounter()const;
	string getDishID()const;
	string getDishName()const;
	int getDishPrice()const;
	time_t getRecordTime()const;

	void showConsumptionRecordTuple()const;
	void showTime()const;
};