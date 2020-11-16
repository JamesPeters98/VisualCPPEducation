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
	String(String&& str);
	~String();

	String& operator=(const String& str);
	String& operator=(String&& str);

	String& operator+=(const String& str);
	String& operator+=(const char* str);

	String operator+(const String& str);
	String operator+(const char* str);
	
	void print();
	int length();

	
};

String::~String()
{
	delete[] string;
}

String::String(String&& str)
{
	len = str.len;
	string = str.string;
	// Otherwise the string will be deleted by the deconstructor of str.
	str.string = nullptr;
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
	if (this != &str)
	{
		len = str.len;
		delete string;
		string = new char[len + 1];
		strcpy_s(string, len + 1, str.string);
	}

	return *this;
}

String& String::operator=(String&& str)
{
	len = str.len;
	string = str.string;
	str.string = nullptr;

	return *this;
}

String String::operator+(const String& str)
{
	size_t length = len + str.len + 1;
	char* tempStr{ new char[length] };

	strcpy_s(tempStr, length, string);
	strcat_s(tempStr, length, str.string);
	
	return String(tempStr);
}

String String::operator+(const char* str)
{
	return *this + String(str);
}

String& String::operator+=(const char* str)
{
	*this = *this + str;
	return *this;
}

String& String::operator+=(const String& str)
{
	*this = *this + str;
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

	String str3{ str + " " + str2 };
	str3.print();

	str3 += " Test!";
	str3 += " ";
	str3 += str;

	str3.print();
	
}

