// Chapter10-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

using namespace std;

int main()
{
	istream_iterator<char> charInput{ cin }, end;

	list<char> chars;

	while (charInput != end)
	{
		chars.push_back(*charInput++);
	}

	chars.sort(less<>());

	for (char c : chars)
	{
		cout << c;
	}

}
