// Chatper2-Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void question_1()
{
	int value{};
	
	cout << "Enter a number to print!" << endl;
	cin >> value;
	cout << "The value entered was: " << value << endl;
}

void question_2()
{
	int value{};

	cout << "Enter a number to find it's remainder when divided by 8" << endl;
	cin >> value;

	// n % 2^i = n & (2^i - 1)
	// Since this ANDs together all of the bits below the power of 2
	// e.g 8 % 8 => 1000 & 0111 == 0

	int mask{ 0b0111 };
	int remainder{ value & mask };

	cout << "The remainder is: " << remainder;
}

void compare_vals(int original, int parenthesized)
{
	cout << "Original value: " << original << " Parenthesized: " << parenthesized << endl;
}

void question_3() 
{
	cout << "Value 1:" << endl;
	compare_vals({ 1 + 2 + 3 + 4 }, { (((1 + 2) + 3) + 4) });
	
	cout << "Value 2:" << endl;
	compare_vals({ 16 * 4 / 2 * 3 }, { (((16 * 4) / 2) * 3) });

	cout << "Value 3:" << endl;
	int a{10}, b{2}, c{10}, d{2}, e{5}, f{6};
	compare_vals({ a > b ? a : c > d ? e : f }, { (a > b) ? (a) : ((c > d) ? (e) : (f)) });

	cout << "Value 4:" << endl;
	compare_vals({ a & b && c & d }, { (a & b) && (c & d) });
}

void question_4()
{
	int width{ 1280 };
	int height{ 1024 };

	// Cast to double to avoid int division.
	double aspect = static_cast<double>(width) / static_cast<double>(height) ;

	cout << "Aspect ratio = " << aspect << endl;
}

void question_5()
{
	unsigned s{ 555 };

	int i{ static_cast<int>((s >> 4) & ~(~0 << 3)) };
	cout << i;

	// 555 in binary form is 0b1000101011
	// 555 >> 4 therefore = 0b100010
	// unsigned value of ~0 == 4,294,967,295 (Max unsigned int value)
	// (4,294,967,295 << 3) == 11111111111111111111111111111000
	// ~11111111111111111111111111111000 == 111
	// Resulting in 0b100010 & 0b000111 == 0b000010 == 2
	
}


int main()
{
	// question_1();
	// question_2();
	// question_3();
	// question_4();
	// question_5();
}