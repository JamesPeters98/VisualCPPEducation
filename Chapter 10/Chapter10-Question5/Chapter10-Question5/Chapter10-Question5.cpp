// Chapter10-Question5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <vector>


int main()
{

	// Recursion function
	std::function<void (std::vector<int>&, size_t, int, int)> fib_recur =
		[&](std::vector<int>& vec, size_t MAX_SIZE, int prevValue = 0, int currentVal = 1)
		{
			vec.push_back(prevValue);
			if (vec.size() > MAX_SIZE) return;
			fib_recur(vec, MAX_SIZE, currentVal, currentVal + prevValue);
		};

	// Wrapper to call the fibonacci function with the array and starting parameters.
	auto fib = [&](size_t MAX_SIZE) -> std::vector<int>
	{
		std::vector<int> values;
		fib_recur(values, MAX_SIZE, 0, 1);
		return values;
	};

	
	std::vector<int> values = fib(20);

	for(int i : values)
	{
		std::cout << i << std::endl;
	}
}
