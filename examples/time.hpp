#ifndef TIME
#define TIME

#include <iostream>
#include <sstream>

enum Week 
{
    Saturday,Sunday,Monday,Tuesday,Wednesday
};

const char DAY_TIME_SEPRATOR = ':';
const char START_END_SEPRATOR = '-';

class Time
{
public:
    Time();
    Time(Week day_of_week , int s , int e);
    ~Time();
    bool is_Interrupt_Time(Week day_of_week , int start_time , int end_time);
    int get_Start();
    int get_End();
    std::string get_Time();
    Week get_Day();

private:
    int start;
    int end;
    Week day;
    std::string Day_To_String(Week day);

};

#endif