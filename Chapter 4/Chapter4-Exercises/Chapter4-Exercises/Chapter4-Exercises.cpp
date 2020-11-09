// Chapter4-Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

using namespace std;

void question_1()
{
	// Setup initial array
	const int arrayBuffer{ 5 };
	int currentArraySize = arrayBuffer;
	int* pArray{ new int[currentArraySize] };

	int i{ 0 }; // Current index.
	
	for(;;)
	{
		if (i >= currentArraySize)
		{
			double total{ 0 };

			cout << "-------------------------" << endl;
			
			// Select every 5th value
			for (int x{0}; x < currentArraySize; x+= 5)
			{
				for (int y{ x }; y < (x + 5); y++)
				{
					cout << setw(4) << pArray[y];
					total += pArray[y];
				}
				cout << endl;
			}

			cout << "-------------------------" << endl;

			// Output average of the previous values
			cout << "Average of values: " << (total / currentArraySize) << endl;

			
			int oldSize{ currentArraySize };
			currentArraySize += arrayBuffer;
			int* pTempArray{ new int[currentArraySize] };

			for (int x{0}; x < oldSize; x++)
			{
				pTempArray[x] = pArray[x];
			}

			delete[] pArray;
			pArray = pTempArray;
			pTempArray = nullptr;
		}

		cout << "Enter a new number to add!" << endl;
		cin >> pArray[i];
		cout << "You entered " << pArray[i] << " at element " << i << endl << endl;

		++i;
	}
}

void question_2()
{
	// Setup initial array
	const int arrayBuffer{ 5 };
	int currentArraySize = arrayBuffer;
	int* pArray{ new int[currentArraySize] };

	int i{ 0 }; // Current index.

	for (;;)
	{
		if (i >= currentArraySize)
		{
			double total{ 0 };

			cout << "-------------------------" << endl;

			// Select every 5th value
			for (int x{ 0 }; x < currentArraySize; x += 5)
			{
				for (int y{ x }; y < (x + 5); y++)
				{
					cout << setw(4) << *(pArray + y);
					total += *(pArray + y);
				}
				cout << endl;
			}

			cout << "-------------------------" << endl;

			// Output average of the previous values
			cout << "Average of values: " << (total / currentArraySize) << endl;


			int oldSize{ currentArraySize };
			currentArraySize += arrayBuffer;
			int* pTempArray{ new int[currentArraySize] };

			for (int x{ 0 }; x < oldSize; x++)
			{
				*(pTempArray + x) = *(pArray + x);
			}

			delete[] pArray;
			pArray = pTempArray;
			pTempArray = nullptr;
		}

		cout << "Enter a new number to add!" << endl;
		cin >> *(pArray + i);
		cout << "You entered " << *(pArray + i) << " at element " << i << endl << endl;

		++i;
	}



}

void question_3()
{
	char str[] {"this was a lowercase string!"};	// Initial char array
	char* newStr = new char[strlen(str) + 1];		// Create a new char array of same size

	// Copy the string into the new array.
	strcpy_s(newStr, _countof(str), str);

	
	for (size_t i{}; i < strlen(str); i++)
	{
		if ((i % 2) == 0)
		{
			if ((newStr[i] >= 'a') && (newStr[i] <= 'z'))
			{
				newStr[i] -= 32;
			}
		}
	}

	// Show comparisons
	cout << str << endl;
	cout << newStr << endl;
}

void question_4()
{
	double temperatures[]{ 48, 53, 57, 66, 77, 86, 92, 91, 81, 70, 55, 46 };

	double total{ 0.0 }, min{}, max{ };

	for (auto t : temperatures)
	{
		t = (t - 32) * (5.0 / 9.0);
		// If total is zero set initial min/max values
		if (total == 0.0)
		{
			min = t;
			max = t;
		}

		if (t < min) min = t;
		if (t > max) max = t;

		total += t;
	}

	double avg{ total / _countof(temperatures) };

	cout << std::fixed;
	cout << setprecision(1);
	
	cout << "Average: " << avg << " \370C" << endl;
	cout << "Min: " << min << " \370C" << endl;
	cout << "Max: " << max << " \370C" << endl;
	
}

int main()
{
	// question_1();
	// question_2();
	// question_3();
	question_4();
}
