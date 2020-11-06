// Ex3_06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	char letter{};
	cout << endl
		<< "Enter a small letter: ";
	cin >> letter;

	// Interesting way of selecting only lowercase letters
	switch (letter * (letter >= 'a' && letter <= 'z'))
	{
	case 'a': case 'e': case 'i': case 'o': case 'u':
		cout << endl << "You entered a vowel.";
		break;

	case 0:
		cout << endl << "That is not a small letter.";
		break;

	default: cout << endl << "You entered a consonant.";
	}

	cout << endl;
}


