// Ex3_05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int choice{}; // Store selection value here

	cout << endl
		<< "Your electronic recipe book is at your service." << endl
		<< "You can choose from the following delicious dishes: "
		<< endl
		<< endl << "1 Boiled eggs"
		<< endl << "2 Fried eggs"
		<< endl << "3 Scrambled eggs"
		<< endl << "4 Coddled eggs"
		<< endl << endl << "Enter your selection number: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		{	// When initialising variables in switch they must be between braces.
			int count{ 2 };
			cout << endl << "Boil " << count << " eggs." << endl;
			break;
		}
	case 2: 
		cout << endl << "Fry some eggs." << endl;
		break;
	case 3: 
		cout << endl << "Scramble some eggs." << endl;
		break;
	case 4: 
		cout << endl << "Coddle some eggs." << endl;
		break;
	default: 
		cout << endl << "You entered a wrong number, try raw eggs."
		<< endl;
		break;
	}
}

