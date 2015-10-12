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

#include "ValidationException.h"
#include "Exoplanet.h"
#include "Exosystem.h"
#include "ExosystemShell.h"
#include "MyArray.h"
#include "Data.h"

//Object that stores all the data for the exosystems
Data planetData;

bool dataManipulationLoop();
Exosystem* search(char userChoice);
bool is_number(const string& s);


/*
The main function that starts this program
*/
int main()
{
	//TODO: User specified files
	//User enter files until presses enter on blank -> data maniupulation
	//User enters invalid file, inform them and continue in loop

	try
	{
		planetData.addDataFromFile("data.csv");
		while (dataManipulationLoop()) {};
	}
	catch (ValidationException exp)
	{
		cout << exp.getInfo();
	}
	return 0;
}

bool dataManipulationLoop()
{
	char userChoice;
	cout << "--------------------------------------------------------------------------\n";
	cout << "Choose an option : \n 'P' for print, 'S' for sort, 'F for find, and 'E' for exit.\n";
	userChoice = cin.get();
	cin.ignore();

	if (userChoice == 'P')
	{
		cout << planetData.toString();
	}
	else if (userChoice == 'S')
	{
		//Sort
		cout << "Choose a value to sort by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		userChoice = cin.get();
		cin.ignore();

		planetData.sort(userChoice);
	}
	else if (userChoice == 'F')
	{
		//Find
		cout << "Choose a value to search by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		userChoice = cin.get();
		cin.ignore();

		Exosystem* result = search(userChoice);

		if (result == nullptr)
		{
			cout << "Planet not found\n";
		}
		else
		{
			cout << result->toString() << "\n";
		}

		return true;
	}
	else if (userChoice == 'E')
	{
		return false;
	}

	return true;
}

Exosystem* search(char userChoice)
{
	Exoplanet searchValue;
	string key;
	string input;
	double value;
	if (userChoice == 'N')
	{
		Exosystem* system = new Exosystem();
		string starName;

		cout << "Input the name to search by: ";
		getline(cin, input);

		//Validate name
		if (input.length() < 2 || input.at(input.length() - 2) != ' ' || input.at(input.length() - 1) == ' ')
		{
			//Name is not in correct format, return to data manipulation loop
			return nullptr;
		}
		
		starName = input.substr(0, input.length() - 2);
		system->setStarName(starName);

		searchValue = Exoplanet(input.at(input.length() - 1), 0, 0, 0, 0, 0, 0, 0, system, starName);
	}
	else if (userChoice == 'M' || userChoice == 'A' || userChoice == 'P' || userChoice == 'E' || userChoice == 'O' || userChoice == 'T' || userChoice == 'K')
	{
		switch (userChoice)
		{
		case 'M':
			key = "msini";
			break;
		case 'A':
			key = "a";
			break;
		case 'P':
			key = "per";
			break;
		case 'E':
			key = "ecc";
			break;
		case 'O':
			key = "om";
			break;
		case 'T':
			key = "t0";
			break;
		case 'K':
			key = "k";
			break;
		}
		cout << "Input the " << key << " to search by: ";
		getline(cin, input);

		try
		{
			//Convert to double
			if (!is_number(input)) throw exception();
			value = stod(input);
		}
		catch (exception e)
		{
			cout << "Not valid, cannot be converted to double.\n";
			return nullptr;
		}

		switch (userChoice)
		{
		case 'M':
			searchValue = Exoplanet(userChoice, value, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			break;
		case 'A':
			searchValue = Exoplanet(userChoice, 0.0, value, 0.0, 0.0, 0.0, 0.0, 0.0);
			break;
		case 'P':
			searchValue = Exoplanet(userChoice, 0.0, 0.0, value, 0.0, 0.0, 0.0, 0.0);
			break;
		case 'E':
			searchValue = Exoplanet(userChoice, 0.0, 0.0, 0.0, value, 0.0, 0.0, 0.0);
			break;
		case 'O':
			searchValue = Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, value, 0.0, 0.0);
			break;
		case 'T':
			searchValue = Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, 0.0, value, 0.0);
			break;
		case 'K':
			searchValue = Exoplanet(userChoice, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, value);
			break;
		}
	}

	return planetData.search(searchValue, userChoice);
}

/*
Code adapted from:
http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
*/
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end())
	{
		if (isalpha(*it))
		{
			return false;
		}
		++it;
	}
	return true;
}