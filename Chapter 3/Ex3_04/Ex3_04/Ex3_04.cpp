// Ex3_04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int nCakes{ 1 }; // Number of cakes

	cout << "We have " << nCakes << " cake" << ((nCakes > 1) ? "s." : ".") << endl;

	++nCakes;

	cout << "We have " << nCakes << " cake" << ((nCakes > 1) ? "s." : ".") << endl;

}


