#define _CRT_SECURE_NO_WARNINGS
#include "String.h"

void String::copyDatas(const String& other, const char* data, size_t capacity)
{
    this->mCapacity = other.mCapacity;
    char* result = new char[capacity + 1];
    this->mData = strcpy(result, data);
}

void String::erase()
{
    delete[] this->mData;
}

void String::resize(size_t capacity)
{
    char* temp = this->mData;
    this->mData = new char[capacity + 1];
    strcpy_s(this->mData,sizeof(this->mData), temp);
    delete[] temp;
}

String::String()
{
    mCapacity = CAPACITY_MIN;
    this->mData = new char[mCapacity + 1];
    this->mData[0] = 0;
}

String::String(const char* data)
{
    mCapacity = CAPACITY_MIN;
    size_t stringSize = strlen(data);
    while ((mCapacity * 3) / 4 < stringSize)
    {
        mCapacity *= 2;
    }
    char* dynCopy = new char[mCapacity + 1];
    this->mData = strcpy(dynCopy, data);
}

String::String(const String& other)
{
    copyDatas(other, mData, mCapacity);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        erase();
        copyDatas(other, mData, mCapacity);
    }
    return *this;
}

String::~String()
{
    erase();
}

size_t String::getLength() const
{
    return strlen(this->mData);
}

size_t String::getCapacity() const
{
    return this->mCapacity;
}

String& String::append(const String& other)
{
    return this->append(other.mData);
}

void String::pushBack(char symbol)
{
    if ((this->mCapacity * 3) / 4 < this->getLength() + 1)
    {
        mCapacity *= 2;
        this->resize(mCapacity);
    }

    size_t oldSize = this->getLength();
    this->mData[oldSize] = symbol;
    this->mData[oldSize + 1] = 0;
}

bool String::isEmpty() const
{
    return this->getLength() == 0;
}

String& String::append(const char* other)
{
    bool isDirty = false;
    while ((this->mCapacity * 3) / 4 < strlen(other) + this->getLength())
    {
        isDirty = true;
        this->mCapacity *= 2;
    }
    if (isDirty)
    {
        resize(this->mCapacity);
    }
    strcat(this->mData, other);
    return *this;
}

String& String::operator+(const String& other) const
{
    String* outcome= new String(*this);
    return outcome->append(other);
}

String& String::operator+=(const String& other)
{
    return this->append(other);
}

char String::operator[](size_t index) const
{
    if (index < this->getLength())
    {
        return this->mData[index];
    }
}

char& String::operator[](size_t index)
{
    if (index < this->getLength())
    {
        return this->mData[index];
    } 
}

bool String::operator==(const String& other) const
{
    return this->mCapacity == other.mCapacity && strcmp(this->mData, other.mData) == 0;
}
bool String::operator!=(const String& other) const
{
    return !(*this == other);
}


std::ostream& operator<<(std::ostream& out, const String& str)
{
    out<<str.getLength()<< ' ' <<str.mData;
    return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
    std::cout << str.mData;
    in >> str.mData;
    std::cout << str.mCapacity;
    in >> str.mCapacity;
    return in;
}
