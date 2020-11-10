// Chapter5-Question5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

char* read_string(const char* str)
{
	static char* string{};
	static size_t length{};
	
	static int currentPos{};
	static int startPos{};

	char* retStr;


	// The first time the string is passed store it in static memory
	if (str != nullptr)
	{
		delete string;
		length = strlen(str);
		string = new char[length + 1]; // +1 for null terminated byte.
		strcpy_s(string, length + 1, str);
		currentPos = 0;
		startPos = 0;
	}

	for (currentPos = startPos; (string[currentPos] != ' ' && string[currentPos] != '\0'); currentPos++);

	if(startPos != currentPos)
	{
		retStr = new char[currentPos - startPos + 2]; // +2 to account for null terminated byte and index starting from 0.
		size_t i{ 0 };

		while (startPos < currentPos)
		{
			retStr[i] = string[startPos];
			++i;
			++startPos;
		}
		retStr[i] = '\0';
		startPos++;

		return retStr;
	}
	
	return nullptr;
}

int main()
{

	std::cout << read_string("Hello World This is a test!") << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;

	std::cout << read_string("Hello World This is another test!") << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
	std::cout << read_string(nullptr) << std::endl;
}

