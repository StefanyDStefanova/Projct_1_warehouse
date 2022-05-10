#ifndef	_PRODUCT_H
#define _PRODUCT_H

#include <iostream>
#include "String.h"
#include"Date.h"
class Product 
{
private:
    String name;
    //формат: гггг-мм-дд
    String expirationDate;
    String entranceDate;
    //Date expirationDate;
    //Date entranceDate;
    String producer;
    String unit;
    double quantity;
    //формат: секция/рафт/номер
    String location;
    String comment;

public:
    Product()=default;
    Product(String nName, String nExpirationDate, String nEntranceDate, String nProducer,
        String nUnit, double nQuantity, String nLocation, String nComment);
    Product(const Product& other);
    Product& operator= (const Product& other);
    ~Product()=default;

    void copyDatas(const Product& other);
    bool isEmptyData(String data);

    String getName() const;
    String getExpirationDate() const;
    String getEntranceDate() const;
    String getProducer() const;
    String getUnit() const;
    double getQuantity() const;
    String getLocation() const;
    String getComment() const;

    void setName(String nName);
    void setExpirationDate(String nExpirationDate);
    void setEntranceDate(String nEntranceDate);
    void setProducer(String nProducer);
    void setUnit(String nUnit);
    void setQuantity(double nQuantity);
    void setLocation(String nLocation);
    void setComment(String nComment);

    friend std::ostream& operator<< (std::ostream& out, const Product& product);
    friend std::istream& operator>> (std::istream& in, Product& product);

    //методи за обработка на срока на годност
    int getExpirationYear(const Product& product);
    int getExpirationMonth(const Product& product);
    int getExpirationDay(const Product& product);
    bool isExpiring(const Product& product);

    //методи за обработка на местоположението
    int getSection(const Product& product);
    int getShelf(const Product& product);
    int getNumber(const Product& product);
    String newLocation(const Product& product);
};


#endif