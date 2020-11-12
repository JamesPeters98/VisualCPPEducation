// Chapter7-Question4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class CRecord
{
private:
	char name[14];
	int item_number;

public:
	void putRecord()
	{
		std::cout	<< "Record: " << name << std::endl
					<< "Item#: " << item_number << std::endl;
	}

	bool getRecord()
	{
		std::cout << "Enter the Record item number: " << std::endl;
		std::cin >> item_number;
		std::cout << "Enter the Record's name: " << std::endl;
		std::cin >> name;
		if (item_number == 0) return false;
		return true;
	}
};

int main()
{
	for(;;)
	{
		CRecord record;
		bool isZero = !record.getRecord();
		record.putRecord();

		if (isZero) break;
	}

	std::cout << "Found zero item-number, exiting.";
}
