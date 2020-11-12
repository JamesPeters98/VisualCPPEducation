// Chapter7-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Sample
{
	int data1;
	int data2;
	char* sPtr = nullptr;
};

void printSample(Sample *sample);

int main()
{
	char* p_str = new char[] {"Hello world!"};
	
	Sample a{ 10, 42, p_str };
	Sample b{};

	std::cout << "init values in a: " << a.data1 << " & " << a.data2 << std::endl;
	std::cout << "init values in b: " << b.data1 << " & " << b.data2 << std::endl;
	std::cout << "init string in a: " << a.sPtr << std::endl;
	std::cout << std::endl;

	b = a;

	std::cout << "After assingment of b = a" << std::endl;
	std::cout << "values in a: " << a.data1 << " & " << a.data2 << std::endl;
	std::cout << "values in b: " << b.data1 << " & " << b.data2 << std::endl;
	std::cout << "string in a: " << a.sPtr << " & b: " << b.sPtr << std::endl;
	std::cout << std::endl;

	char string[] { " This is a new string!" };
	strncat_s(a.sPtr, strlen(a.sPtr) + strlen(string) + 2, string, strlen(string));

	std::cout << "After changing a.p_str" << std::endl;
	std::cout << "values in a: " << a.data1 << " & " << a.data2 << std::endl;
	std::cout << "values in b: " << b.data1 << " & " << b.data2 << std::endl;
	std::cout << "string in a: " << a.sPtr << " & b: " << b.sPtr << std::endl;
	std::cout << std::endl;

	// This changes the string for both a AND b, since they both point to the same char array.
	// To get around this the pointer value should be changed to point to a new string.

	b.sPtr = new char[] {"B now has a different string!"};

	std::cout << "After pointing new string to b.p_str" << std::endl;
	std::cout << "string in a: " << a.sPtr << " & b: " << b.sPtr << std::endl;
	std::cout << std::endl;

	printSample(&a);
	printSample(&b);
}

void printSample(Sample* sample)
{
	std::cout << "Printing sample: " << std::endl;
	std::cout << "data1: " << sample->data1 << std::endl;
	std::cout << "data2: " << sample->data2 << std::endl;
	std::cout << "string: " << sample->sPtr << std::endl;
	std::cout << std::endl;
}
