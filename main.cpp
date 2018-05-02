//include the following header files in the standard library
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 

//include the following header files created by ourselves
#include "Account.h"
#include "Dish.h"
#include "RawMaterial.h"
#include "ConsumptionRecordTuple.h"

using namespace std;
using std::cout;

//file name
const char* accountFileName = "account.dat";
const char* dishFileName = "dish.dat";
const char* rawMaterialFileName = "rawMaterial.dat";
const char* consumptionRecordFileName = "consumptionRecord.dat";

//in order to limit the length of various types of data, using enum types contributes to a clear expression
enum accountInfoLimit{ lenAccountID = 15, lenAccountPIN = 10, lenAccountName = 12, lenAccountGender = 6, lenAccountRegion = 12, lenAccountPreference = 24 };
//enum dishInfoLimit { lenDishID = 12, lenDishName = 20, lenDishDescription = 24};
//enum rawMaterialInfoLimit { lenMaterialID = 12, lenMaterialName =12, lenMaterialUnit = 6, lenMaterialDescrption = 29};

void controlPannel(vector<Account>& accountList, vector<Dish>& dishList, vector<RawMaterial>& rawMaterialList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList);
bool isLoggedIn(const Account& x, const string& id, const string& pin);
void waitingOrders(Account& x, vector<Account>& accountList, vector<Dish>& dishList, vector<RawMaterial>& rawMaterialList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList);
void orderADish(Account& x, vector<Dish>& dishList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList, vector<ConsumptionRecordTuple>& currentOrderList, ConsumptionRecordTuple& currentOrder);	//order a dish
void addDishForCustomer(Account& manager, vector<Account>& accountList, vector<Dish>& dishList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList, vector<ConsumptionRecordTuple>& currentOrderList, ConsumptionRecordTuple& currentOrder);
void showBillForCustomer(vector<Account>& accountList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList);

vector<Account> readAccountList(const char* filename);
void writeAccountList(const char* filename, vector<Account> x);
vector<Dish> readDishList(const char* filename);
void writeDishList(const char* filename, vector<Dish> x);
vector<RawMaterial> readRawMaterialList(const char* filename);
void writeRawMaterialList(const char* filename, vector<RawMaterial> x);
vector<ConsumptionRecordTuple> readConsumptionList(const char* filename);
void writeConsumptionList(const char* filename, vector<ConsumptionRecordTuple> x);

//add, delete, modification and show functions of Account, dish and raw material
void registerNewAccount(vector<Account>& accountList, vector<ConsumptionRecordTuple>& consumptionRecordList);	//register new account
void showAccountList(vector<Account>& accountList);
void eraseAccount(vector<Account>& accountList);		//erase an Account 
void modifyAccount(vector<Account>& accountList);	//modify Account info

void addNewDish(vector<Dish>& dishList);	//dishLsit for Browse
void showDishMenuList(vector<Dish>& dishList);
void eraseDish(vector<Dish>& dishList);
void modifyDish(vector<Dish>& dishList);

void addRawMaterial(vector<RawMaterial>& rawMaterialList);
void showRawMaterialList(vector<RawMaterial>& rawMaterialList);
void eraseRawMaterial(vector<RawMaterial>& rawMaterialList);
void modifyRawMaterial(vector<RawMaterial>& rawMaterialList);

//function for input
int intParser();
char charParser();
string strParser(int lenLimit, string name);

struct accountFlatened {
	char accountID[lenAccountID + 1];		//use phone number as ID
	char accountPIN[lenAccountPIN + 1];
	char accountName[lenAccountName + 1];//player's name
	char accountGender[lenAccountGender + 1];
	char accountRegion[lenAccountRegion + 1];
	char accountPreference[lenAccountPreference + 1];
	int accountIDFLAG;
	int accountDebts;
	int accountOrdersCounter;
};
struct dishFlatened {
	char dishID[lenDishID + 1];		//use phone number as ID
	char dishName[lenDishName + 1];//player's name
	char dishDescription[lenDishDescription + 1];
	int dishPrice;
};
struct rawMaterialFlatened {
	char materialID[lenMaterialID + 1];		//use phone number as ID
	char materialName[lenMaterialName + 1];//player's name
	char materialUnit[lenMaterialUnit + 1];
	char materialDescription[lenMaterialDescrption + 1];
	int materialAmount;
	int materialPricePerUnit;
};
struct consumptionRecordTupleFlatened {
	char dishID[lenDishID + 1];
	char dishName[lenDishName + 1];//player's name
	int accountOrdersCounter;
	int dishPrice;
	char accountID[lenAccountID + 1];		//use phone number as ID
	char accountName[lenAccountName + 1];//player's name
	time_t recordTime;
};


int main() {
	system("mode con cols=125");
	Account currentAccount;

	//at the beginning of this program, read four sorts of data into four vectors
	vector<Account> aL = readAccountList(accountFileName);
	vector<Dish> dL = readDishList(dishFileName);
	vector<RawMaterial> rML = readRawMaterialList(rawMaterialFileName);
	vector<ConsumptionRecordTuple> cRTL = readConsumptionList(consumptionRecordFileName);

	//show the control pannel
	controlPannel(aL, dL, rML, cRTL);

	//when exit the program, write all the data contained in four vectors into file
	writeAccountList(accountFileName, aL);
	writeDishList(dishFileName, dL);
	writeRawMaterialList(rawMaterialFileName, rML);
	writeConsumptionList(consumptionRecordFileName, cRTL);
	
	cout << "Exit Successfully.\n";

	return 0;
}

//show the control pannel
void controlPannel(vector<Account>& accountList, vector<Dish>& dishList, vector<RawMaterial>& rawMaterialList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList) {
	bool exitFlag = false;		//a flag for exit
	int select = 0;		//an integer variable for selecting options
	Account currentAccount;		//creat an objective of the class Account
	string ID = "";			//initialize string varibles ID and PIN
	string PIN = "";
	bool logInSuccess = true;		//a flag indicating whether login is successful
	vector<Account>::iterator ptr;		//use iteraor to traverse the vector
	while (exitFlag != true) {
	enum controlPannelOption{ exitSystem, logIn, newAccount};	//creat an enum variable where exitSystem = 0,  logIn =1, newAccount =2
		cout << "0 = exit, 1 = LogIn, 2=CreateNewAccount" << endl;

		select = intParser();
		switch (select) {		//get the selection
		case exitSystem:			//exit function
			exitFlag = true;
			break;

		case logIn:		//login function
			logInSuccess = false;
			cout << "Please Enter your account ID: " << endl;		//get ID and PIN inputted by the user
			getline(cin, ID);
			cout << "Please Enter your account PIN" << endl;
			getline(cin, PIN);
			cout << "Looking for Account... " << endl;
		
			for (ptr = accountList.begin(); ptr != accountList.end();) {
				if(!logInSuccess){
					//use the function isLoggedIn to check if ID and PIN are matched with the element of account list
					if ((logInSuccess = isLoggedIn(*ptr, ID, PIN))){	
						system("pause");
						system("cls");
						// Account x loged in successfully, ready to start ordering
						waitingOrders(*ptr, accountList, dishList, rawMaterialList, consumptionRecordTupleList);
					}
				}
				if (logInSuccess)		
					ptr = accountList.end();
				else
					ptr++;
			}

			if (!logInSuccess){		//ID and PIN did not match correctly, login failed
				cout << "Cannot find account. Wrong ID or PIN Entered" << endl;
				system("pause");
				system("cls");
			}
			break;

		case newAccount:		//registration function
			registerNewAccount(accountList, consumptionRecordTupleList);
			system("pause");
			system("cls");
			break;

		default:
			break;
		}
	}

}

//No parameter to limit, return value is a character inputted by user
char charParser() {
	char temp;
	bool isErr = true;
	//while (input failed) or (input succeeded with redundant tail, clear steream and repeat)
	while ((isErr = !(cin >> temp)) || (!isErr && cin.get() != '\n')) {
		if (isErr) { cin.clear(); }
		//reset cin
		while (cin.get() != '\n')//clear a whole line
			continue;
		cout << "\t\tPlease enter a character: ";
	}
	return temp;
}

// the function for checking if login is successful
bool isLoggedIn(const Account& x, const string& id, const string& pin) {
	if (!(x.getAccountID().compare(id) || x.getAccountPIN().compare(pin))) {
		cout << "Log in successfully." << endl;
		return true;
	}
	return false;
}

//the function for customers to order dishes
void orderADish(Account& x, vector<Dish>& dishList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList, vector<ConsumptionRecordTuple>& currentOrderList, ConsumptionRecordTuple& currentOrder) {
	char ch;
	int repeatedOrder = 0;
	string orderedDish;
	bool dishFindFLAG = false;
	bool continueOrder = false;
	dishFindFLAG = false;
	if (dishList.size() == 0)	
		cout << "Sorry, the menue is currently empty." << endl;
	else {
		do {
			showDishMenuList(dishList);		//show menu
			cout << "Please Enter the dish ID you want to order: ";
			getline(cin, orderedDish);		//get the dish ID which is ordered by user
			for (auto &Adish : dishList) {
				if (!Adish.getDishID().compare(orderedDish)) {	// if the same ID is found
					repeatedOrder = 0;	
					dishFindFLAG = true;
					for (auto &o : currentOrderList) {		//check if this dish has been ordered
						if (!o.getDishID().compare(orderedDish))
							repeatedOrder++;
					}
					if (repeatedOrder == 0) {		//if it has not been ordered, place an order of this dish
						cout << "Order Placed.";
						currentOrder = ConsumptionRecordTuple(x.getAccountID(), x.getAccountName(), x.getAccountOrderCounter(), Adish.getDishID(), Adish.getDishName(), Adish.getDishPrice());
						currentOrderList.push_back(currentOrder);    // order is successful
					}
					else {		//if it has been ordered, reconfirm it
						cout << "You have already added" << repeatedOrder << " MORE Dishes of " << Adish.getDishName() << ". Are you sure to ADD one more SAME dish to this history record?(Y/N)" << endl;

						ch = charParser();
						if (ch == 'y' || ch == 'Y') {
							cout << "Order Placed." << endl;
							currentOrder = ConsumptionRecordTuple(x.getAccountID(), x.getAccountName(), x.getAccountOrderCounter(), Adish.getDishID(), Adish.getDishName(), Adish.getDishPrice());
							currentOrderList.push_back(currentOrder);	 // order is successful
						}
						else {	// do not want to add one more same dish, quit this order
							cout << "Order quited." << endl;
						}
					}
				}
				if (!dishFindFLAG)		//if ID not found
					cout << "Sorry, we currentlt do not serve this dish." << endl;
			}
			cout << "Any Dish else?(Y/N): ";		//if add other dishes
			ch = charParser();
			if (ch == 'y' || ch == 'Y')
				continueOrder = true;
			else {
				continueOrder = false;
				for (auto& z : currentOrderList)
					consumptionRecordTupleList.push_back(z);		//write the total added dishes into the vector
			}
			system("cls");
		} while (continueOrder);
	}
}

void addDishForCustomer(Account& manager, vector<Account>& accountList, vector<Dish>& dishList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList, vector<ConsumptionRecordTuple>& currentOrderList, ConsumptionRecordTuple& currentOrder) {
	char ch;
	int repeatedOrder = 0;
	int temp = 1;
	string accountID;
	string orderedDish;
	bool dishFindFLAG = false;
	bool continueOrder = false;
	bool accountFindFLAG = false;
	dishFindFLAG = false;
	int historyOrderID = 0;			//the order of a history order
	int orderCounter = 0;				//order times
	int totalDishCount = 0;			//how many dishes in an order
	int billEveryTime = 0;				//the bill of one order
	int totalBill = 0;						//total bill

	showAccountList(accountList);		//show the account list
	cout << "Please Enter the Account ID you want add dish to: ";
	getline(cin, accountID);		//get the account id which the user want add dish to
	for (auto &x : accountList) {
		if (!x.getAccountID().compare(accountID)) {		//if ID is found
			if (x.getAccountIDFLAG() == customer) {			//do an identity check, because only customers need to order a dish
				cout << "Account found." << endl;
				system("pause");
				system("cls");
				//show the information of history ordered dishes
				cout << "Currently Account " << x.getAccountID() << " Customer " << x.getAccountName() << " have " << x.getAccountOrderCounter() - 1 << " times of Consuption Record." << endl;
				cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "# Account ID      # Account Name #CRID   #DishID        #DishName              #Price   #RecordTime" << endl;
				cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				for (historyOrderID = 1; historyOrderID != x.getAccountOrderCounter(); historyOrderID++) {
					billEveryTime = 0; orderCounter = 0;
					for (auto &y : consumptionRecordTupleList) {
						if (!y.getAccountID().compare(accountID) && (y.getAccountOrderCounter() == historyOrderID)) {
							y.showConsumptionRecordTuple();
							cout << "------------------------------------------------------------------------------------------------------------------" << endl;
							orderCounter++;
							totalDishCount++;
							billEveryTime += y.getDishPrice();
							totalBill += y.getDishPrice();
						}
					}
					if (orderCounter > 0) {
						cout << "Totally " << orderCounter << " Dishes for ConsuptionRecord #" << historyOrderID << ", Bill: " << billEveryTime << endl;
						cout << "------------------------------------------------------------------------------------------------------------------" << endl;
					}
					else
						cout << "Sorry, cannot find history order record for Order #" << historyOrderID << " for customer " << x.getAccountID() << endl;
					cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				}
				cout << "##################################################################################################################" << endl;
				cout << "Totally " << totalDishCount << " Dishes in Customer " << x.getAccountID() << " " << x.getAccountName() << " History Record, Total Bill: " << totalBill << endl;

				//ask user which consumption record he want to add to
				cout << "To which Consumption Record you want to Add? Please Enter CRID (Consumption Record ID): " << endl ;
				temp = intParser();		//get the order of the history consumption

				if (!(temp <= 0 || temp >= x.getAccountOrderCounter())) {

					system("pause");
					system("cls");

					if (dishList.size() == 0)
						cout << "Sorry, the menu is currently empty." << endl;
					else {

						//start to add dish for customer
						do {
							showDishMenuList(dishList);
							cout << "Please Enter the dish ID you want to add to the consumer: ";
							getline(cin, orderedDish);
							dishFindFLAG = false;
							for (auto &Adish : dishList) {
								if (!Adish.getDishID().compare(orderedDish)) {
									repeatedOrder = 0;
									dishFindFLAG = true;
									for (auto &o : currentOrderList) {
										if (!o.getDishID().compare(orderedDish))
											repeatedOrder++;
									}
									if (repeatedOrder == 0) {
										cout << "Order Placed Successfully.";
										currentOrder = ConsumptionRecordTuple(x.getAccountID(), x.getAccountName(), temp, Adish.getDishID(), Adish.getDishName(), Adish.getDishPrice());
										currentOrderList.push_back(currentOrder);
									}
									else {
										cout << "You have ordered " << repeatedOrder << " Dishes of " << Adish.getDishName() << ". Are you sure to order one more SAME dish?(Y/N)" << endl;

										ch = charParser();
										if (ch == 'y' || ch == 'Y') {
											cout << "Order placed." << endl;
											currentOrder = ConsumptionRecordTuple(x.getAccountID(), x.getAccountName(), temp, Adish.getDishID(), Adish.getDishName(), Adish.getDishPrice());
											currentOrderList.push_back(currentOrder);
										}
										else {
											cout << "Order quited." << endl;
										}
									}
								}
								
							}
							if (!dishFindFLAG)
								cout << "Sorry, we currentlt do not serve this dish." << endl;
							cout << "Any Dish else?(Y/N): ";
							ch = charParser();
							if (ch == 'y' || ch == 'Y')
								continueOrder = true;
							else {
								continueOrder = false;
								for (auto& z : currentOrderList)
									consumptionRecordTupleList.push_back(z);
							}
							system("cls");
						} while (continueOrder);
					
					}
				}
				else { cout << "Sorry dishes can only be added to EXISTED histroy record" << endl; }
						accountFindFLAG = true;
				
			}
			else{		//only customers need to order a dish
				cout << "Sorry, cannot add dishes for Manager or Chef." << endl;
				accountFindFLAG = true;
			}
	}
	
	} // perform tasks on chosen account
	if (!accountFindFLAG) {
		cout << "Sorry, cannnot find account " << accountID << " to add Dishes." << endl;
	}
}

void showBillForCustomer(vector<Account>& accountList,vector<ConsumptionRecordTuple>& consumptionRecordTupleList) {
	string accountID;
	int historyOrderID = 0;			//the order of a history order
	int orderCounter = 0;				//order times
	int totalDishCount = 0;			//how many dishes in an order
	int billEveryTime = 0;				//the bill of one order
	int totalBill = 0;						//total bil
	showAccountList(accountList);		//show account list
	cout << "Please Enter the Account ID you want show bill to: ";
	getline(cin, accountID);		//get someone's account ID
	for (auto &a : accountList) {
		if (!a.getAccountID().compare(accountID)) {
			if (!(a.getAccountIDFLAG() == manager || a.getAccountIDFLAG() == chef)) {		//do an identity check, because only customers have a bill
				cout << "Account found." << endl;
				system("pause");
				system("cls");
				//show the information of all history bills 
				cout << "Currently Account " << a.getAccountID() << " Customer " << a.getAccountName() << " have " << a.getAccountOrderCounter() - 1 << " times of Consuption Record." << endl;
				cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "# Account ID      # Account Name #CRID   #DishID        #DishName              #Price   #RecordTime" << endl;
				cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				for (historyOrderID = 1; historyOrderID != a.getAccountOrderCounter(); historyOrderID++) {
					billEveryTime = 0; orderCounter = 0;
				for (auto &x : consumptionRecordTupleList) {
					if (!x.getAccountID().compare(accountID) && (x.getAccountOrderCounter() == historyOrderID)) {
						x.showConsumptionRecordTuple();
						cout << "------------------------------------------------------------------------------------------------------------------" << endl;
						orderCounter++;
						totalDishCount++;
						billEveryTime += x.getDishPrice();
						totalBill += x.getDishPrice();
					}
				}
				if (orderCounter > 0){
					cout << "Totally " << orderCounter << " Dishes for ConsuptionRecord #" << historyOrderID << ", Bill: " << billEveryTime << endl;
					cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				}
				else     //order counter = 0 which means no history bill
					cout << "Sorry, cannot find history order record for Order #" << historyOrderID << " for customer " << a.getAccountID() << endl;
				cout << "------------------------------------------------------------------------------------------------------------------" << endl;
				}
				cout << "##################################################################################################################" << endl;
				cout << "Totally " << totalDishCount << " Dishes in Customer " << a.getAccountID() << " " << a.getAccountName() << " History Record, Total Bill: " << totalBill << endl;
			}
			else         // only customers have a bill
				cout << "Sorry, Manager or Chef does not have a record of debts." << endl;
		}
	}
}

// waiting  order interface
void waitingOrders(Account& x, vector<Account>& accountList, vector<Dish>& dishList, vector<RawMaterial>& rawMaterialList, vector<ConsumptionRecordTuple>& consumptionRecordTupleList) {
	
	int select = 0;		//a varible for selecting the function
	int totalBill = 0;
	int totalExpenditure = 0;
	int totalIncome = 0;
	int repeatedOrder = 0;
	bool dishFindFLAG = false;
	bool exitFlag = false;		//a flag for exit
	bool continueOrder = false;
	string orderedDish;
	vector<ConsumptionRecordTuple> currentOrderList;
	ConsumptionRecordTuple currentOrder;
	
	switch(x.getAccountIDFLAG()){	//the case varies from the identity of account x
	case manager:
		cout << "Welcome back, Manager " << x.getAccountName() <<". Waiting orders! ";

		while(!exitFlag){
			cout << "Please give command: " << endl;
			cout << "############################################ConrolPannel#####################################################" << endl;
			cout << "# 0=LogOut          #                                                                                       #" << endl;
			cout << "# 1=showCustomer    # 4=addNewAccount     # 7=modifyAccount  # 10=deleteAccount     # 13=showBillForCustomer#" << endl;
			cout << "# 2=showMenu        # 5=addNewDish        # 8=modifyDish     # 11=deleteDish        # 14=addDishForCustomer #" << endl;
			cout << "# 3=showRawMaterial # 6=addNewRawMaterial # 9=modifyMaterial # 12=deleteRawMaterial # 15=showReport         #" << endl;
			cout << "#############################################################################################################" << endl;
			
		select = intParser();			//get the choice
		switch(select){
			//enum type contributes a clear expression, where exitSystem = 0, showCustomer = 1 ,etc.
		enum{	logOut, 
				showCustomer, showMenu, showRawMaterial, 
				newAccount,	newDish, newRawMaterial, 
				modifyAccountInList, modifyDishInMenu, modifyRawMaterialInList,
				deleteAccount, deleteDish, deleteRawMaterial, 
				showBill ,addDishToCustomer, showReport
		};
			case logOut:	// get out of the while loop then exit
			exitFlag = true;
			system("pause");
			system("cls");
			break;

			case showCustomer:	//show the information of all accounts
			showAccountList(accountList);
			system("pause");
			system("cls");
			break;

			case showMenu:		//show the menu
			showDishMenuList(dishList);
			system("pause");
			system("cls");
			break;

			case showRawMaterial:		//show the raw material
			showRawMaterialList(rawMaterialList);
			system("pause");
			system("cls");
			break;

			case newAccount:		//add new account
			registerNewAccount(accountList, consumptionRecordTupleList);
			system("pause");
			system("cls");
			break;

			case newDish:		//add new dish
			addNewDish(dishList);
			system("pause");
			system("cls");
			break;

			case newRawMaterial:		//add new material
			addRawMaterial(rawMaterialList);
			system("pause");
			system("cls");
			break;

			case modifyAccountInList:		//modify the information of accounts in the list
			modifyAccount(accountList);
			system("pause");
			system("cls");
			break;

			case modifyDishInMenu:		//modify the menu
			modifyDish(dishList);
			system("pause");
			system("cls");
			break;

			case modifyRawMaterialInList:		//modify the raw material in the list
			modifyRawMaterial(rawMaterialList);
			system("pause");
			system("cls");
			break;

			case deleteAccount:		//delete accounts
			eraseAccount(accountList);
			system("pause");
			system("cls");
			break;

			case deleteDish:		//delete dishes
			eraseDish(dishList);
			system("pause");
			system("cls");
			break;

			case deleteRawMaterial:			//delete raw materials
			eraseRawMaterial(rawMaterialList);
			system("pause");
			system("cls");
			break;

			case showBill:		//show the bill
				showBillForCustomer(accountList, consumptionRecordTupleList);
				system("pause");
				system("cls");
			break;

			case addDishToCustomer:		//manager add dish for customer
				addDishForCustomer(x, accountList, dishList, consumptionRecordTupleList, currentOrderList, currentOrder);
				system("pause");
				system("cls");
			break;

			case showReport:		//show the total income, expenditure and profit
				totalIncome = 0;
				totalExpenditure = 0;
				for (auto& billRecord : consumptionRecordTupleList) {
					totalIncome += billRecord.getDishPrice();
				}
				for (auto& material : rawMaterialList) {
					totalExpenditure += material.getMaterialTotalPrice();
				}
				cout << "Total Expenditure: " << totalExpenditure << endl;
				cout << "Total Income: " << totalIncome << endl;
				cout << "The gross profit is " << totalIncome - totalExpenditure << endl;
				system("pause");
				system("cls");
			break;

			default:
				system("pause");
				system("cls");
			break;
			}
		}
		break;

	case chef:	
		cout << "Welcome back, Chef " << x.getAccountID() << ": "<< x.getAccountName() << endl;

		while (!exitFlag) {
			cout << "Please give command: " << endl;
			cout << "#####################################ConrolPannel####################################" << endl;
			cout << "# 0=LogOut           #                                                              #" << endl;
			cout << "# 1=showMenu         # 3=addNewDish        # 5=modifyDish     # 7=deleteDish        #" << endl;
			cout << "# 2=showRawMaterial  # 4=addNewRawMaterial # 6=modifyMaterial # 8=deleteRawMaterial #" << endl;
			cout << "#####################################################################################" << endl;
	
			select = intParser();
			switch (select) {
				enum {
					logOut,
					showMenu, showRawMaterial,
					newDish, newRawMaterial,
					modifyDishInMenu, modifyRawMaterialInList,
					deleteDish, deleteRawMaterial,
				};
			case logOut:
				exitFlag = true;
				break;

			case showMenu:
				showDishMenuList(dishList);
				system("pause");
				system("cls");
				break;

			case showRawMaterial:
				showRawMaterialList(rawMaterialList);
				system("pause");
				system("cls");
				break;

			case newDish:
				addNewDish(dishList);
				system("pause");
				system("cls");
				break;

			case newRawMaterial:
				addRawMaterial(rawMaterialList);
				system("pause");
				system("cls");
				break;

			case modifyDishInMenu:
				modifyDish(dishList);
				system("pause");
				system("cls");
				break;

			case modifyRawMaterialInList:
				modifyRawMaterial(rawMaterialList);
				system("pause");
				system("cls");
				break;

			case deleteDish:
				eraseDish(dishList);
				system("pause");
				system("cls");
				break;

			case deleteRawMaterial:
				eraseRawMaterial(rawMaterialList);
				system("pause");
				system("cls");
				break;

			default:
				break;
			}
		}
		break;
		
	case customer:
		cout << "Welcome back, Dear " << x.getAccountName() << endl;

		while (!exitFlag) {
			cout << "Please give command: " << endl;
			cout << "##ConrolPannel##" << endl;
			cout << "# 0=LogOut     #" << endl;
			cout << "# 1=showMenu   #" << endl;
			cout << "# 2=placeOrder #" << endl;
			cout << "# 3=showBill   #" << endl;
			cout << "################" << endl;

			select = intParser();
			switch (select) {
				enum {
					logOut,
					showMenu,
					placeOrder,
					showBill
				};
			case logOut:
				if (currentOrderList.size() > 0)
					x.orderPlaced();
				exitFlag = true;
				break;

			case showMenu:
				showDishMenuList(dishList);
				system("pause");
				system("cls");
				break;

			case placeOrder:		//place an order for himself
				orderADish(x, dishList, consumptionRecordTupleList, currentOrderList, currentOrder);
				system("pause");
				system("cls");
				break;

			case showBill:		//show his bill
				totalBill = 0;
				for (auto& billRecord : consumptionRecordTupleList) {
					if (billRecord.getAccountID() == x.getAccountID()) {
						totalBill += billRecord.getDishPrice();
						billRecord.showConsumptionRecordTuple();
					}
				}
				cout << "The total bill is: " << totalBill << endl;
				system("pause");
				system("cls");
				break;

			default:
				break;
			}
		}

		break;
	}
	
	
}

vector<Account> readAccountList(const char* filename) {
	accountFlatened aF;	//aF is a structure variable for storing the information of one temporary person
	vector<Account> accountList;	// this vector is used for storing all the information of accounts in the file
	// caution!
	cout << fixed << right;

	//show initial constents
	ifstream fin;
	fin.open(filename, ios_base::in | ios_base::binary); //binary file
														 //NOTE: some system doesn't accept ios_base::binary mode

	if (fin.is_open()) {			//if open file successfully

		while (fin.read((char*)&aF, sizeof aF)) {			//if read data with a length of (sizeof aF), the loop goes on
			bool repetitionFlag = false;			//a variable for detecting whether the ID is repeated
			//read the data of aF into the element(class Account) of the vector
			Account x = Account(aF.accountID, aF.accountPIN, aF.accountName, aF.accountGender, aF.accountRegion, aF.accountPreference, aF.accountDebts, aF.accountOrdersCounter, aF.accountIDFLAG);
			for (auto & y : accountList) {
				if (!(y.getAccountID().compare(x.getAccountID()))) //if ID is repeatd set flag true
					repetitionFlag = true;
			}
			if (!repetitionFlag) { // if not repeated push back
				accountList.push_back(x);
			}
		}
		fin.close();		//close the file
	}
	return accountList;
}

void writeAccountList(const char* filename, vector<Account> x) {
	//Add new data
	accountFlatened aF;
	vector<Account>::iterator ptr;		//aF is a structure variable for storing the information of one temporary person
	ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	//NOTE: some systems don't accept the ios_base::binary mode
	if (!fout.is_open()) {				//if open file failed, exit the program
		cerr << "Cant't open " << filename << " file for output:\n";
		exit(EXIT_FAILURE);
	}
	//if open file successfully, copy all the elements of the vector into file
	for (ptr = x.begin(); ptr != x.end(); ptr++) {
		strcpy_s(aF.accountID, ptr->getAccountID().c_str());			//copy the data of one element into aF
		strcpy_s(aF.accountPIN, ptr->getAccountPIN().c_str());
		strcpy_s(aF.accountName, ptr->getAccountName().c_str());
		strcpy_s(aF.accountGender, ptr->getAccountGender().c_str());
		strcpy_s(aF.accountRegion, ptr->getAccountRegion().c_str());
		strcpy_s(aF.accountPreference, ptr->getAccountPreference().c_str());
		aF.accountIDFLAG = ptr->getAccountIDFLAG();
		aF.accountDebts = ptr->getAccountDebts();
		aF.accountOrdersCounter = ptr->getAccountOrderCounter();
		fout.write((char*)& aF, sizeof aF);	//write the data of aF into file on each iteration
	}
	fout.close();		//close the file
}

vector<Dish> readDishList(const char* filename) {
	dishFlatened dF;		//dF is a structure variable for storing the information of one temporary dish
	vector<Dish> dishList;	// this vector is used for storing all the information of dishes in the file
	// caution!
	cout << fixed << right;

	//show initial constents
	ifstream fin;
	fin.open(filename, ios_base::in | ios_base::binary); //binary file
														 //NOTE: some system doesn't accept ios_base::binary mode

	if (fin.is_open()) {

		while (fin.read((char*)&dF, sizeof dF)) {		//if read data with a length of (sizeof dF), the loop goes on
			bool repetitionFlag = false;	
			//read the data of dF into the element(class Dish )of the vector
			Dish x = Dish(dF.dishID, dF.dishName, dF.dishDescription, dF.dishPrice);
			for (auto & y : dishList) {
				if (!(y.getDishID().compare(x.getDishID()))) //if ID is repeatd set flag true
					repetitionFlag = true;
			}
			if (!repetitionFlag) { // if not repeated push back
				dishList.push_back(x);
			}
		}
		fin.close();
	}
	return dishList;
}

void writeDishList(const char* filename, vector<Dish> x) {
	//Add new data
	dishFlatened dF;		//dF is a structure variable for storing the information of one temporary dish
	vector<Dish>::iterator ptr;
	ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	//NOTE: some systems don't accept the ios_base::binary mode
	if (!fout.is_open()) {
		cerr << "Cant't open " << filename << " file for output:\n";
		exit(EXIT_FAILURE);
	}
	//if open file successfully, copy all the elements of the vector into file
	for (ptr = x.begin(); ptr != x.end(); ptr++) {
		strcpy_s(dF.dishID, ptr->getDishID().c_str());		//copy the data of one element into dF
		strcpy_s(dF.dishName, ptr->getDishName().c_str());
		strcpy_s(dF.dishDescription, ptr->getDishDescription().c_str());
		dF.dishPrice = ptr->getDishPrice();
		
		fout.write((char*)& dF, sizeof dF);	//write the data of dF into file on each iteration
	}
	fout.close();
}

vector<RawMaterial> readRawMaterialList(const char* filename) {
	rawMaterialFlatened rF;	//rF is a structure variable for storing the information of one temporary raw material
	vector<RawMaterial> materialList;		// this vector is used for storing all the information of materials in the file
	// caution!
	cout << fixed << right;

	//show initial constents
	ifstream fin;
	fin.open(filename, ios_base::in | ios_base::binary); //binary file
														 //NOTE: some system doesn't accept ios_base::binary mode

	if (fin.is_open()) {	

		while (fin.read((char*)&rF, sizeof rF)) {		//if read data with a length of (sizeof rF), the loop goes on
			bool repetitionFlag = false;	
			RawMaterial x = RawMaterial(rF.materialID, rF.materialName, rF.materialAmount, rF.materialUnit, rF.materialPricePerUnit, rF.materialDescription);
			for (auto & y : materialList) {
				if (!(y.getMaterialID().compare(x.getMaterialID()))) //if ID is repeatd set flag true
					repetitionFlag = true;
			}
			if (!repetitionFlag) { // if not repeated push back
				materialList.push_back(x);
			}
		}
		fin.close();
	}
	return materialList;
}

void writeRawMaterialList(const char* filename, vector<RawMaterial> x) {
	//Add new data
	rawMaterialFlatened rMF;		//rMF is a structure variable for storing the information of one temporary material
	vector<RawMaterial>::iterator ptr;	
	ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	//NOTE: some systems don't accept the ios_base::binary mode
	if (!fout.is_open()) {
		cerr << "Cant't open " << filename << " file for output:\n";
		exit(EXIT_FAILURE);
	}
	//if open file successfully, copy all the elements of the vector into file
	for (ptr = x.begin(); ptr != x.end(); ptr++) {
		strcpy_s(rMF.materialID, ptr->getMaterialID().c_str());		//copy the data of one element into rMF
		strcpy_s(rMF.materialName, ptr->getMaterialName().c_str());
		strcpy_s(rMF.materialUnit, ptr->getMaterialUnit().c_str());
		strcpy_s(rMF.materialDescription, ptr->getMaterialDescrption().c_str());
		rMF.materialAmount = ptr->getMaterialAmount();
		rMF.materialPricePerUnit = ptr->getMaterialPricePerUnit();
		fout.write((char*)& rMF, sizeof rMF);		//write the data of rMF into file on each iteration
	}
	fout.close();		//close the file
}
vector<ConsumptionRecordTuple> readConsumptionList(const char* filename) {
	consumptionRecordTupleFlatened cRTF;		//cRTF is a structure variable for storing the information of one temporary consumption record
	vector<ConsumptionRecordTuple> consumptionRecordList;		// this vector is used for storing all the information of consumption records in the file
	// caution!
	cout << fixed << right;

	//show initial constents
	ifstream fin;
	fin.open(filename, ios_base::in | ios_base::binary); //binary file
														 //NOTE: some system doesn't accept ios_base::binary mode

	if (fin.is_open()) {	

		while(fin.read((char*)&cRTF, sizeof cRTF)) {		//if read data with a length of (sizeof cRTF), the loop goes on
			bool repetitionFlag = false;	
			//read the data of cRTF into the element(class ConsumptionRecordTuple) of the vector
			ConsumptionRecordTuple x = ConsumptionRecordTuple(cRTF.accountID, cRTF.accountName, cRTF.accountOrdersCounter, cRTF.dishID, cRTF.dishName, cRTF.dishPrice, cRTF.recordTime);
			for (auto & y : consumptionRecordList) {
				if (!(y.getAccountID().compare(x.getAccountID()))) //if ID is repeatd set flag true
					repetitionFlag = false;
			}
			if (!repetitionFlag) { // if not repeated push back
				consumptionRecordList.push_back(x);
			}
		}

		fin.close();
	}
	return consumptionRecordList;
}

void writeConsumptionList(const char* filename, vector<ConsumptionRecordTuple> x) {

	//Add new data
	consumptionRecordTupleFlatened cRTF;		//cRTF is a structure variable for storing the information of one temporary consumption record
	vector<ConsumptionRecordTuple>::iterator ptr;
	ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	//NOTE: some systems don't accept the ios_base::binary mode
	if (!fout.is_open()) {
		cerr << "Cant't open " << filename << " file for output:\n";
		exit(EXIT_FAILURE);
	}
	//if open file successfully, copy all the elements of the vector into file
	for (ptr = x.begin(); ptr != x.end(); ptr++) {
		strcpy_s(cRTF.accountID, ptr->getAccountID().c_str());		//copy the data of one element into cRTF
		strcpy_s(cRTF.accountName, ptr->getAccountName().c_str());
		cRTF.accountOrdersCounter = ptr->getAccountOrderCounter();
		strcpy_s(cRTF.dishID, ptr->getDishID().c_str());
		strcpy_s(cRTF.dishName, ptr->getDishName().c_str());
		cRTF.dishPrice = ptr->getDishPrice();
		cRTF.recordTime = ptr->getRecordTime();
		
		fout.write((char*)& cRTF, sizeof cRTF);	//write the data of cRTF into file on each iteration
	}
	fout.close();
}

void registerNewAccount(vector<Account>& accountList, vector<ConsumptionRecordTuple>& consumptionRecordList) {
	//Add new data
	bool alreadyRegisteredFlag = false;		//a bool variable for checking if some types of data has been registered
	bool strLengthFitFlag = true;		//a bool variable for checking if the length of string is appropriate
	string accountID;			//Declare several string variables for the registration necessary information
	string accountPIN;
	string accountName;
	string accountGender;
	string accountRegion;
	string accountPreference;
	int accountIDFLAG;		//a flag for choosing the acount type

	do {
		strLengthFitFlag = true;
		cout << "Which account type you want to register: 1=Manager, 2=Chef, 3=Customer: ";//(enter a blank line to quit)
		accountIDFLAG = intParser();		//read the choice
		switch (accountIDFLAG) {
		case manager:		//register a manager account
			cout << "Now regitering as manager: " << endl;
			break;
		case chef:		//register a chef account
			cout << "Now regitering as chef: " << endl;
			break;
		case customer: 		//register a customer account
			cout << "Now regitering as customer: " << endl;
			break;
		default: 	//wrong input
			cout << "Sorry, wrong command entered. Try again:" << endl;
			strLengthFitFlag = false;		// the do-while loop will continue
			break;
		}
	} while ((!strLengthFitFlag));

	//get the qualified ID
	do {
		strLengthFitFlag = true;
		if (alreadyRegisteredFlag)
			cout << "Sorry, this ID has been registered or existed in history Consumption Record.";
		cout << "Enter account ID: ";		//read the ID inputted
		alreadyRegisteredFlag = false;
		getline(cin, accountID);
		for (auto & x : accountList) {
			if (!(accountID.compare(x.getAccountID()))) //if ID is repeatd set flag true
				alreadyRegisteredFlag = true;
		}
		for (auto & x : consumptionRecordList) {
			if (!(accountID.compare(x.getAccountID()))) //if ID is repeatd set flag true
				alreadyRegisteredFlag = true;
		}
		if (accountID.size() > lenAccountID)	//if the length of ID > 20, set flag false
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountID << " characters";
	} while (alreadyRegisteredFlag || (!strLengthFitFlag));
	//only when both the length and repeatability of ID satisfy the demand, the program can get out of this do-while loop

	//get the qualified name
	do {
		strLengthFitFlag = true;
		cout << "Enter the ACCOUNT name : ";//(enter a blank line to quit)
		getline(cin, accountName);
		if (accountName.size() > lenAccountName)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, Name length cannot exceed " << lenAccountName << " characters";
	} while ((!strLengthFitFlag));

	//get the qualified PIN
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's PIN: ";
		getline(cin, accountPIN);
		if (accountPIN.size() > lenAccountPIN)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, PIN length cannot exceed " << lenAccountPIN << " characters";
	} while ((!strLengthFitFlag));

	//get the qualified gender
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Gender: ";
		getline(cin, accountGender);
		if (accountGender.size() > lenAccountGender)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, Gender length cannot exceed " << lenAccountGender << " characters";
	} while ((!strLengthFitFlag));

	//get the qualified region
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Region: ";
		getline(cin, accountRegion);
		if (accountRegion.size() > lenAccountRegion)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, Region length cannot exceed " << lenAccountRegion << " characters";
	} while ((!strLengthFitFlag));

	//get the qualified motto
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Preference: ";
		getline(cin, accountPreference);
		if (accountPreference.size() > lenAccountPreference)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, Preference length cannot exceed " << lenAccountPreference << " characters";
	} while ((!strLengthFitFlag));

	//creat an objective of the class temp for storing the data of a new account
	Account temp = Account(accountID, accountPIN, accountName, accountGender, accountRegion, accountPreference, accountIDFLAG);
	//write temp to the end of the vetctor accountList
	accountList.push_back(temp);
}

//print the account list
void showAccountList(vector<Account>& accountList) {
	//show manager accounts
	cout << "############################MANGER################################" << endl;
	for (auto &x : accountList) {
		if(x.getAccountIDFLAG() == manager){
			showAccount(x);
			cout << "------------------------------------------------------------------" << endl;
		}
	}
	cout << "##################################################################" << endl;
	//show chef accounts
	cout << "#############################CHEF#################################" << endl;
	for (auto &x : accountList) {
		if (x.getAccountIDFLAG() == chef){
			showAccount(x);
			cout << "------------------------------------------------------------------" << endl;
		}
	}
	cout << "##################################################################" << endl;
	//show customer accounts
	cout << "#############################CUSTOMER#############################" << endl;
	for (auto &x : accountList) {
		if (x.getAccountIDFLAG() == customer){
			showAccount(x);
			cout << "------------------------------------------------------------------" << endl;
		}
	}
	cout << "############################END#OF#LIST###########################" << endl;
}

//delete accounts function
void eraseAccount(vector<Account>& accountList) {
	string accountID;		//a string variable for storing the account ID which is going to be de deleted
	bool accountFoundFlag = false;		//a flag represents whether the account is found
	char ch;		//a char variable for confirming the delete operation
	showAccountList(accountList);		//show the account list
	cout << "Please Enter the dish ID you want to delete: " << endl;
	getline(cin, accountID);		//get the account ID which is going to be de deleted
	vector<Account>::iterator ptr;		//use iterator to traverse the vector
	for (ptr = accountList.begin(); ptr != accountList.end(); ptr++) {
		if (!(accountID.compare(ptr->getAccountID()))) { //if same ID found
			accountFoundFlag = true;		//set the flag true
			cout << "Account found:" << endl;
			cout << "Are you sure to delete the account? (Y/N)" << endl;		//confirm the delete operation
			ch = charParser();
			if (ch == 'Y' || ch == 'y') {	//Be sure to delete, then use erase( ) to delete
				accountList.erase(ptr, (ptr + 1));
				ptr = accountList.begin();		//the pointer should be reset to the beginning for a double check
				cout << "Account deleted successfully!" << endl;
			}
			else		//Not sure to delete
				cout << "Account deletion quitted";
		}
	}
	if(!accountFoundFlag){		//if the ID is not found
		cout << "Sorry, cannot find appointed account." << endl;
	}
}

//modify accounts function
void modifyAccount(vector<Account>& accountList) {
	string accountID;			//a string variable for storing the account ID which is going to be de modified
	bool accountFoundFlag = false;			//a flag represents whether the account is found
	showAccountList(accountList);	//show the account list
	if(accountList.size() > 0){
	cout << "Please Enter the Account ID you want to modify: " << endl;
	getline(cin, accountID);	//get the account ID which is going to be de modified
	vector<Account>::iterator ptr;	//use iterator to traverse the vector
	
	for (ptr = accountList.begin(); ptr != accountList.end(); ptr++) {
		if (!(accountID.compare(ptr->getAccountID()))) { //if same ID found
			accountFoundFlag = true;	//set the flag true
			cout << "Account found..." << endl;
			enum { finishModification, accountPIN, accountName, accountGender, accountRegion, accountPrefernce, accountDebts };//enum type contributes to clear modification options
			int select;		//an int variable for selecting options
			bool modificationDoneFlag = false;		//a flag represents whether the modification is done
			while (modificationDoneFlag != true) { //strats to modify
				cout << "Please give command to modify:" << endl;
				cout << "0 = Fnish Modification, 1 = AccountPIN, 2=AccountName, 3=AccountGender, 4=AccountRegion, 5=accountPrefernce" << endl;
				select = intParser();	//get the choice
				switch (select) {
				case finishModification:	//modification is finished, set the flag true, get out of the while loop
					modificationDoneFlag = true;
					break;
				case accountPIN:				//modify this account's PIN
					ptr->setAccountPIN(strParser(lenAccountPIN, "AccountPIN"));
					break;
				case accountName:			//modify this account's name
					ptr->setAccountName(strParser(lenAccountName, "AccountName"));
					break;
				case accountGender:		//modify this account's gender
					ptr->setAccountGender(strParser(lenAccountGender, "AccountGender"));
					break;
				case accountRegion:		//modify this account's region
					ptr->setAccountRegion(strParser(lenAccountRegion, "AccountRegion"));
					break;
				case accountPrefernce:	//modify this account's preference
					ptr->setAccountPreference(strParser(lenAccountPreference, "AccountPreference"));
					break;
				default:
					break;
				}
				cout << "Account attribute modified successfully!" << endl;
			}
			cout << "Account modified successfully:" << endl;
			showAccount(*ptr);			//show the new account
		}
	}
	if (!accountFoundFlag) {		//if the ID is not found
			cout << "Sorry, cannot find the account \"" << accountID << "\" for modification." << endl;
	}
	}
}

//add new dish function
void addNewDish(vector<Dish>& dishList) {//dishLsit for Browse
										 //Add new data
	bool alreadyRegisteredFlag = false;
	bool strLengthFitFlag = true;
	string dishID;
	string dishName;
	string dishDescription;
	int dishPrice = 0;
	//check the new dish ID
	do {
		strLengthFitFlag = true;
		if (alreadyRegisteredFlag)
			cout << "Sorry, this ID is currently occuyied by another Dish.";
		cout << "Enter dish ID: ";
		getline(cin, dishID);
		alreadyRegisteredFlag = false;
		for (auto & x : dishList) {
			if (!(dishID.compare(x.getDishID()))) //if ID is not repeatd, it is feasible
				alreadyRegisteredFlag = true;
		}
		if (dishID.size() > lenDishID)		//check the length
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, dish ID length cannot exceed " << lenDishID << " characters";
	} while (alreadyRegisteredFlag || (!strLengthFitFlag));
	//while the ID is feasible and the length is fit, get out of the loop

	//check the new dish name
	do {
		
		strLengthFitFlag = true;
		if (alreadyRegisteredFlag)
			cout << "Sorry, this dish Name is currently by another Dish.";
		cout << "Enter the Dish name: ";
		getline(cin, dishName);
		alreadyRegisteredFlag = false;
		for (auto & x : dishList) {
			if (!(dishName.compare(x.getDishName()))) //if ID not repeatd set flag false
				alreadyRegisteredFlag = true;
				
		}
		if (dishName.size() > lenDishName)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, Dish name length cannot exceed " << lenDishName << " characters";
	} while (alreadyRegisteredFlag || (!strLengthFitFlag));

	//set the description of the new dish 
	dishDescription = strParser(lenMaterialDescrption, "DishDescription");

	//set the price of the new dish 
	do {
		if (dishPrice < 0) {
			cout << "Dish price can not be negative!";
		}
		cout << "Please Enter dish price£º";
		dishPrice = intParser();

	} while (dishPrice < 0);

	//call constructor of the class Dish, declare an objective temp to record the data of the new dish
	Dish temp = Dish(dishID, dishName, dishDescription, dishPrice);

	//write the data of the new dish as an element to the end of the vector
	dishList.push_back(temp);

}

//show total dishes
void showDishMenuList(vector<Dish>& dishList) {
	cout << "#############################################################################################################" << endl;
	if (dishList.size() == 0)
		cout << "Sorry, the menu is currently empty." << endl;
	for (auto &x : dishList) {
		showDish(x);
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "#############################################################################################################" << endl;
}

//delete dish function
void eraseDish(vector<Dish>& dishList) {
	string dishID;
	bool dishFoundFlag = false;
	char ch;
	showDishMenuList(dishList);		//show the dish list
	cout << "Please Enter the Account ID you want to delete: " << endl;
	getline(cin, dishID);		//get the dish ID which is going to be de deleted
	vector<Dish>::iterator ptr;
	for (ptr = dishList.begin(); ptr != dishList.end(); ptr++) {
		if (!(dishID.compare(ptr->getDishID()))) { //if same ID found
			dishFoundFlag = true;
			cout << "Dish found:" << endl;
			cout << "Are you sure to delete the Dish from menu? (Y/N)" << endl;
			ch = charParser();
			if (ch == 'Y' || ch == 'y') {		//Be sure to delete, then use erase( ) to delete
				dishList.erase(ptr, (ptr + 1));
				ptr = dishList.begin();
				cout << "Dish deleted from menu successfully!" << endl;
			}
			else      	//Not sure to delete
				cout << "Dish deletion quitted";
		}
	}
	if (!dishFoundFlag) {		//if the ID is not found
		cout << "Sorry, cannot find appointed Dish in the menu." << endl;
	}
}

//modify dish function
void modifyDish(vector<Dish>& dishList) {
	string dishID;
	string temp;
	bool dishFoundFlag = false;
	bool repeatedFLAG = false;
	showDishMenuList(dishList);			//show the dish list
	if (dishList.size() > 0) {
		cout << "Please Enter the dish ID you want to modify: " << endl;
		getline(cin, dishID);		//get the dish ID which is going to be de modified
		vector<Dish>::iterator ptr;
		for (ptr = dishList.begin(); ptr != dishList.end(); ptr++) {
			if (!(dishID.compare(ptr->getDishID()))) { //if same ID found
				dishFoundFlag = true;
				cout << "Dish found..." << endl;
				enum { finishModification, dishID, dishName, dishDescription, dishPrice };
				int select;
				bool modificationDoneFlag = false;
				while (modificationDoneFlag != true) { //strats to modify
					cout << "Please give command to modify:" << endl;
					cout << "0 = Fnish Modification, 1 = DishID, 2=DishName, 3=DishDescription 4=DishPrice" << endl;
					select = intParser();		//get the choice
					switch (select) {
					case finishModification:	//modification is finished, set the flag true, get out of the while loop
						modificationDoneFlag = true;
						break;
					case  dishID:					//modify this dish's ID
						temp = strParser(lenDishID, "DishID");
						for (auto & x : dishList) {
							if (!(temp.compare(x.getDishID()))) //if ID is repeatd set flag true
								repeatedFLAG = true;
						}
						if (!repeatedFLAG)
							ptr->setDishID(temp);
						else
							cout << "Sorry, this ID has been occupied by another Dish" << endl;
						break;

					case dishName:		//modify this dish's name
						temp = strParser(lenDishName, "DishName");
						for (auto & x : dishList) {
							if (!(temp.compare(x.getDishID()))) //if ID not repeatd set flag false
								repeatedFLAG = true;
						}
						if (!repeatedFLAG)
							ptr->setDishName(temp);
						else
							cout << "Sorry, this ID has been occupied by another Dish" << endl;
						break;

					case dishDescription: 			//modify this dish's description
						temp = strParser(lenDishDescription, "DishDescription");
						ptr->setDishDescription(temp);
						break;

					case dishPrice:			//modify this dish's price
						cout << "Please reset the DISH's price: ";
						ptr->setDishPrice(intParser());
						break;
					default:
						break;
					}
					cout << "Dish attribute modified successfully!" << endl;
				}
				cout << "Dish modified successfully:" << endl;
				showDish(*ptr);		//show the new dish
			}
			
		}
		if (!dishFoundFlag) {				//if the ID is not found
				cout << "Sorry, cannot find the Dish \"" << dishID << "\"for modification." << endl;
			}
	}
}

//add new raw material function
void addRawMaterial(vector<RawMaterial>& rawMaterialList) {
	//Add new data
	bool alreadyRegisteredFlag = false;
	bool strLengthFitFlag = true;
	string materialID;
	string materialName;
	int materialAmount = 0;	//account Debts
	string materialUnit = "kg";		//a string variable to recordmaterial weight's unit
	int materialPricePerUnit = 0;		//an int variable to record the price of material per unit
	string materialDescription = "N/A";	//account preference of dishes
	do {
		strLengthFitFlag = true;
		if (alreadyRegisteredFlag)
			cout << "Sorry, this ID has been registered by another Material.";
		cout << "Enter raw material ID: ";
		getline(cin, materialID);		//get new material ID
		for (auto & x : rawMaterialList) {
			if (!(materialID.compare(x.getMaterialID()))) //if ID is not repeatd,  it is feasible
				alreadyRegisteredFlag = true;
		}
		if (materialID.size() > lenMaterialID)		//check the length
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, material ID length cannot exceed " << lenMaterialID << " characters";
	} while (alreadyRegisteredFlag || (!strLengthFitFlag));
	//while the ID is feasible and the length is fit, get out of the loop

	//set the name, description and unit of the new material
	materialName = strParser(lenMaterialName, "MaterialName");
	materialDescription = strParser(lenMaterialDescrption, "MaterialDescription");
	materialUnit = strParser(lenMaterialUnit, "MaterialUnit");
	
	//set the price per unit and amount of the material, and they are not allowed to be less than 0
	do {
		if (materialPricePerUnit < 0) {
			cout << "Raw Material price per unit can not be negative!";
		}
		cout << "Please Enter Raw Material price per unit£º";
		materialPricePerUnit = intParser();

	} while (materialPricePerUnit < 0);

	do {
		if (materialAmount < 0) {
			cout << "Raw material amount can not be negative!";
		}
		cout << "Please Enter material amount£º";
		materialAmount = intParser();

	} while (materialAmount < 0);

	//call constructor of the class RawMaterial, declare an objective temp to record the data of the new material
	RawMaterial temp = RawMaterial(materialID, materialName, materialAmount, materialUnit, materialPricePerUnit, materialDescription);

	//write the data of the new material as an element to the end of the vector
	rawMaterialList.push_back(temp);
}

//show raw material list
void showRawMaterialList(vector<RawMaterial>& rawMaterialList){
	cout << "#############################################################################################################" << endl;
	if (rawMaterialList.size() == 0)
		cout << "The inventory is currently empty." << endl;
	for (auto &x : rawMaterialList) {
		x.showMaterialInfo();
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "#############################################################################################################" << endl;
}

//delete raw material function
void eraseRawMaterial(vector<RawMaterial>& rawMaterialList) {
	string materialID;
	bool materialFoundFlag = false;
	char ch;
	showRawMaterialList(rawMaterialList);		//show the account list
	cout << "Please Enter the raw material ID you want to delete: " << endl;
	getline(cin, materialID);	//get the material ID which is going to be de deleted
	vector<RawMaterial>::iterator ptr;
	for (ptr = rawMaterialList.begin(); ptr != rawMaterialList.end(); ptr++) {
		if (!(materialID.compare(ptr->getMaterialID()))) {	//if same ID found
			materialFoundFlag = true;
			cout << "Raw material found:" << endl;
			cout << "Are you sure to delete the Material from inventory? (Y/N)" << endl;
			ch = charParser();
			if (ch == 'Y' || ch == 'y') {		//Be sure to delete, then use erase( ) to delete
				rawMaterialList.erase(ptr, (ptr + 1));
				ptr = rawMaterialList.begin();
				cout << "Material deleted from intventory successfully!" << endl;
			}
			else		//Not sure to delete
				cout << "Material deletion quitted";
		}
	}
	if (!materialFoundFlag) {		// if ID is not found
		cout << "Sorry, cannot find appointed material in the inventory." << endl;
	}
}

//modify raw materials function
void modifyRawMaterial(vector<RawMaterial>& rawMaterialList) {
	string materialID;
	bool dishFoundFlag = false;
	showRawMaterialList(rawMaterialList);	//show the raw material list
	if (rawMaterialList.size() > 0) {
	cout << "Please Enter the dish ID you want to modify: " << endl;
	getline(cin, materialID);		//get the material ID which is going to be de modified
	vector<RawMaterial>::iterator ptr;
	for (ptr = rawMaterialList.begin(); ptr != rawMaterialList.end(); ptr++) {
		if (!(materialID.compare(ptr->getMaterialID()))) { //if same ID found
			dishFoundFlag = true;
			cout << "Material found..." << endl;
			enum { finishModification, materialID, materialName, materialUnit, materialPricePerUnit, materialAmount, materialDescription
			};
			int select;
			bool modificationDoneFlag = false;
			bool repeatedFLAG = false;
			string id;
			while (modificationDoneFlag != true) { //strats to modify
				cout << "Please give command to modify:" << endl;
				cout << "0 = Fnish Modification, 1 = MaterialID, 2=MaterialName, 3=MaterialUnit, 4=MaterialPricePerUnit, 5=MaterialAmount, 6=MaterialDescription" << endl;
		
				select = intParser();		//get the choice
				switch (select) {
				case finishModification:		//modification is finished, set the flag true, get out of the while loop
					modificationDoneFlag = true;
					break;
				case  materialID:			//modify this material's ID
					id = strParser(lenMaterialID, "MaterialID");
					for (auto & x : rawMaterialList) {
						if (!(id.compare(x.getMaterialID()))) //if ID is not repeated, it is feasible
							repeatedFLAG = true;
					}
					if (!repeatedFLAG)
						ptr->setMaterialID(id);
					else
						cout << "Sorry, this ID has been occupied by another raw material" << endl;
					break;
				case materialName:			//modify this material's name
					ptr->setMaterialName(strParser(lenMaterialName, "MaterialName"));
					break;
				case materialUnit:			//modify this material's unit
					ptr->setMaterialUnit(strParser(lenMaterialUnit, "MaterialUnit"));
					break;
				case materialPricePerUnit:	//modify this material's price per unit
					cout << "Please reset the Material's price per unit: ";
					ptr->setMaterialAmount(intParser());
					break;
				case materialAmount:			//modify this material's amount
					cout << "Please reset the Material's amount: ";
					ptr->setMaterialAmount(intParser());
					break;
				case materialDescription:	//modify this material's description
					ptr->setMaterialDescrption(strParser(lenMaterialDescrption, "MaterialDescription"));
					break;
				default:
					break;
				}
				cout << "Material attribute modified successfully!" << endl;
			}
			cout << "Material modified successfully:" << endl;
			ptr->showMaterialInfo();		//show the new material

		}
		
	}
	if (!dishFoundFlag) {		//if the ID is not found
			cout << "Sorry, cannot find the Dish \"" << materialID << "\"for modification." << endl;
		}
	}
}

//No parameter to limit, return value is an integer inputted by user
int intParser() {
	int temp;
	bool isErr = true;
	//while (input failed) or (input succeeded with redundant tail, clear steream and repeat)
	while ((isErr = !(cin >> temp)) || (!isErr && cin.get() != '\n')) {
		if (isErr) { cin.clear(); }
		//reset cin
		while (cin.get() != '\n')//clear a whole line
			continue;
		cout << "\t\tPlease enter an integer: ";
	}
	return temp;
}

//the length is limitted, and the name is given, return value is a string inputted by user
string strParser(int lenLimit, string name) {
	string temp = "";
	bool strLengthFitFlag = true;
	do {
		strLengthFitFlag = true;
		cout << "Enter the " << name << ":";//(enter a blank line to quit)
		getline(cin, temp);
		if (temp.size() > (unsigned)lenLimit)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, " << name << " length cannot exceed " << lenLimit << " characters";
	} while ((!strLengthFitFlag));
	return temp;
}
