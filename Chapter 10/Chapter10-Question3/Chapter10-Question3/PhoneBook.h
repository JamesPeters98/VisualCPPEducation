#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "Person.h"

using std::make_pair;

using NameBook = std::multimap<Person, std::string>;
using NumberBook = std::multimap<std::string, Person>;

const size_t person{ 0 }, number{ 1 };

struct EntryData
{
    Person person;
    std::string number;
};

class PhoneBook
{

private:
    NameBook name_book;
    NumberBook number_book;

public:
    // Add a new entry to a phone name_book
    void addEntry();

    // List the contents of a phone name_book
    void listEntries();

    // Retrieve an entry from a phone name_book
    void getEntry_fromName();

    // Retrieve an entry from a phone name_book
    void getEntry_fromNumber();

    // Delete an entry from a phone name_book
    void deleteEntry();

    // Delete an entry from a phone name_book
    void deleteEntry_byNumber();

    // Read a person from cin
    Person getPerson() const;

    std::string getPhoneNumber() const;

    // Read a phone name_book entry from standard input
    EntryData inputEntry() const;


    void deletePerson(Person& person);
};

