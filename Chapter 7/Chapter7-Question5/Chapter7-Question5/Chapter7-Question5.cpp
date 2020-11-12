// Chapter7-Question5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <string>

class Stack
{
private:
	uint8_t sp{0}; // Stack pointer
	uint64_t stack[UINT8_MAX + 1]; // Define stack to be the size of the max byte size + 1 == 256

public:
	
	// Remove the value at the top of the stack and return it
	uint64_t pop()
	{
		// If this wasn't caught stack would start reading data from the top of the stack that may be garbage.
		if (sp == 0) 
			throw std::string("Stack underflow: stack-pointer = ") + std::to_string(sp);
		
		return stack[sp++]; // Currently leaves the previous data on the stack but is set for removal by the next push().
	}

	// Add a value to the top of the stack
	void push(uint64_t val)
	{
		// If this wasn't caught previous values on the stack would be overwritten, starting with the very first item pushed.
		if (--sp == 0) 
			throw std::string("Stack overflow: stack-pointer = ") + std::to_string(sp) + std::string(" value entered: ") + std::to_string(val);
		
		stack[sp] = val;
	}

	// Look at the value currently at the top of the stack without removing it.
	uint64_t peek()
	{
		return stack[sp];
	}

	// prints array of items currently on the stack
	void print()
	{
		std::cout << "Stack values: [";
		for(size_t i = UINT8_MAX; (i >= sp) && sp != 0; i--)
			std::cout << stack[i] << ", ";
		std::cout << "]" << std::endl;
	}
};

int main()
{
	Stack stack;
	try
	{
		std::cout << "Populating stack: " << std::endl;
		for(int i{}; i < 255; i++)
			stack.push(i);
		
		stack.print();

		std::cout << "Peeking stack: " << stack.peek() << std::endl;

		std::cout << "Popping from stack: " << std::endl;
		for (int i{}; i < 255; i++)
			std::cout << "popped: " << stack.pop() << std::endl;
		
		stack.print();
		
	} catch (std::string err)
	{
		std::cerr << err;
		return 0;
	}
}



