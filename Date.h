#ifndef	_DATE_H
#define _DATE_H


class Date
{
private:
    int day;
    int month;
    int year;

    bool isLeapYear(unsigned short year);
    bool isValid(unsigned short day, unsigned short month, unsigned short year);
    void setDefaultValues();

public:
    Date();
    Date(int day, int month, int year);

    void print() const;

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool setDay(int day);
    bool setMonth(int month);
    bool setYear(int year);
    
    short compareDates(const Date& date);


};

#endif