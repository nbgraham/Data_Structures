/*
Project 0
CS 2413
Dean Hougen
Fall 2015

A program that reads exoplanet data, stores it in appropriate data structures, and outputs the data in a desired fashion
@author Nicholas Graham 113038384
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Exoplanet.h"
#include "Exosystem.h"
#include "Array.h"
#include "Data.h"

//Object that stores all the data for the exosystems
Data planetData;

bool dataInputLoop();
bool dataManipulationLoop();
Exosystem* search(char userChoice);
double convertToDouble(const string& s);
char convertToKey(string input);
Exoplanet* createSearchValue(string input);
Exoplanet* createSearchValue(string input, char userChoice);

/*
The main function that starts this program
*/
int main()
{	
	while (dataInputLoop()) {};
	if (!planetData.IsEmpty())
	{
		while (dataManipulationLoop()) {};
	}
	
	return 0;
}

bool dataInputLoop()
{
	string fileName;
	cout << "Enter a file name (blank to continue): ";
	getline(cin, fileName);

	if (fileName == "")
	{
		return false;
	}

	try
	{
		planetData.addDataFromFile(fileName);
		cout << "Data from " << fileName << " was read in." << "\n";
	}
	catch (exception e)
	{
		cout << e.what() << "\n";
	}

	return true;
}

bool dataManipulationLoop()
{
	string input;
	char userChoice;
	cout << "--------------------------------------------------------------------------\n";
	cout << "Choose an option : \n 'P' for print, 'S' for sort, 'F for find, and 'E' for exit.\n";
	getline(cin, input);
	userChoice = input.at(0);

	if (userChoice == 'P')
	{
		//Print
		cout << planetData.toString();
	}
	else if (userChoice == 'S')
	{
		//Sort
		string input;
		cout << "Choose a value to sort by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		getline(cin, input);

		try
		{
			planetData.sort(convertToKey(input));
			cout << "Sorted on " << input << '\n';
		}
		catch (exception e)
		{
			cout << e.what() << "\n";
		}
	}
	else if (userChoice == 'F')
	{
		//Find
		string input;
		cout << "Choose a value to search by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		getline(cin, input);

		try
		{
			Exosystem* result = search(convertToKey(input));

			if (result == nullptr)
			{
				cout << "Planet not found\n";
			}
			else
			{
				cout << result->toString() << "\n";
			}
		}
		catch (exception e)
		{
			cout << e.what() << '\n';
		}
	}
	else if (userChoice == 'E')
	{
		//Exit
		return false;
	}
	else
	{
		cout << "Invalid choice.\n";
	}

	return true;
}

Exosystem* search(char userChoice)
{
	Exoplanet* searchValue = nullptr;
	string input;
	string check = "MAPEOTK";

	if (userChoice == 'N')
	{
		//Name
		cout << "Input the name to search by: ";
		getline(cin, input);
		
		searchValue = createSearchValue(input);
	}
	else if (check.find(userChoice) != check.npos)
	{
		//One of the double attributes was selected
		cout << "Input the double to search by: ";
		getline(cin, input);

		searchValue = createSearchValue(input, userChoice);
	}
	else
	{
		throw exception("Invalid choice.");
	}

	return planetData.search(*searchValue, userChoice);
}

/*
Code adapted from:
http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
*/
double convertToDouble(const string& s)
{
	bool encounteredDecimal = false;
	string::const_iterator it = s.begin();
	while (it != s.end())
	{
		if (!isdigit(*it))
		{
			if (*it == '.')
			{
				if (encounteredDecimal) throw exception("Too many decimal points.");
				else encounteredDecimal = true;
			}
			else throw exception("Input has invalid characters.");
		}
	
		++it;
	}

	return stod(s);
}

char convertToKey(string input)
{
	char userChoice;
	if (input.length() > 1) throw exception("Entry has more than one character.");
	else
	{
		userChoice = input.at(0);
		string check = "NMAPEOTK";
		if (check.find(userChoice, 0) == check.npos)
		{
			throw exception("Invalid choice.");
		}
	}

	return userChoice;
}

Exoplanet* createSearchValue(string input)
{
	//Validate name
	if (input.length() < 2 || input.at(input.length() - 2) != ' ' || input.at(input.length() - 1) == ' ')
	{
		//Name is not in correct format, return to data manipulation loop
		throw exception("Name is not in correct format.");
	}

	Exosystem* system = new Exosystem();
	string starName = input.substr(0, input.length() - 2);

	system->setStarName(starName);

	return new Exoplanet(input.at(input.length() - 1), 0, 0, 0, 0, 0, 0, 0, system, starName);
}

Exoplanet* createSearchValue(string input, char userChoice)
{
	double value = convertToDouble(input);

	switch (userChoice)
	{
	case 'M':
		return new Exoplanet(userChoice, value, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		break;
	case 'A':
		return new Exoplanet(userChoice, 0.0, value, 0.0, 0.0, 0.0, 0.0, 0.0);
		break;
	case 'P':
		return new Exoplanet(userChoice, 0.0, 0.0, value, 0.0, 0.0, 0.0, 0.0);
		break;
	case 'E':
		return new Exoplanet(userChoice, 0.0, 0.0, 0.0, value, 0.0, 0.0, 0.0);
		break;
	case 'O':
		return new Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, value, 0.0, 0.0);
		break;
	case 'T':
		return new Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, 0.0, value, 0.0);
		break;
	case 'K':
		return new Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, value);
		break;
	default:
		return nullptr;
		break;
	}
}