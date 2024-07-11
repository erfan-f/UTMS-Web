#ifndef DATE
#define DATE

#include "iostream"
#include "sstream"



const char DATE_SEPRATOR = '/';

class Date
{
public:
    Date();
    Date(int d , int m , int y);
    ~Date();
    void Print();
    bool is_Equal_Date(Date* date);
    std::string get_Date();

private:
    int day;
    int month;
    int year;

};

#endif