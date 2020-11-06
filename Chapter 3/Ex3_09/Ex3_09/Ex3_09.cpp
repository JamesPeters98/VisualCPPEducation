// Ex3_09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

int main()
{
	//Exercise 9
	const long max{ 16L };

	for (long i{}, power{ 1L }; i <= max; i++, power += power)
		cout << endl
		<< setw(10) << i << setw(10) << power; // Loop statement

	cout << endl;

	// Exercise 10

	double value{}; // Value entered stored here
	double sum{}; // Total of values accumulated here
	int i{}; // Count of number of values
	char indicator{ 'n' }; // Continue or not?

	for (;;) // Indefinite loop
	{
		cout << endl
			<< "Enter a value: ";
		cin >> value; // Read a value
		++i; // Increment count
		sum += value; // Add current input to total

		cout << endl
			<< "Do you want to enter another value (enter y or n)? ";
		cin >> indicator; // Read indicator
		if (('n' == indicator) || ('N' == indicator))
			break; // Exit from loop
	}

	cout << endl
		<< "The average of the " << i
		<< " values you entered is " << sum / i << "."
		<< endl;
	
	return 0;
}
