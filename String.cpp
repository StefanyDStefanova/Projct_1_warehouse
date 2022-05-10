#include "String.h"

void String::erase()
{
    delete[] this->mData;
}

void String::resize(size_t capacity)
{
    char* temp = this->mData;
    this->mData = new char[capacity + 1];
    strcpy(this->mData, temp);
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
    mCapacity = other.mCapacity;
    char* dynCopy = new char[mCapacity + 1];
    this->mData = strcpy(dynCopy, other.mData);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        erase();
        this->mCapacity = other.mCapacity;
        char* dynCopy = new char[mCapacity + 1];
        this->mData = strcpy(dynCopy, other.mData);
    }
    return *this;
}

String::~String()
{
    erase();
}

size_t String::get_length() const
{
    return strlen(this->mData);
}

size_t String::get_capacity() const
{
    return this->mCapacity;
}


