// Chapter5-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

// Use 64 bit int since factorials get big VERY quickly :)
// Overflows at n = 21
uint64_t factorial(int n);

uint64_t factorial(int n)
{
	if (n == 1)
	{
		return 1;
	}

	return n * factorial(n - 1);
}


int main()
{
	cout << "Enter an integer to find it's factorial. (0 to exit)" << endl;

	int value{};
	cin >> value;

	if (value == 0) return 0;

	uint64_t answer = factorial(value);
	cout << "Answer: " << answer << endl;

	main();
}