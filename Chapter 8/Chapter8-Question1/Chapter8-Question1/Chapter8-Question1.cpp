// Chapter8-Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class EstimatedInt64
{
private:
	int64_t value;
	bool estimated;

public:
	void print();
	void println();
	void setEstimated(bool estimated);

	EstimatedInt64(int64_t val = 0, bool estimated = false)
	{
		this->value = val;
		this->estimated = estimated;
	}

	EstimatedInt64 operator+(const EstimatedInt64& estimated_int64) const
	{
		return EstimatedInt64(value + estimated_int64.value, (estimated || estimated_int64.estimated));
	}

	EstimatedInt64 operator+(const int& val) const
	{
		return EstimatedInt64(value + val, estimated);
	}

	EstimatedInt64& operator+=(const EstimatedInt64& estimated_int64)
	{
		value += estimated_int64.value;
		estimated = estimated || estimated_int64.estimated;
		return *this;
	}

	EstimatedInt64& operator-=(const EstimatedInt64& estimated_int64)
	{
		value -= estimated_int64.value;
		estimated = estimated || estimated_int64.estimated;
		return *this;
	}
	
};

void EstimatedInt64::print()
{
	std::cout << value;
	if(estimated) std::cout << "E";
}

void EstimatedInt64::println()
{
	print();
	std::cout << std::endl;
}

void EstimatedInt64::setEstimated(bool estimated)
{
	this->estimated = estimated;
}




int main()
{
    std::cout << "Hello World!\n";

	EstimatedInt64 value{ 5 };
	value.println();
	value.setEstimated(true);
	value.println();

	EstimatedInt64 value2{ 6, true };
	value2.println();

	EstimatedInt64 value3{ value + value2 };
	value3.println();

	value3 += value2;
	value3.println();

	value3 += 3;
	value3.println();

	value3 -= 3;
	value3.println();
}
