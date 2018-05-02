#include "ConsumptionRecordTuple.h"

ConsumptionRecordTuple::ConsumptionRecordTuple() {
	accountID = "NA";//use phone number as ID
	accountName = "NA";		//account's name
	dishID = "NA";
	dishName = "NA";
	dishPrice = 0;
	recordTime = time(NULL);
}
ConsumptionRecordTuple::ConsumptionRecordTuple(string accountid, string accountname, int accountordercounter, string dishid, string dishname, int dishprice) {
	accountID = accountid;		//use phone number as ID
	accountName = accountname;	//account's name
	accountOrderCounter = accountordercounter;
	dishID = dishid;
	dishName = dishname;
	dishPrice = dishprice;
	recordTime = time(NULL);
}
ConsumptionRecordTuple::ConsumptionRecordTuple(string accountid, string accountname, int accountordercounter, string dishid, string dishname, int dishprice, time_t recordtime) {
	accountID = accountid;		//use phone number as ID
	accountName = accountname;	//account's name
	accountOrderCounter = accountordercounter;
	dishID = dishid;
	dishName = dishname;
	dishPrice = dishprice;
	recordTime = recordtime;
}

string ConsumptionRecordTuple::getAccountID()const {
	return accountID;
}
string ConsumptionRecordTuple::getAccountName()const {
	return accountName;
}
int ConsumptionRecordTuple::getAccountOrderCounter()const {
	return accountOrderCounter;
}
string ConsumptionRecordTuple::getDishID()const {
	return dishID;
}
string ConsumptionRecordTuple::getDishName()const {
	return dishName;
}
int ConsumptionRecordTuple::getDishPrice()const {
	return dishPrice;
}
time_t ConsumptionRecordTuple::getRecordTime()const {
	return recordTime;
}

void ConsumptionRecordTuple::showTime()const {
	//time(&now);

	// 定义两个变量，存储转换结果
	struct tm tmTmp;
	char stTmp[TIME_MAX];

	// 转换为tm结构
	localtime_s(&tmTmp, &recordTime);

	// 转换为字符串并输出
	asctime_s(stTmp, &tmTmp);
	cout << stTmp;

}

void ConsumptionRecordTuple::showConsumptionRecordTuple()const {
	cout << fixed << left;
	cout << "# " << setw(15) << accountID <<" # "<< setw(12) << accountName << " # " << setw(5) << accountOrderCounter << " # " << setw(12) << dishID << " # " << setw(20)<< dishName << " # " << setw(6)<< dishPrice << " # ";  this->showTime();
	cout << fixed << right;
}
