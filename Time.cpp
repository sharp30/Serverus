#include "Time.h"

Time::Time(int year, int month, int day, int hour, int minute, int second, int miliSec)
{
    this->_year = year;
    this->_month = month;
    this->_day = day;
    this->_hour = hour;
    this->_minute = minute;
    this->_second = second;
    this->_miliSec = miliSec;
}
/*
This function returns the difference between 2 time stamps in milliseconds()
Input: other - the other timeStamp : Time
Output: differece in millisecond : int
*/
int Time::operator-(const Time other) const
{
    int diff = 0;
    diff += this->_miliSec - other._miliSec;
    diff += (this->_second - other._second)*1000;
    diff += (this->_minute - other._second) * 1000 * 60;
    diff += (this->_hour - other.) * 1000 * 60 * 60;
    diff += (this->daysSinceYearStart() - other.daysSinceYearStart()) * 1000 * 60 * 60 * 24;
    diff += (this->_year - other._year) * 1000 * 60 * 60 * 24 * 365;


}
/*
This function returns the amount days since start of the year
Input:None
Output: Amount of years : int
*/
int Time::daysSinceYearStart()
{
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (!(this->_year % 4))
        days[1]++; //February +1
    int sum = 0;
    for (int i = 0; i < this->_month - 1; i++)
    {
        sum += days[i];
    }

    return sum + this->_day;
}


void Time::setYear(int year) { this->_year = year; } 
int Time::getYear() const { return this->_year; }
void Time::setMonth(int month) { this->_month = month; } 
int Time::getMonth() const { return this->_month; }
void Time::setDay(int day) { this->_day = day; } 
int Time::getDay() const { return this->_day; }
void Time::setHour(int hour) { this->_hour = hour; } 
int Time::getHour() const { return this->_hour; }
void Time::setMinute(int minute) { this->_minute = minute; } 
int Time::getMinute() const{ return this->_minute; }
void Time::setSecond(int second) { this->_second = second; } 
int Time::getSecond() const { return this->_second; }
void Time::setMiliSec(int miliSec) { this->_miliSec = miliSec; } 
int Time::getMiliSec() const{ return this->_miliSec; }