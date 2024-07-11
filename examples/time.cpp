#include "time.hpp"

Time::Time()
{
    start = -1;
    end = -1;
}


Time::Time(Week day_of_week , int s , int e)
{
    start = s;
    end = e;
    day = day_of_week;
}

Time::~Time() {}

bool Time::is_Interrupt_Time(Week day_of_week , int start_time , int end_time)
{
    if(day == day_of_week)
    {
        if(!(start_time >= end || end_time <= start))
            return true;
        return false;
    }
    else
        return false;
}


std::string Time::get_Time()
{
    std::ostringstream S;
    S << Day_To_String(day) << DAY_TIME_SEPRATOR << start << START_END_SEPRATOR << end;
    return S.str();
}

Week Time::get_Day()
{
    return day;
}
int Time::get_Start()
{
    return start;
}
int Time::get_End()
{
    return end;
}

std::string Time::Day_To_String(Week day)
{
    if(day == Saturday)
        return "Saturday";
    else if(day == Sunday)
        return "Sunday";
    else if(day == Monday)
        return "Monday";
    else if(day == Tuesday)
        return "Tuesday";
    else if(day == Wednesday)
        return "Wednesday";   
    return "";
}