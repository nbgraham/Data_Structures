#include <string>
#include <iostream>

using namespace std;

#include "ValidationException.h"
#include "Exosystem.h"
#include "Exoplanet.h"

//Constructors
/*
Default constructor
*/
Exosystem::Exosystem(void)
{
	starName = "";
	numberOfPlanets = 0;
}

/*
Constructor that sets the values of exosystem
*/
Exosystem::Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
}

/*
Validates that the system has not reached its specified number of planets and _exoplanet is unique in the system
Then adds the planet to the list of planets
@param _exoplanet	the planet to be added
*/
void Exosystem::addPlanet(Exoplanet _exoplanet)
{
	if (planets.length() == numberOfPlanets)
	{
		string message = "Exceeded number of planets in " + starName + " system";
		throw ValidationException(message);
	}

	if (planets.indexOf(_exoplanet) >= 0)
	{
		string planetName = { _exoplanet.getName() };
		string message = "Planet name " + planetName + " is not unique within the system " + starName;
		throw ValidationException(message);
	}

	planets.add(_exoplanet);
}

/*
Iterates over the planets in this system and calculates the average msini
*/
double Exosystem::calculateAverageMsini(void)
{
	double sum = 0;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		sum += planets.at(i).getMsini();
	}

	return sum / numberOfPlanets;

}

/*
Iterates over the planets in this system and calculates the max per
*/
double Exosystem::calculateMaxPer(void)
{
	//The orbital period of the planet in days will always be positive so the minimum value is 0
	double max = 0;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets.at(i).getPer();
		if (per > max)
		{
			max = per;
		}
	}

	return max;
}

/*
Iterates over the planets in this system and calculates the average msini
*/
double Exosystem::calculateMinPer(void)
{
	//Set to the largest possible double
	double min = DBL_MAX;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets.at(i).getPer();
		if (per < min)
		{
			min = per;
		}
	}

	return min;
}

/*
Prints an exosystem summary and then iterates over all the planets, calling thier print methods
*/
void Exosystem::printExosystem(void)
{
	cout << starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	cout << "\n";

	int i;
	for (i = 0; i < numberOfPlanets; i++)
	{
		planets.at(i).printPlanet();
		cout << "\n";
	}
	//Two line space between systems
	cout << "\n\n";
	return;
}

string Exosystem::toString(void)
{
	string result;
	result += starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	result += "\n";

	int i;
	for (i = 0; i < numberOfPlanets; i++)
	{
		result += planets.at(i).toString();
		result += "\n";
	}
	//Two line space between systems
	result += "\n\n";
	return result;
}

/*
Overrides the == operator for searching through MyArray<Exosystem>. Compares solely on starName
@param otherExosystem	the system to compare this to
*/
bool Exosystem::operator==(Exosystem otherExosystem)
{
	if (starName == otherExosystem.getStarName())
	{
		return true;
	}

	return false;
}