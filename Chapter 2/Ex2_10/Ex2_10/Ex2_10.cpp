// Ex2_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Namespaces

#include <iostream>

namespace test_namespace
{
	int value{};
}

using namespace test_namespace;

int main()
{
    std::cout << "Enter an integer\n";
	std::cin >> value;
	std::cout << "\nYou entered " << value;
}