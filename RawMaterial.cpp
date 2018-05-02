#include "RawMaterial.h"
RawMaterial::RawMaterial(string id, string name, int amount, string unit, int unitPrice, string description){
	materialID = id;		//use phone number as ID
	materialName = name;		//account's name
	materialAmount = amount;	//account Debts
	materialUnit = unit;
	materialPricePerUnit = unitPrice;
	materialTotalPrice = materialAmount*materialPricePerUnit;
	materialDescription = description;	//account preference of dishes
}
RawMaterial::~RawMaterial() {
}
string RawMaterial::getMaterialID()const {
	return materialID;
}
string RawMaterial::getMaterialName()const {
	return materialName;
}
int RawMaterial::getMaterialAmount()const {
	return materialAmount;
}
string RawMaterial::getMaterialUnit()const {
	return materialUnit;
}
int RawMaterial::getMaterialPricePerUnit()const {
	return materialPricePerUnit;
}
int RawMaterial::getMaterialTotalPrice()const {
	return materialTotalPrice;
}
string RawMaterial::getMaterialDescrption()const {
	return materialDescription;
}

void RawMaterial::setMaterialID(const string& s) {
	materialID = s;
}
void RawMaterial::setMaterialName(const string& s) {
	materialName = s;
}
void RawMaterial::setMaterialAmount(int x) {
	materialAmount = x;
}
void RawMaterial::setMaterialUnit(const string& s) {
	materialUnit = s;
}
void RawMaterial::setMaterialPricePerUnit(int x) {
	materialPricePerUnit = x;
}
void RawMaterial::setMaterialTotalPrice(int x) {
	materialTotalPrice = x;
}
void RawMaterial::setMaterialDescrption(const string& s) {
	materialDescription = s;
}

void RawMaterial::showMaterialInfo() {
	cout << "# MaterialID " << setw(lenMaterialID) << materialID << " # MaterialName" << setw(lenMaterialName) << materialName << " # Amount " << setw(10) << materialAmount << setw(lenMaterialUnit) << materialUnit << " #" << endl;
	cout << "# TotalCost " << setw(13) << materialTotalPrice << " # Description " << setw(lenMaterialDescrption+9) << materialDescription << " #" << endl;
}
