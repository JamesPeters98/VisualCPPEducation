// Ex3_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int main()
{
	char letter{};

	cout << "Enter a letter" << endl;
	cin >> letter;

	if (letter >= 'A')
	{
		if (letter <= 'Z')
		{
			cout << "You entered a capital letter!" << endl;

			letter += 'a' - 'A'; // Convert to lowercase
			cout << "I converted it to lowercase: " << letter << endl;
			
			return 0;
		}
	}

	
	if (letter >= 'a')
	{
		if (letter <= 'z')
		{
			cout << "You entered a lowercase letter!" << endl;
			return 0;
		}	
	}

	cout << "You didn't enter a letter!" << endl;
	return 0;
}