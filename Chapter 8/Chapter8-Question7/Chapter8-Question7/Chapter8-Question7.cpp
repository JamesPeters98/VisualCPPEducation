// Chapter8-Question7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

void readInput();

void replace_string(string &message, string &replacement);

string message, replacement;

int main()
{
	readInput();
	replace_string(message, replacement);

	cout << "Replaced string: " << message;
}


void readInput()
{
	cout << "Enter a string: " << endl;
	getline(cin, message, '\n');

	cout << "You entered: " << message << endl;
	cout << "Now enter a word to be replaced!" << endl;

	getline(cin, replacement, '\n');
	cout << "Replacement: " << replacement << endl;
}

void replace_string(string &message, string &replacement)
{
	// Convert both string to lower case, storing the actual message separately
	string lowerCaseMessage{ message };
	std::transform(lowerCaseMessage.begin(), lowerCaseMessage.end(), lowerCaseMessage.begin(), ::tolower);
	std::transform(replacement.begin(), replacement.end(), replacement.begin(), ::tolower);
	string asterix(replacement.length(), '*'); // Create string of '*' the size of the replacement

	// Find first occurance of the replacement
	auto pos = lowerCaseMessage.find(replacement);

	// Loop to replacement all occurances
	while (pos != string::npos)
	{
		// Check if character is first character or has space before it. If not move to next pos and continue.
		if (pos != 0 && message.at(pos - 1) != ' ') {
			pos = lowerCaseMessage.find(replacement, pos + 1);
			continue;
		}

		// Check if character is last character or has space after it.
		size_t endOfString = pos + replacement.length();
		if (endOfString < message.length() && message.at(endOfString) != ' ') {
			pos = lowerCaseMessage.find(replacement, pos + 1);
			continue;
		}

		// Replace in both the actual message and the lowercase version so they are matching.
		message.replace(pos, replacement.size(), asterix);
		lowerCaseMessage.replace(pos, replacement.size(), asterix);
		pos = lowerCaseMessage.find(replacement);
	}
}



