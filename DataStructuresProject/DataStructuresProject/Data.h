#pragma once
#include <iostream>
#include <fstream>

#include "Exoplanet.h"
#include "Exosystem.h"
#include "MyArray.h"
#include "ValidationException.h"

class Data
{
private:
	MyArray<Exosystem>* exosystems;
	MyArray<Exoplanet>* planets;
	char isSortedOnKey;
public:
	Data()
	{
		isSortedOnKey = 0;
		planets = new MyArray<Exoplanet>();
		exosystems = new MyArray <Exosystem>();
	}
	~Data() { cout << "Data destructor called\n"; };

	void outputData(ostream& os)
	{
		//Step through all exosystems and print out their info
		for (int i = 0; i < exosystems->length(); i++)
		{
			os << exosystems->at(i);
		}
	};

	string toString(void)
	{
		string result = "";
		//Step through all exosystems and print out their info
		for (int i = 0; i < exosystems->length(); i++)
		{
			result += exosystems->at(i).toString();
		}
		return result;
	};

	void sort(char userChoice)
	{
		quickSort(*planets, 0, planets->length() - 1, userChoice);
		isSortedOnKey = userChoice;
	};

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
	};

	Exosystem* search(Exoplanet& key, char sortingKey)
	{
		Exoplanet result;
		if (isSortedOnKey == sortingKey)
		{
			result = binarySearch(key, *planets, sortingKey);
		}
		else
		{
			result = linearSearch(key, *planets, sortingKey);
		}

		Exosystem* resultP = result.getSystemPointer();
		return resultP;
	};

	Exoplanet binarySearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey)
	{
		int mid = 0;
		int left = 0;
		int right = planets.length() - 1;

		while (left <= right)
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
	};

	Exoplanet linearSearch(Exoplanet& key, MyArray<Exoplanet>& planets, char sortingKey)
	{
		for (int j = 0; j < planets.length(); j++)
		{
			if (key.compare(planets[j], sortingKey) == 0)
			{
				return planets[j];
			}
		}
		return Exoplanet();
	};
	/*
	Reads in data from the data file and fills the public array of Exosystems
	*/
	void addDataFromFile(string inputFileName)
	{
		ifstream inputData;
		inputData.open(inputFileName);

		string line;
		//Read the header line, but do nothing with it
		getline(inputData, line);

		//Declare necessary data
		Exosystem* currentSystem = nullptr;
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
	
			if (currentSystem == nullptr || starName != currentSystem->getStarName()) //Encountered new system at this line
			{
				//For the first line, the values of currentSystem will have no meaning until currentSystem is given a value after this if block
				if (lineNumber > 1)
				{
					//Validate number of planets in current system
					if (currentSystem->getCurrentNumberOfPlanets() == currentSystem->getNumberOfPlanets())
					{
						exosystems->add(*currentSystem);
					}
				}

				//Create a new exosystem with the information on the current line
				currentSystem = new Exosystem(starName, numberOfPlanets, hasSingleStar);
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
				currentPlanet = Exoplanet(planetName, msini, a, per, ecc, om, t0, k, currentSystem, currentSystem->getStarName());
				try
				{
					currentSystem->addPlanet(currentPlanet);
					planets->add(currentPlanet);
				}
				catch (ValidationException exp)
				{
					exp.setLineNumber(lineNumber);
					throw exp;
				}
			}
		}

		//Add the last system if it has the right number of planets
		if (currentSystem->getCurrentNumberOfPlanets() == currentSystem->getNumberOfPlanets())
		{
			exosystems->add(*currentSystem);
		}

		inputData.close();

		return;
	};
};