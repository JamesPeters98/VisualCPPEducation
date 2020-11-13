// Chapter8-Question2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class String
{
private:
	char* string;
	int len;

public:
	String(const char* data = "Default string");
	String(const String& str);
	~String();

	String& operator=(const String& str);
	
	void print();
	int length();

	
};

String::~String()
{
	delete[] string;
}


String::String(const char* data)
{
	len = strlen(data);
	string = new char[len + 1];
	strncpy_s(string, len + 1, data, len + 1);
}

String::String(const String& str)
{
	len = str.len;
	string = new char[len + 1];
	strcpy_s(string, len + 1, str.string);
}

String& String::operator=(const String& str)
{
	len = str.len;
	delete string;
	string = new char[len + 1];
	strcpy_s(string, len + 1, str.string);

	return *this;
}

void String::print()
{
	std::cout << string << std::endl;
}

int String::length()
{
	return len;
}



int main()
{
	String str{ "Hello world!" };
	str.print();

	String str2{ "Test String!" };
	str2.print();
	
}

