// Chapter6-Question2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Method prototypes
bool equal(char, char);
bool equal(int, int);
bool equal(double, double);
bool equal(char*, char*);

// Implementations
bool equal(int i1, int i2)
{
	return i1 == i2;
}

bool equal(double d1, double d2)
{
	return d1 == d2;
}

bool equal(char c1, char c2)
{
	return c1 == c2;
}

bool equal(char* c1, char* c2)
{
	return strcmp(c1, c2) == 0;
}

int main()
{
	std::cout << "Compare 1 and 1 = " << equal(1, 1) << std::endl;
	std::cout << "Compare 1 and 10 = " << equal(1, 10) << std::endl;
	std::cout << "Compare 3.1415 and 2.7182 = " << equal(3.1415, 2.7182) << std::endl;
	std::cout << "Compare 3.1415 and 3.1415 = " << equal(3.1415, 3.1415) << std::endl;
	std::cout << "Compare a and a = " << equal('a', 'a') << std::endl;
	std::cout << "Compare A and a =" << equal('A', 'a') << std::endl;

	char c1[]{ "Hello" };
	char c2[]{ "Hello" };
	std::cout << "Compare "<< c1 <<" and " << c2 << " = " << equal(c1, c2) << std::endl;

	char c3[]{ "Hello" };
	char c4[]{ "Bye" };
	std::cout << "Compare " << c3 << " and " << c4 << " = " << equal(c3, c4) << std::endl;
}

