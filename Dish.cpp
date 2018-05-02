#include "Dish.h"

Dish::Dish() {
	dishName = "N/A";
	dishPrice = 0;
}
Dish::Dish(string id, string name, string description, int price) {
	dishID = id;
	dishName = name;
	dishDespcription = description;
	dishPrice = price;
}
string Dish::getDishID()const {
	return dishID;
}
string Dish::getDishName()const {
	return dishName;
}
string Dish::getDishDescription()const {
	return dishDespcription;
}
int Dish::getDishPrice()const {
	return dishPrice;
}
void Dish::setDishID(const string& s) {
	dishID = s;
}
void Dish::setDishName(const string& s) {
	dishName = s;
}
void Dish::setDishDescription(const string& s) {
	dishDespcription = s;
}
void Dish::setDishPrice(int price) {
	dishPrice = price;
}
void showDish(const Dish& d) {

	cout << "# Dish " << setw(lenDishID+2) << d.dishID << " # Name " << setw(lenDishName+2) << d.dishName << " # price " << setw(6+1) << d.dishPrice <<" # Desctiption " << setw(lenDishDescription+1) << d.dishDespcription<< " #" << endl;

}