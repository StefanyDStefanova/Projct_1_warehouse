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

	size_t get_length() const;
	size_t get_capacity() const;

	String& append(const String& other);
	void pushBack(char c);
	bool isEmpty() const;
	String& append(const char* other);

	String& operator+(const String& other)const;
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;

	void copyDatas(const String&, const char* data, size_t capacity);
	void erase();
	
	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::istream& operator>>(std::istream& in, String& str);

	

private:
	char* mData{ nullptr };
	size_t mCapacity;
	void resize(size_t capacity);
};

#endif 