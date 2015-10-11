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
#include "MyArray.h"

//Object that stores all the data for the exosystems
MyArray<Exosystem> exosystems;
char isSortedOnKey = 0;

void readFile(string inputFileName);
void outputData();
bool dataManipulationLoop();

Exoplanet search(char userChoice);
Exoplanet search(Exoplanet& key, char sortingKey);
Exoplanet searchSystem(Exoplanet& key, Exosystem& system, char sortingKey);
Exoplanet searchSystem(Exoplanet& key, string starName, char sortingKey);
Exoplanet binarySystemSearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey);
Exoplanet linearSystemSearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey);

void sort(char userChoice);
void quickSort(MyArray<Exoplanet>& arr, int left, int right, char sortingKey);

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
		readFile("test.csv");
		while (dataManipulationLoop()) {};
	}
	catch (ValidationException exp)
	{
		cout << exp.getInfo();
	}
	return 0;
}

/*
Reads in data from the data file and fills the public array of Exosystems
*/
void readFile(string inputFileName)
{
	ifstream inputData;
	inputData.open(inputFileName);

	string line;
	//Read the header line, but do nothing with it
	getline(inputData, line);

	//Declare necessary data
	Exosystem currentSystem;
	string starName;
	char planetName;
	int numberOfPlanets;
	double msini, a, per, ecc, om, t0, k;
	bool hasSingleStar;
	Exoplanet currentPlanet;
	string message;
	bool hasAllInfo;

	//Step through each line in the data file until there are no more lines
	int lineNumber = 0;
	while (getline(inputData, line))
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

		//Data validation
		hasAllInfo = true;
		if (count < 9)
		{
			hasAllInfo = false;
			//throw ValidationException(lineNumber, "Less than ten data items");
		}
		if (info[0].at(info[0].length() - 2) != ' ')
		{
			hasAllInfo = false;
			//throw ValidationException(lineNumber, "Name is not there or has more than one character");
		}
		for (int i = 0; i < count; i++)
		{
			if (info[i].length() < 1)
			{
				//A field is blank
				hasAllInfo = false;
			}
		}

		//Exosystem info
		starName = info[0].substr(0, info[0].length() - 2);
		hasSingleStar = info[9] == "0";
		numberOfPlanets = stoi(info[1]);
		if (starName != currentSystem.getStarName()) //Encountered new system at this line
		{
			//For the first line, the values of currentSystem will have no meaning until currentSystem is given a value after this if block
			if (lineNumber > 1)
			{
				//Validate number of planets in current system
				if (currentSystem.getCurrentNumberOfPlanets() == currentSystem.getNumberOfPlanets())
				{
					exosystems.add(currentSystem);
				}
			}

			//Create a new exosystem with the information on the current line
			currentSystem = Exosystem(starName, numberOfPlanets, hasSingleStar);
		}

		//Exoplanet info
		if (hasAllInfo) //All information for planet is present
		{
			planetName = info[0].at(info[0].length() - 1);
			msini = stod(info[2]);
			a = stod(info[3]);
			per = stod(info[4]);
			ecc = stod(info[5]);
			om = stod(info[6]);
			t0 = stod(info[7]);
			k = stod(info[8]);

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
	}

	//Add the last system if it has the right number of planets
	if (currentSystem.getCurrentNumberOfPlanets() == currentSystem.getNumberOfPlanets())
	{
		exosystems.add(currentSystem);
	}

	inputData.close();
	//Causing exception on array destructor
	//delete &currentSystem;
}

/*
Step through all exosystems and print out their info
*/
void outputData()
{
	//Step through all exosystems and print out their info
	for (int i = 0; i < exosystems.length(); i++)
	{
		cout << exosystems.at(i);
	}
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
		outputData();
	}
	else if (userChoice == 'S')
	{
		//Sort
		cout << "Choose a value to sort by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		userChoice = cin.get();
		cin.ignore();

		sort(userChoice);
	}
	else if (userChoice == 'F')
	{
		//Find
		cout << "Choose a value to search by:\n" << "'N' for name, "
			<< "'M' for msini, 'A' for a, 'P' for per, 'E' for ecc, 'O' for om, 'T' for T0, or 'K' for k\n";
		userChoice = cin.get();
		cin.ignore();

		Exoplanet result = search(userChoice);

		if (result.getName() == 0)
		{
			cout << "Planet not found\n";
		}
		else
		{
			cout << result.toString() << "\n";
		}
	}
	else if (userChoice == 'E')
	{
		return false;
	}

	return true;
}

void sort(char userChoice)
{
	//Loop through all systems and sort each list of planets
	MyArray<Exoplanet> planets;
	for (int i = 0; i < exosystems.length(); i++)
	{
		planets = exosystems[i].getPlanets();
		quickSort(planets, 0, planets.length() - 1, userChoice);
	}
	isSortedOnKey = userChoice;
}

Exoplanet search(char userChoice)
{
	Exoplanet searchValue;
	string key;
	string input;
	double value;
	if (userChoice == 'N')
	{
		cout << "Input the name to search by: ";
		getline(cin, input);

		//Validate name
		if (input.length() < 2 || input.at(input.length() - 2) != ' ' || input.at(input.length() - 1) == ' ')
		{
			//Name is not in correct format, return to data manipulation loop
			return Exoplanet();
		}

		searchValue = Exoplanet(input.at(input.length() - 1), 0, 0, 0, 0, 0, 0, 0);
		return searchSystem(searchValue, input.substr(0, input.length() - 2), userChoice);
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
			return Exoplanet();
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

		return search(searchValue, userChoice);
	}

	return Exoplanet();
}

Exoplanet search(Exoplanet& key, char sortingKey)
{
	Exoplanet result;
	for (int i = 0; i < exosystems.length(); i++)
	{
		result = searchSystem(key, exosystems.at(i), sortingKey);
		if (result.getName() != 0)
		{
			return result;
		}
	}
	return Exoplanet();
}

Exoplanet searchSystem(Exoplanet& key, string starName, char sortingKey)
{
	for (int i = 0; i < exosystems.length(); i++)
	{
		if (starName == exosystems[i].getStarName())
		{
			return searchSystem(key, exosystems[i], sortingKey);
		}
	}
	return Exoplanet();
}

Exoplanet searchSystem(Exoplanet& key, Exosystem& system, char sortingKey)
{
	MyArray<Exoplanet> planets = system.getPlanets();
	if (isSortedOnKey == sortingKey)
	{
		return binarySystemSearch(key, planets, sortingKey);
	}
	else
	{
		return linearSystemSearch(key, planets, sortingKey);
	}
}

Exoplanet binarySystemSearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey)
{
	int mid = 0;
	int left = 0;
	int right = planets.length() - 1;

	while (left < right)
	{
		mid = (left + right) / 2;

		if (key.compare(planets[mid], sortingKey) < 0)
		{
			right = mid - 1;
		}
		else if (key.compare(planets[mid], sortingKey) > 0)
		{
			left = mid + 1;
		}
		else
		{
			return planets[mid];
		}
	}

	return Exoplanet();
}

Exoplanet linearSystemSearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey)
{
	for (int j = 0; j < planets.length(); j++)
	{
		if (key.compare(planets[j], sortingKey) == 0)
		{
			return planets[j];
		}
	}
	return Exoplanet();
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

/*
Adapted from:
http://www.algolist.net/Algorithms/Sorting/Quicksort
*/
void quickSort(MyArray<Exoplanet>& arr, int left, int right, char sortingKey)
{
	int i = left, j = right;
	Exoplanet pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		//while (arr[i] < pivot)
		while (arr[i].compare(pivot, sortingKey) < 0)
			i++;
		//while (arr[j] > pivot)
		while (arr[j].compare(pivot, sortingKey) > 0)
			j--;
		if (i <= j) {
			arr.swap(i, j);
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, left, j, sortingKey);
	if (i < right)
		quickSort(arr, i, right, sortingKey);
}