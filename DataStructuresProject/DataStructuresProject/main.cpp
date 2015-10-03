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
using namespace std;

#include "ValidationException.h"
#include "Exoplanet.h"
#include "Exosystem.h"
#include "MyArray.h"

//Object that stores all the data for the exosystems
MyArray<Exosystem> exosystems;
void readFile();
void outputData();

/*
The main function that starts this program
*/
int main()
{
	try
	{
		readFile();
		outputData();
	}
	catch (ValidationException exp)
	{
		cout << exp.getInfo();
	}
	return 0;
}

/*
Reads in data from the data file (which has been set as stdin) and fills the public array of Exosystems
*/
void readFile()
{
	string line;
	//Read the header line, but do nothing with it
	getline(cin, line);

	//Declare necessary data
	Exosystem currentSystem;
	string starName;
	char planetName;
	int numberOfPlanets;
	double msini, a, per, ecc, om, t0, k;
	bool hasSingleStar;
	Exoplanet currentPlanet;
	string message;

	//Step through each line in the data file (stdin) until there are no more lines
	int lineNumber = 0;
	while (getline(cin, line))
	{
		lineNumber++;

		//Break line up into an array on commas
		int startIndex = 0;
		int endIndex = 0;
		int count = 0;
		string info[10];

		for (unsigned int i = 0; i < line.length(); i++)
		{
			if (line[i] == ',')
			{
				endIndex = i;
				info[count] = line.substr(startIndex, endIndex - startIndex);
				count++;
				//skip comma
				startIndex = i + 1;
			}
		}
		//Get the section from the last comma to the end
		info[count] = line.substr(startIndex, line.length() - startIndex);

		//Validation
		if (count < 9)
		{
			throw ValidationException(lineNumber, "Less than ten data items");
		}
		if (info[0].at(info[0].length() - 2) != ' ')
		{
			throw ValidationException(lineNumber, "Name is not there or has more than one character");
		}
		if (info[0].length() < 1)
		{
			throw ValidationException(lineNumber, "Star name is blank");
		}
		if (info[1].length() < 1)
		{
			throw ValidationException(lineNumber, "Number of planets is blank");
		}
		if (info[9].length() < 1)
		{
			throw ValidationException(lineNumber, "Binary field is blank");
		}

		//Assign data to variables
		starName = info[0].substr(0, info[0].length() - 2);
		planetName = info[0].at(info[0].length() - 1);
		numberOfPlanets = stoi(info[1]);
		//For all fields that can be blank:
		//Set value to -1.0 if blank so that it does not cause errors and can be excluded from printing
		msini = info[2].length() > 0 ? stod(info[2]) : -1.0;
		a = info[3].length() > 0 ? stod(info[3]) : -1.0;
		per = info[4].length() > 0 ? stod(info[4]) : -1.0;
		ecc = info[5].length() > 0 ? stod(info[5]) : -1.0;
		om = info[6].length() > 0 ? stod(info[6]) : -1.0;
		t0 = info[7].length() > 0 ? stod(info[7]) : -1.0;
		k = info[8].length() > 0 ? stod(info[8]) : -1.0;
		hasSingleStar = info[9] == "0";

		if (starName != currentSystem.getStarName())
		{
			//Encountered new system at this line

			//For the first line, the values of currentSystem will have no meaning until currentSystem is given a value after this if block
			if (lineNumber > 1)
			{
				//Validate number of planets in current system
				if (currentSystem.getCurrentNumberOfPlanets() < currentSystem.getNumberOfPlanets())
				{
					throw ValidationException(lineNumber, "Less planets listed than specified");
				}
				exosystems.add(currentSystem);
			}

			//Create a new exosystem with the information on the current line
			currentSystem = Exosystem(starName, numberOfPlanets);
		}

		//Create and add the current planet to the current exosystem
		currentPlanet = Exoplanet(planetName, msini, a, per, ecc, om, t0, k);
		try
		{
			currentSystem.addPlanet(currentPlanet);
		}
		catch (ValidationException exp)
		{
			exp.setLineNumber(lineNumber);
			throw exp;
		}
	}

	//Add the last system
	if (currentSystem.getCurrentNumberOfPlanets() < currentSystem.getNumberOfPlanets())
	{
		//Too few planets
		throw ValidationException(lineNumber, "Less planets listed than specified");
	}
	exosystems.add(currentSystem);

	return;
}

/*
Step through all exosystems and print out their info
*/
void outputData()
{
	//Step through all exosystems and print out their info
	int i;
	for (i = 0; i < exosystems.length(); i++)
	{
		exosystems.at(i).printExosystem();
	}
}