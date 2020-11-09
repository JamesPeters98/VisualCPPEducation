// Chapter5-Question4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void readInput(int* number, char name[]);

void readInput(int* number, char name[])
{
	cout << "Enter a number: (0 to exit)" << endl;
	cin >> *number;

	if (*number != 0) {
		cout << "Enter a name: (Less than 15 characters)" << endl;
		cin >> name;
	}
}

void printOutput(int* number, char name[]);

void printOutput(int* number, char name[])
{
	cout << "Name selected: " << name << " number: " << *number << endl;;
}



int main()
{
	char nameArray[15];
	int number{};

	for (;;) {
		readInput(&number, nameArray);
		if(number == 0) break;
		printOutput(&number, nameArray);
	}

	cout << "Exited!";
	return 0;
}
