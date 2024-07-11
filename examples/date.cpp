#include "date.hpp"

Date::Date()
{
    day = 1;
    month = 1;
    year = 1;
}


Date::Date(int d , int m , int y)
{
    day = d;
    month = m;
    year = y;
}


Date::~Date() {}

void Date::Print()
{
    std::ostringstream S;
    std::cout << year << DATE_SEPRATOR << month << DATE_SEPRATOR << day;
} 

bool Date::is_Equal_Date(Date *date)
{
    if(date->day == day && date->month == month && date->year == year)
        return true;
    return false;
}


std::string Date::get_Date()
{
    std::ostringstream S;
    S << year << DATE_SEPRATOR << month << DATE_SEPRATOR << day;
    return S.str();
}