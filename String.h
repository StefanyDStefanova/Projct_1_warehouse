#ifndef _STRING_H
#define _STRING_H
#define CAPACITY_MIN 10
#include <iostream>

class String
{
public:
	String();
	String(const char* data);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	size_t length() const;
	size_t capacity() const;

	String& append(const char*);
	void pushBack(char c);
	bool isEmpty() const;

	String& operator+(const String&)const;
	bool operator!=(const String&) const;
	bool operator==(const String&) const;

	void erase();
	
	friend std::ostream& operator<<(std::ostream& out, const String& str);

private:
	char* mData{ nullptr };
	size_t mCapacity;
	void resize(size_t capacity);
};

#endif 