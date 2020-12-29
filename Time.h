#pragma once

#include <string>
#include <iostream>

using std::string;

class Time{
    private: 
        int _year;
        int _month;
        int _day;
        int _hour;
        int _minute;
        int _second;
        int _miliSec;

    /*
    The Time class's c'tor
    #TODO: check time format comes from the data base
    */
    public:
        Time() = default;
        Time(int year, int month, int day, int hour, int minute, int second, int miliSec);
        Time(string time);

        string toString();

        //Set & Get
        void setYear(int year);
        int getYear();
        void setMonth(int month);
        int getMonth();
        void setDay(int day);
        int getDay();
        void setHour(int hour);
        int getHour();
        void setMinute(int minute);
        int getMinute();
        void setSecond(int second);
        int getSecond();
        void setMiliSec(int miliSec);
        int getMiliSec();
};

