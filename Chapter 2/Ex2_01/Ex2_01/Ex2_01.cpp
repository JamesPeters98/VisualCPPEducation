// Ex2_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
// A simple example of a program.

#include <iostream>

// Namespace for standard library functions
// If used in header files will be globally available to any source file that uses that header.
using std::cout;
using std::endl;

int main()
{
	int apples = 5; int oranges = 6;

	int fruit = apples + oranges;

	cout << endl;
	cout << "Oranges are not the only fruit..." << endl
		 << "- and we have " << fruit << " fruits in all.";
	cout << endl;
}
