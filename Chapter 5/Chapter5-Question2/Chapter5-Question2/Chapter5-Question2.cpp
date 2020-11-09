// Chapter5-Question2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void swapInts(int*, int*);

int main()
{
	int i1 = 1;
	int i2 = 2;

	std::cout << "Int 1: " << i1 << " Int 2: " << i2 << std::endl;
	swapInts(&i1, &i2);
	std::cout << "After swap: " << std::endl;
	std::cout << "Int 1: " << i1 << " Int 2: " << i2 << std::endl;
}

void swapInts(int* i1, int* i2)
{
	// Temporary store the value at int pointer 2.
	int temp2{ *i2 };

	// Set value at second pointer to value at first pointer
	*i2 = *i1;
	
	// Set value at first pointer to temporary value stored.
	*i1 = temp2;
}


