// Ex2_02.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Manipulating output

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

int main()
{
    int num1 { 1234 }, num2 { 5678 };

	cout << endl;									// Start on new line
	cout << setw(6) << num1 << setw(6) << num2;		// Output two values
	cout << endl;									// Start on new line

	return 0;
}
