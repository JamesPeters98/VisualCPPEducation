// Chapter7-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Sample
{
	int data1;
	int data2;
};

int main()
{
	Sample a{ 10, 42 };
	Sample b{};

	std::cout << "init values in a: " << a.data1 << " & " << a.data2 << std::endl;
	std::cout << "init values in b: " << b.data1 << " & " << b.data2 << std::endl;

	b = a;

	std::cout << "After assingment of b = a" << std::endl;
	std::cout << "values in a: " << a.data1 << " & " << a.data2 << std::endl;
	std::cout << "values in b: " << b.data1 << " & " << b.data2 << std::endl;
}