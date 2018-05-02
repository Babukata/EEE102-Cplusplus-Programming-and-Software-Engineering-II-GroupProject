#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
enum rawMaterialInfoLimit { lenMaterialID = 12, lenMaterialName = 12, lenMaterialUnit = 6, lenMaterialDescrption = 29 };
class RawMaterial {
private:
	string materialID;		//use phone number as ID
	string materialName;		//account's name
	int materialAmount = 0;	//account Debts
	string materialUnit = "kg";
	int materialPricePerUnit = 0;
	int materialTotalPrice;
	string materialDescription = "N/A";	//account preference of dishes
	
public:
	RawMaterial();
	RawMaterial(string id, string name, int amount = 0, string unit ="kg", int unitPrice = 0, string description = "N/A");	//Construct RawMaterial object BY creating
	~RawMaterial();
	string getMaterialID()const;
	string getMaterialName()const;
	int getMaterialAmount()const;
	string getMaterialUnit()const;
	int getMaterialPricePerUnit()const;
	int getMaterialTotalPrice()const;
	string getMaterialDescrption()const;

	void setMaterialID(const string& s);
	void setMaterialName(const string& s);
	void setMaterialAmount(int x);
	void setMaterialUnit(const string& s);
	void setMaterialPricePerUnit(int x);
	void setMaterialTotalPrice(int x);
	void setMaterialDescrption(const string& s);
	void showMaterialInfo();
	
};