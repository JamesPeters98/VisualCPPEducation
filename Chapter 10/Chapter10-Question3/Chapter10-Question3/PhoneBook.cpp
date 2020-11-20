#include "PhoneBook.h"

// Add a new entry to a phone name_book
void PhoneBook::addEntry()
{
	EntryData data = inputEntry();

	name_book.emplace(make_pair(data.person, data.number));
	number_book.emplace(make_pair(data.number, data.person));

	std::cout << "Added entry for " << data.person.getName()
		<< ". The number is " << data.number << std::endl;
}

// List the contents of a phone name_book
void PhoneBook::listEntries()
{
	if (name_book.empty())
	{
		std::cout << "The phone name_book is empty." << std::endl;
		return;
	}
	std::cout << setiosflags(std::ios::left);              // Left justify output
	for (const auto& entry : name_book)
	{
		std::cout << std::setw(30) << entry.first.getName()
			<< std::setw(12) << entry.second << std::endl;
	}
	std::cout << resetiosflags(std::ios::right);           // Right justify output
}

// Retrieve an entry from a phone name_book
void PhoneBook::getEntry_fromName()
{
	Person person{ getPerson() };
	auto iter = name_book.lower_bound(person);
	if (iter == name_book.end())
		std::cout << "No entries found for " << person.getName() << std::endl;
	else {
		std::cout << "The following entries are listed for " << person.getName() << std::endl;

		auto upper = name_book.upper_bound(person);

		for (int i{}; iter != upper; ++iter, i++)
			std::cout << i << ". " << iter->second << std::endl;
	}
}

// Retrieve an entry from a phone name_book
void PhoneBook::getEntry_fromNumber()
{
	std::string phone_number{ getPhoneNumber() };
	auto iter = number_book.lower_bound(phone_number);
	if (iter == number_book.end())
		std::cout << "No entries found for " << phone_number << std::endl;
	else {
		std::cout << "The following entries are listed for " << phone_number << std::endl;

		auto upper = number_book.upper_bound(phone_number);

		for (int i{}; iter != upper; ++iter, i++)
			std::cout << i << ". " << iter->second.getName() << std::endl;
	}
}

void PhoneBook::deletePerson(Person& person)
{
	auto iter = name_book.lower_bound(person);
	if (iter == name_book.end())
		std::cout << "No entries found for " << person.getName() << std::endl;
	else {
		std::cout << "The following entries are listed for " << person.getName() << std::endl;

		auto upper = name_book.upper_bound(person);

		std::vector<std::multimap<Person, std::string>::iterator> vec;
		for (int i{}; iter != upper; ++iter, i++) {
			vec.push_back(iter);
			std::cout << i << ". " << iter->second << std::endl;
		}

		std::cout << "Select a number to delete: " << std::endl;
		int number;
		std::cin >> number;

		auto iterSelected{ vec[number] };
		name_book.erase(iterSelected);

	}
}

// Delete an entry from a phone name_book
void PhoneBook::deleteEntry()
{
	Person person{ getPerson() };
	deletePerson(person);
}



void PhoneBook::deleteEntry_byNumber()
{
	std::string phone_number{ getPhoneNumber() };
	
	auto iter = number_book.lower_bound(phone_number);
	if (iter == number_book.end())
		std::cout << "No entries found for " << phone_number << std::endl;
	else {
		std::cout << "The following entries are listed for " << phone_number << std::endl;

		auto upper = number_book.upper_bound(phone_number);

		std::vector<std::multimap<std::string, Person>::iterator> vec;
		for (int i{}; iter != upper; ++iter, i++) {
			vec.push_back(iter);
			std::cout << i << ". " << iter->second.getName() << std::endl;
		}

		std::cout << "Select a number to delete: " << std::endl;
		int number;
		std::cin >> number;

		auto iterSelected{ vec[number] };
		number_book.erase(iterSelected);

		// // Also remove the number from the name_book map
		// auto pIter = name_book.lower_bound(iterSelected->second);
		// if (pIter != name_book.end())
		// {
		// 	auto pUpper = name_book.upper_bound(iterSelected->second);
		// 	for (int i{}; pIter != pUpper; ++pIter, i++) {
		// 		if (pIter->second == iterSelected->first) {
		// 			name_book.erase(pIter);
		// 		}
		// 	}
		// }
	}
}


// Read a person from cin
Person PhoneBook::getPerson() const
{
	std::string first, second;
	std::cout << "Enter a first name: ";
	getline(std::cin, first);
	std::cout << "Enter a second name: ";
	getline(std::cin, second);
	return Person{ std::move(first), std::move(second) };
}

std::string PhoneBook::getPhoneNumber() const
{
	std::string phone_number;
	std::cout << "Enter a phone number: ";
	getline(std::cin, phone_number);
	return phone_number;
}

// Read a phone name_book entry from standard input
EntryData PhoneBook::inputEntry() const
{
	Person person{ getPerson() };

	std::string number;
	std::cout << "Enter the phone number for " << person.getName() << ": ";
	getline(std::cin, number);
	
	return EntryData{ (std::move(person)), number };
}
