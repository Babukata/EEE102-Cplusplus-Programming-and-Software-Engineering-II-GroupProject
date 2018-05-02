#pragma once
#ifndef _DISH
#define _DISH

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum dishInfoLimit { lenDishID = 12, lenDishName = 20, lenDishDescription = 24 };

class Dish {
	friend void showDish(const Dish& d);
private:
	string dishID;
	string dishName;
	string dishDespcription;
	int dishPrice;
	
public:
	Dish();
	Dish(string id, string name, string description, int price);
	string getDishID()const;
	string getDishName()const;
	string getDishDescription()const;
	int getDishPrice()const;
	void setDishID(const string& s);
	void setDishName(const string& s);	//edit dish name in menu
	void setDishDescription(const string& s);
	void setDishPrice(int price);	//edit dish price in menu
};


#endif