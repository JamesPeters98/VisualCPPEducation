// Chapter10-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	istream_iterator<char> charInput{ cin }, end;

	vector<char> chars;

	while (charInput != end)
	{
		chars.push_back(*charInput++);
	}

	sort(chars.begin(), chars.end());

	for (char c : chars)
	{
		cout << c;
	}

}
