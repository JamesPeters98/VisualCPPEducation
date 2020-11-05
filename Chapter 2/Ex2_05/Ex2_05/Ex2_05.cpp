// Ex2_05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	double height{}, width{}, length{};

	double perimeter{};

	const double rollWidth{ 21.0 };
	const double rollLength{ 12.0 * 33.0 };

	int strips_per_roll{};
	int strips_reqd{};
	int n_rolls{};

	cout << endl
		<< "Enter the height of the room in inches: ";
	cin >> height;

	cout << endl
		<< "Now enter the length and width in inches: ";
	cin >> length >> width;

	strips_per_roll = static_cast<int> (rollLength / height);
	perimeter = 2.0 * (length + width);
	strips_reqd = static_cast<int> (perimeter / rollWidth);
	n_rolls = strips_reqd / strips_per_roll;

	cout << endl
		<< "For your room you need " << n_rolls << " rolls of wallpapers."
		<< endl;
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
