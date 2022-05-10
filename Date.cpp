#include <iostream>
#include "Date.h"

bool Date::isLeapYear(unsigned short year)
{
    return ((year % 400) || ((year % 4 == 0) && (year % 100 != 0)));
}

bool Date::isValid(unsigned short day, unsigned short month, unsigned short year)
{

    if (month > 12 || day > 31)
        return 0;

    unsigned short validDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year)) {
        validDays[1]++;
    }

    if (day > validDays[month - 1])
        return 0;

    return 1;
}

void Date::setDefaultValues()
{
    day = 1;
    month = 1;
    year = 2000;
}

Date::Date()
{
    setDefaultValues();
}

Date::Date(int day, int month, int year)
{
    if (!isValid(day, month, year)) 
    {
        setDefaultValues();
    };
    this->day = day;
    this->month = month;
    this->year = year;
}

void Date::print() const
{
    std::cout << "Date: ";
    std::cout << year << '-' << month << '-' << day << std::endl;
}

int Date::getDay() const
{
    return day;
}
int Date::getMonth() const
{
    return month;
}
int Date::getYear() const
{
    return year;
}

bool Date::setDay(int day)
{
    if (!isValid(day, this->month, this->year))
        return 0;

    this->day = day;
    return 1;
}

bool Date::setMonth(int month)
{
    if (!isValid(this->day, month, this->year))
        return 0;

    this->month = month;
    return 1;
}

bool Date::setYear(int year)
{
    if (!isValid(this->day, this->month, year))
        return 0;

    this->year = year;
    return 1;
}

short Date::compareDates(const Date& date)
{
    if (year > date.year)
        return 1;
    else if (year == date.year)
    {
        if (month > date.month)
            return 1;
        else if (month == date.month) 
        {
           if (day > date.day)
                return 1;
            else if (day == date.day)
                return 0;
        }
    }

    return -1;

}
