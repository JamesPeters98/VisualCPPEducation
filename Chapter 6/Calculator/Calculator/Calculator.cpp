// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <math.h>

using namespace std;

/* TRIG FUNCTIONS*/
const double DEGREE_TO_RADIAN = M_PI / 180;

double sind(double degrees);
double cosd(double degrees);
double tand(double degrees);

void eatspaces(char* str);
double expr(char* str);
double term(char* str, size_t& index);
double number(char* str, size_t& index);
char* extract(char* str, size_t& index);

void printError(char* str, size_t index);

bool doFunction(char* str, size_t& index, double& value);

int main()
{
    const size_t MAX{ 80 };
	char buffer[MAX] {};

	cout << "Enter your calculation:" << endl;

	for (;;) {
		cin.getline(buffer, sizeof buffer);
		eatspaces(buffer);

		if (!buffer[0])
			return 0;

		try
		{
			cout << "\t= " << expr(buffer) << endl << endl;
		} catch (const char* pEx)
		{
			cerr << pEx << endl;
			cerr << "Ending program." << endl;
			return 1;
		}

		eatspaces(buffer);
	}


}

void eatspaces(char* str)
{
	size_t i{};                                    // 'Copy to' index to string
	size_t j{};                                    // 'Copy from' index to string

	while ((*(str + i) = *(str + j++)) != '\0')    // Loop while character
	  // copied is not \0
		if (*(str + i) != ' ')                         // Increment i as long as
			i++;                                         // character is not a space

	return;
}

double expr(char* str)
{
	double value{};
	size_t index{};

	value = term(str, index);

	for (;;)
	{
		switch (*(str + index++))
		{
		case '\0':
			return value;
		case '+':
			value += term(str, index);
			break;
		case '-':
			value -= term(str, index);
			break;

		default:
			printError(str, index);
			char message[38]{ "Expression evaluation error. Found: " };
			strncat_s(message, str + index - 1, 1); // Append the character
			throw message;			
		}
	}
	
}

double term(char* str, size_t& index)
{
	double value{};

	value = number(str, index);

	while(true)
	{
		if (*(str + index) == '*')
		{
			value *= number(str, ++index);
		}

		else if (*(str + index) == '/')
		{
			value /= number(str, ++index);
		}

		else if (*(str + index) == '^')
		{
			value = pow(value, number(str, ++index));
		}

		else break;
	}

	return value;
}

double number(char* str, size_t& index)
{
	double value{};

	if (*(str + index) == '(') // Start of parentheses
	{
		char* psubstr{}; // Pointer for substring
		psubstr = extract(str, ++index); // Extract substring in brackets
		value = expr(psubstr); // Get the value of the substring
		delete[]psubstr; // Clean up the free store
		return value; // Return substring value
	}

	// Check for digit or function
	if(!isdigit(*(str + index)))
	{
		// Check if there is a function at the current index
		// If so the function is resolved and value updated and returned.
		if(doFunction(str, index, value))
		{
			return value;
		}
		else 
		{
			printError(str, index);
			// Not a digit at start
			char message[31]{ "Invalid character in number: " };
			strncat_s(message, str + index, 1); //Adds char to message.
			throw message;
		}
	}

	// Creates a base 10 number starting from this digit.
	while (isdigit(*(str + index)))
		value = 10 * value + (*(str + index++) - '0');

	// Return if value has no decimal place next
	if (*(str + index) != '.')
		return value;

	// Add on decimal part to value
	double factor{ 1.0 };

	while(isdigit(*(str + (++index))))
	{
		factor *= 0.1;
		value = value + (*(str + index) - '0') * factor;
	}

	return value;
}

char* extract(char* str, size_t& index)
{
	char* pstr{};
	size_t numL{};				// Number of left brackets found
	size_t bufindex{ index };	// Save starting value for index

	do
	{
		switch (*(str + index))
		{
		case ')':
			if(0 == numL)
			{
				++index;
				pstr = new char[index - bufindex];
				if(!pstr)
				{
					throw "Memory allocation failed.";
				}
				// copy substring to new memory
				strncpy_s(pstr, index - bufindex, str + bufindex, index - bufindex - 1);

				return pstr;
			}
			else
			{
				numL--;
				break;
			}

		case '(':
			numL++;
			break;
		}
	}
	while (*(str + index++) != '\0');

	printError(str, index);
	throw "Ran off the end of the expression - must be bad input.";
}


// Creates a string with a '^' underneath the character at the given index
void printError(char* str, size_t index)
{
	cout << endl;
	cout << "Character at index " << index << " is bad: " << endl;
	cout << str << endl;

	// Add spaces until the given index is reached
	size_t i{ 0 };
	while (i < index)
	{
		cout << ' ';
		i++;
	}

	cout << '^' << endl << endl;;
}

bool doOperation(char* str, const char* opStr, size_t& index, double& value, double (*op)(double))
{
	size_t opSize = strlen(opStr);
	char* stringIndex = str + index;
	if (0 == strncmp(opStr, stringIndex, opSize))
	{
		index += opSize - 1;
		value = op(number(str, index));
		return true;
	}
	return false;
}

// Checks if a valid function is at the index in the given string
// If so it calculates the value and updates 'value'
// Returns true if a function was calculated, false if not.
bool doFunction(char* str, size_t& index, double& value)
{
	// Radian trig functions
	if (doOperation(str, "sin(", index, value, sin)) return true;
	if (doOperation(str, "cos(", index, value, cos)) return true;
	if (doOperation(str, "tan(", index, value, tan)) return true;

	// Degree trig functions
	if (doOperation(str, "sind(", index, value, sind)) return true;
	if (doOperation(str, "cosd(", index, value, cosd)) return true;
	if (doOperation(str, "tand(", index, value, tand)) return true;

	// Exponential function
	if (doOperation(str, "exp(", index, value, exp)) return true;
	
	return false;
}


double sind(double degrees)
{
	return std::sin(degrees * DEGREE_TO_RADIAN);
}

double cosd(double degrees)
{
	return std::cos(degrees * DEGREE_TO_RADIAN);
}

double tand(double degrees)
{
	return std::tan(degrees * DEGREE_TO_RADIAN);
}




