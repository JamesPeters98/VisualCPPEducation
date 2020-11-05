// Ex2_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Namespaces

#include <iostream>

namespace test_namespace
{
	int value{};
}

int main()
{
    std::cout << "Enter an integer\n";
	std::cin >> test_namespace::value;
	std::cout << "\nYou entered " << test_namespace::value;
}