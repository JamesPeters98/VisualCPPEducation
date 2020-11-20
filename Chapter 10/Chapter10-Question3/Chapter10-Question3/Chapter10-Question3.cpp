// Chapter10-Question3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>

#include "PhoneBook.h"

using std::string;

int main()
{
    PhoneBook phonebook;
    char answer{};

    while (true)
    {
        std::cout << "Do you want to enter a phone book entry(Y or N): ";
        std::cin >> answer;
        while (std::cin.get() != '\n');                      // Ignore up to newline
        if (toupper(answer) == 'N')
            break;
        if (toupper(answer) != 'Y')
        {
            std::cout << "Invalid response. Try again." << std::endl;
            continue;
        }
        phonebook.addEntry();
    }

    // Query the phonebook
    while (true)
    {
        std::cout << "\nChoose from the following options:" << std::endl
            << "A  Add an entry   D Delete an entry by name     G  Get an entry ny name    " << std::endl
            << "L  List entries   d Delete an entry by number   g  Get an entry by number  " << std::endl
            << "Q  Quit" << std::endl;
    	
        std::cin >> answer;
        while (std::cin.get() != '\n');                      // Ignore up to newline

        switch ((answer))
        {
        case 'A': case 'a':
            phonebook.addEntry();
            break;
        case 'G':
            phonebook.getEntry_fromName();
            break;
        case 'g':
            phonebook.getEntry_fromNumber();
        	break;
        case 'D':
            phonebook.deleteEntry();
            break;
        case 'd':
            phonebook.deleteEntry_byNumber();
            break;
        case 'L': case 'l':
            phonebook.listEntries();
            break;
        case 'Q': case 'q':
            return 0;
        default:
            std::cout << "Invalid selection. Try again." << std::endl;
            break;
        }
    }
    return 0;
}