// Chapter8-Question6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <string>

template <class T>
class Stack
{
private:
	T sp{ 0 }; // Stack pointer
	uint64_t* stack; // Define stack to be the size of the max byte size + 1 == 256
	T SIZE;

	T MAX_SIZE = std::numeric_limits<T>::max();

	void increaseStackSize(T newSize);

public:
	// Creates stack with a custom size.
	Stack(T size);
	T StackSize();

	// Remove the value at the top of the stack and return it
	uint64_t pop();
	// Add a value to the top of the stack
	void push(uint64_t val);
	// Look at the value currently at the top of the stack without removing it.
	uint64_t* peek();
	// prints array of items currently on the stack
	void print();

	void printStackInfo(uint64_t testSize, bool doPrint = true);
};

// Creates stack with a custom size.
template <class T>
Stack<T>::Stack(T size)
{
	SIZE = size;
	stack = new uint64_t[SIZE];
}

template <class T>
T Stack<T>::StackSize()
{
	return SIZE;
}


// Remove the value at the top of the stack and return it
template <class T>
uint64_t Stack<T>::pop()
{
	// If this wasn't caught stack would start reading data from the top of the stack that may be garbage.
	if (sp)
	{
		return stack[--sp]; // Currently leaves the previous data on the stack but is set for removal by the next push().
	}
	
	std::cout << "Stack is empty";
	return 0;
}

// Add a value to the top of the stack
template <class T>
void Stack<T>::push(uint64_t val)
{
	if (sp == MAX_SIZE) {
		throw std::string("Reached max limit for stack pointer: ") + std::to_string(MAX_SIZE);
	}
	
	// If this wasn't caught previous values on the stack would be overwritten, starting with the very first item pushed.
	if (sp >= SIZE)
	{
		increaseStackSize(SIZE);
	}

	stack[sp++] = val;
}

// Look at the value currently at the top of the stack without removing it.
template <class T>
uint64_t* Stack<T>::peek()
{
	if (sp == 0)
		return nullptr;
	return &stack[sp - 1];
}

template <class T>
void Stack<T>::increaseStackSize(T additionalMem)
{
	T newSize = SIZE + additionalMem;
	if (newSize <= SIZE || newSize <= additionalMem )
	{
		newSize = MAX_SIZE;
	}
	
	uint64_t* temp{ new uint64_t[newSize] };
	//std::memcpy(temp, stack, newSize);
	for (T i{}; i < SIZE; i++)
		temp[i] = stack[i];
	
	SIZE = newSize;
	delete[] stack;
	stack = temp;

	std::cout << "Increased stack size to " << +newSize << std::endl;
}


// prints array of items currently on the stack
template <class T>
void Stack<T>::print()
{
	std::cout << "Stack values: [";
	for (T i = 0; (i < sp); i++)
		std::cout << stack[i] << ", ";
	std::cout << "]" << std::endl;
}

// Pushes values from 0 to 'testSize' onto the stack
// And then pops them off.
template <class T>
void Stack<T>::printStackInfo(uint64_t testSize, bool doPrint)
{
	std::cout << "Printing Stack with SP type: " << typeid(T).name() << std::endl;
	std::cout << "Stack SIZE = " << +StackSize() << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	try
	{
		std::cout << "Populating stack: " << std::endl;
		for (T i{0}; i < testSize; ++i)
			push(i);

		if(doPrint) print();

		std::cout << "Popping from stack: " << std::endl;
		for (T i{0}; i < testSize; ++i)
			pop();

		if(doPrint) print();
	}
	catch (std::string err)
	{
		std::cerr << err << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	// Physical limit = 255.
	Stack<uint8_t> stack{5};
	stack.printStackInfo( 100);	// First run increases stack up to 160
	stack.printStackInfo( 100);	// Second run the stack is already at 160 so doesn't need to be increased.
	stack.printStackInfo(256);	// Push stack to it's physical 8bit limit - will throw an exception.

	Stack<uint16_t> stack16{ 512 };
	stack16.printStackInfo(65536, false);

	Stack<uint32_t> stack32{ 131072 };
	stack32.printStackInfo(16777216, false); // Can't use all 32bits ~= 4GB since it crashes due to using too much memory.

	while (1);
}