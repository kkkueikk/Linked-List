#include <iostream>
#include "Date.h"

using namespace std;

//Constructor
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

//Print Data object in this format
void Date::print(ostream& out)
{
	out << day << "/" << month << "/" << year;

}