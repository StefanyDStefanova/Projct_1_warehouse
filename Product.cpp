#ifndef _PRODUCT_CPP
#define _PRODUCT_CPP

#include "Product.h"
#include "Date.h"

#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <string>
#include <sstream>


void Product::copyDatas(const Product& other)
{
    name = other.name;
    expirationDate = other.expirationDate;
    entranceDate = other.entranceDate;
    producer = other.producer;
    unit = other.unit;
    quantity = other.quantity;
    location = other.location;
    comment = other.comment;
}

Product::Product(String nName, String nExpirationDate, String nEntranceDate, String nProducer,
    String nUnit, double nQuantity, String nLocation, String nComment)
{
    setName(nName);
    setExpirationDate(nExpirationDate);
    setEntranceDate(nEntranceDate);
    setProducer(nProducer);
    setUnit(nUnit);
    setQuantity(nQuantity);
    setLocation(nLocation);
    setComment(nComment);
}

Product::Product(const Product& other) 
{
    copyDatas(other);
}

Product& Product:: operator= (const Product& other) 
{
    if (this != &other)
    {
        copyDatas(other);
    }
}

String Product::getName() const
{
    return name; 
}
String Product::getExpirationDate() const 
{
    return expirationDate;
}
String Product::getEntranceDate() const 
{
    return entranceDate; 
}
String Product::getProducer() const 
{
    return producer; 
}
String Product::getUnit() const 
{
    return unit; 
}
double Product::getQuantity() const 
{
    return quantity;
}
String Product::getLocation() const
{
    return location; 
}
String Product::getComment() const 
{
    return comment; 
}

bool Product::isEmptyData(String data)
{
    return data.isEmpty();
}

void Product::setName(String nName) 
{
    if (isEmptyData(nName))
    {
        name = nName;
    }
}

void Product::setExpirationDate(String nExpirationDate) 
{
    if (isEmptyData(nExpirationDate))
    {
        expirationDate = nExpirationDate;
    }
}

void Product::setEntranceDate(String nEntranceDate)
{
    if (isEmptyData(nEntranceDate))
    {
        entranceDate = nEntranceDate;
    }
}

void Product::setProducer(String newProducer) 
{
    if (isEmptyData(newProducer))
    {
        producer = newProducer;
    }
}

void Product::setUnit(String nUnit) 
{
    if (nUnit == "kg" || nUnit == "L") 
    {
        unit = nUnit;
    }  
}

void Product::setQuantity(double nQuantity) 
{
    quantity = nQuantity;
}

void Product::setLocation(String nLocation) 
{
    if (isEmptyData(nLocation))
    {
        location = nLocation;
    }
}

void Product::setComment(String nComment) 
{
    if (isEmptyData(nComment))
    {
        comment = nComment;
    }
}

std::ostream& operator<< (std::ostream& out, const Product& product) 
{
    out << "Name: " << product.name << std::endl;
    out << "Expiration date: " << product.expirationDate << std::endl;
    out << "Entrance date: " << product.entranceDate << std::endl;
    out << "Producer: " << product.producer << std::endl;
    out << "Unit: " << product.unit << std::endl;
    out << "Quantity: " << product.quantity << std::endl;
    out << "Location: " << product.location << std::endl;
    out << "Comment: " << product.comment << std::endl;
    return out;
}

std::istream& operator>> (std::istream& in, Product& product) 
{
    std::cout << "Name: ";
    in >> product.name;
    std::cout << "Expiration date: ";
    in >> product.expirationDate;
    std::cout << "Entrance date: ";
    in >> product.entranceDate;
    std::cout << "Producer: ";
    in >> product.producer;
    std::cout << "Unit: ";
    in >> product.unit;
    std::cout << "Quantity: ";
    in >> product.quantity;
    std::cout << "Comment: ";
    in >> product.comment;
    return in;
}

int getExpirationYear(const Product& product) 
{
    //връща годинат от срока на годност
    String curr = product.getExpirationDate();
    //String res;
    std::string res;
    unsigned i = 0;

    while (curr[i] != '-') 
    {
        res[i] = curr[i];
        i++;
    }

    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

int getExpirationMonth(const Product& product)
{
    //връща месеца от срока на годност
    String curr = product.getExpirationDate();
    //String res;
    std::string res;
    unsigned i = 0;

    while (curr[i] != '-') 
    {
        i++;
    }
    unsigned j = i + 2;
    i = 0;

    while (curr[j] != '-') 
    {
        res[i] = curr[j];
        i++; j++;
    }

    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

int getExpirationDay(const Product& product)
{
    //връща деня от срока на годност
    String curr = product.getExpirationDate();
    //String res;
    std::string res;
    unsigned i = 0;

    while (curr[i] != '-') 
    {
        i++;
    }
    i++;

    while (curr[i] != '-') 
    {
        i++;
    }
    unsigned j = 0;

    while (i < curr.getLength())
    {
        res[j] = curr[i + 1];
        i++; j++;
    }

    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

bool isExpiring(const Product& product)
{
    //проверява дали дадена стока е с изтекъл или изтичащ срок на годност
    //приемаме, че срок на годност е изтичащ, ако изтича след по-малко от 4 дни
    int expDay = getExpirationDay(product);
    int expMonth = getExpirationMonth(product);
    int expYear = getExpirationYear(product);

    time_t theTime = time(NULL);
    struct tm* aTime = localtime(&theTime);
    int currDay = aTime->tm_mday;
    int currMonth = aTime->tm_mon + 1;
    int currYear = aTime->tm_year + 1900;

    if (expYear < currYear) 
    { 
        return true; 
    }
    else if (expYear == currYear) 
    {
        if (expMonth < currMonth) 
        { 
            return true; 
        }
        else if (expMonth == currMonth) 
        {
            if (expDay <= currDay || expDay - currDay < 3)
            {
                return true;
            }
            else if (expDay - currDay > 3)
            { 
                return false; 
            }
        }
        else if (expMonth - currMonth == 1)
        {
            if (currMonth == 2)
            {
                return ((expDay == 1 && currDay == 26) || (expDay <= 2 && currDay == 27)
                    || (expDay <= 3 && currDay == 28) || (expDay <= 4 && currDay == 29));
            }
            else if (currMonth == 1 || currMonth == 3 || currMonth == 5 || currMonth == 7 ||
                currMonth == 8 || currMonth == 10 || currMonth == 12) 
            {
                return ((expDay == 1 && currDay == 29) || (expDay <= 2 && currDay == 30) || (expDay <= 3 && currDay == 31));    
            }
            else if (currMonth == 4 || currMonth == 6 || currMonth == 9 || currMonth == 11)
            {
                return  ((expDay == 1 && currDay == 28) || (expDay <= 2 && currDay == 29) || (expDay <= 3 && currDay == 30));  
            }
        }
        else if (expMonth - currMonth > 1)
        { 
            return false; 
        }
    }
    else if (expYear - currYear == 1) 
    {
        if (currMonth == 12 && expMonth == 1) 
        {
                return ((expDay == 1 && currDay == 29) || (expDay <= 2 && currDay == 30) || (expDay <= 3 && currDay == 31));
        }
        else return false;
    }
    else if (expYear - currYear > 1) 
    { 
        return false; 
    }
}

int getSection(const Product& product) {
    //връща номера на секцията от местоположението на продукта
    String location = product.getLocation();
    //String res;
    std::string res;
    unsigned i = 0;

    while (location[i] != '/') 
    {
        res[i] = location[i];
        i++;
    }
    
    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

int getShelf(const Product& product) {
    //връща номера на рафта от местоположението на продукта
    String location = product.getLocation();
    //String res;
    std::string res;
    unsigned i = 0;

    while (location[i] != '/') 
    {
        i++;
    }
    unsigned j = i + 1;
    i = 0;

    while (location[j] != '/') 
    {
        res[i] = location[j];
        i++; 
        j++;
    }
    
    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

int getNumber(const Product& product) {
    //връща номера от местоположението на продукта
    String location = product.getLocation();
    //String res;
    std::string res;
    unsigned i = 0;

    while (location[i] != '/') 
    {
        i++;
    }
    i++;

    while (location[i] != '/') 
    {
        i++;
    }
    unsigned j = 0;

    while (i < location.getLength()) 
    {
        res[j] = location[i + 1];
        i++; j++;
    }
    
    std::stringstream container(res);
    int x;
    container >> x;
    return x;
}

String nLocation(const Product& product) 
{
    //създава нова локация от текущата
    String location = product.getLocation();
    int section = getSection(product);
    int shelf = getShelf(product);
    int number = getNumber(product);
    String res;

    if (number >= 100) 
    {
        shelf++;
        number = 1;
        if (shelf > 50) 
        {
            section++;
            shelf = 1;
        }
    }
    else number++;

    String curr = reinterpret_cast<char*>(section);
    res = curr;
    res += "/";

    curr = reinterpret_cast<char*>(shelf);
    res += curr;
    res += "/";

    curr = reinterpret_cast<char*>(number);
    res += curr;
    res += '\0';

    return res;
}

#endif