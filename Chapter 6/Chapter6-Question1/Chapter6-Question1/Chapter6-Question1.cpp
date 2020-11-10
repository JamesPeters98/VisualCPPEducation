// Chapter6-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int ascVal(size_t i, const char* p)
{
    // Return the ASCII value of the char
    if (!p || i > strlen(p))
        return -1;
    else
        return p[i];
}

int (*func)(size_t i, const char* p);

int main()
{
    func = ascVal;

    const char* arr{ "Hello world!" };

	for (size_t i{0}; i <= strlen(arr); i++)
	{
        std::cout << "Value for " << arr[i] << ": " << func(i, arr) << std::endl;
	}
}
