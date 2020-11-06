// Chapter3-Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

// While loop variant
void question_1a()
{
	int sum{}, value{};

	cout << "Enter a value to start summation. Enter 0 to exit." << endl;
	cin >> value;

	while (value != 0)
	{
		sum += value;
		cout << "Enter a value to add to summation. Enter 0 to exit." << endl;
		cin >> value;
	}

	cout << "Sum: " << sum;
}

// do-while variant
void question_1b()
{
	int sum{}, value{};

	do
	{
		cout << "Enter a value to add to summation. Enter 0 to exit." << endl;
		cin >> value;
		sum += value;
	} while (value != 0);

	cout << "Sum: " << sum;
}

// for loop variant
void question_1c()
{
	int sum{}, value{};

	for (;;)
	{
		cout << "Enter a value to add to summation. Enter 0 to exit." << endl;
		cin >> value;
		if (value == 0) break;
		sum += value;
	}

	cout << "Sum: " << sum;
}

void question_2()
{
	char c{};
	int vowels{};

	for(;;)
	{
		cout << "Enter a character (q to exit)" << endl;
		cin >> c;

		if ((c >= 'A') && (c <= 'Z'))
		{
			c += 'a' - 'A'; //Convert to lowercase
		}

		switch (c)
		{
		case 'q':
			// 'goto' could be replaced with an if statement before or after the switch.
			// would be best to just call a separate method that handles the quit functionality.
			// Since goto is considered bad practice by many people :)
			goto quit;
			
		case 'a': case 'e': case 'i': case 'o': case 'u':
			vowels++;
			break;
			
		default:
			break;
		}
	}

	quit:
	cout << "You entered " << vowels << " vowel" << ((vowels > 1) ? "s." : ".") << endl;		
}

// Multiplication table
void question_3()
{
	int range_low{ 2 }, range_upper{ 12 };
	int width{ 4 };

	// Print the range of values in the top row
	cout << setw(width) << " X " << " |";
	for (int i{ range_low }; i <= range_upper; i++)
	{
		cout << setw(width) << i;
	}
	cout << endl;

	// Print the row separator
	cout << setw(width) << "-----" << "|";
	for (int i{ range_low }; i <= range_upper; i++)
	{
		cout << "----";
	}
	cout << endl;

	// Print the multiplication table
	for (int col{ 1 }; col <= range_upper; col++) {
		cout << setw(width) << col << " |";
		for (int i{ range_low }; i <= range_upper; i++)
		{
			cout << setw(width) << col*i;
		}
		cout << endl;
	}
}

/**********************************
 * QUESTION 4
 **********************************/

// Binary = 0b00, Text = 0b01
enum class FILE_TYPE : int { BINARY, TEXT };

// Read = 0b00, Write = 0b01, Append = 0b10
// Shifted to left by 1.
enum class ACCESS_MODE { READ, WRITE, APPEND, UNDEFINED };

FILE_TYPE getFileType(int data)
{
	return static_cast<FILE_TYPE>(data & 0b1);
}

ACCESS_MODE getAccessMode(int data)
{
	return static_cast<ACCESS_MODE>((data >> 1) & 0b11);
}

int setAccessMode(int data, ACCESS_MODE mode)
{
	return (data | (static_cast<int>(mode) << 1));
}

int setFileType(int data, FILE_TYPE mode)
{
	return (data | static_cast<int>(mode));
}

int askUserForInput()
{
	cout << "Enter a file type:" << endl;
	cout << static_cast<int>(FILE_TYPE::BINARY) << ". Binary" << endl;
	cout << static_cast<int>(FILE_TYPE::TEXT) << ". Text" << endl;
	int file_type{};
	cin >> (file_type);

	cout << "Enter a access mode:" << endl;
	cout << static_cast<int>(ACCESS_MODE::READ) << ". Read" << endl;
	cout << static_cast<int>(ACCESS_MODE::WRITE) << ". Write" << endl;
	cout << static_cast<int>(ACCESS_MODE::APPEND) << ". Append" << endl;
	int access_mode{};
	cin >> (access_mode);

	int data{};
	data = setFileType(data, static_cast<FILE_TYPE>(file_type));
	data = setAccessMode(data, static_cast<ACCESS_MODE>(access_mode));

	return data;
}

void question_4()
{
	int attrData{ askUserForInput() };

	FILE_TYPE file_type = getFileType(attrData);
	ACCESS_MODE access_mode = getAccessMode(attrData);

	cout << "File type: ";
	switch (file_type)
	{
		case FILE_TYPE::BINARY:
			cout << "Binary";
			break;
		case FILE_TYPE::TEXT:
			cout << "Text";
			break;
		default:
			cout << "invalid";
			break;
	}
	cout << endl;

	cout << "Access mode: ";
	switch (access_mode)
	{
		case ACCESS_MODE::READ:
			cout << "Read";
			break;
		case ACCESS_MODE::WRITE:
			cout << "Write";
			break;
		case ACCESS_MODE::APPEND:
			cout << "Append";
			break;
		default:
			cout << "invalid";
			break;
	}
	cout << endl;
	
}


int main()
{
	// question_1a();
	// question_1b();
	// question_1c();
	// question_2();
	// question_3();
	question_4();
}
