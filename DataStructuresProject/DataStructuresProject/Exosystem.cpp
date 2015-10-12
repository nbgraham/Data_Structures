#include <string>
#include <iostream>

using namespace std;

#include "ValidationException.h"
#include "Exosystem.h"
#include "Exoplanet.h"

Exosystem::Exosystem(void)
{
	starName = "";
	numberOfPlanets = 0;
	planets = new MyArray<Exoplanet>();
}

Exosystem::Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
	planets = new MyArray<Exoplanet>(_numberOfPlanets);
}

void Exosystem::addPlanet(Exoplanet _exoplanet)
{
	if (planets->length() == numberOfPlanets)
	{
		string message = "Exceeded number of planets in " + starName + " system";
		throw ValidationException(message);
	}

	if (planets->indexOf(_exoplanet) >= 0)
	{
		string planetName = { _exoplanet.getName() };
		string message = "Planet name " + planetName + " is not unique within the system " + starName;
		throw ValidationException(message);
	}

	planets->add(_exoplanet);
}

double Exosystem::calculateAverageMsini(void)
{
	double sum = 0;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		sum += planets->at(i).getMsini();
	}

	return sum / numberOfPlanets;

}

double Exosystem::calculateMaxPer(void)
{
	//The orbital period of the planet in days will always be positive so the minimum value is 0
	double max = 0;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets->at(i).getPer();
		if (per > max)
		{
			max = per;
		}
	}

	return max;
}

double Exosystem::calculateMinPer(void)
{
	//Set to the largest possible double
	double min = DBL_MAX;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets->at(i).getPer();
		if (per < min)
		{
			min = per;
		}
	}

	return min;
}

void Exosystem::printExosystem(void)
{
	cout << starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	cout << "\n";

	int i;
	for (i = 0; i < numberOfPlanets; i++)
	{
		planets->at(i).printPlanet();
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
		result += planets->at(i).toString();
		result += "\n";
	}
	//Two line space between systems
	result += "\n\n";
	return result;
}

bool Exosystem::operator==(Exosystem otherExosystem)
{
	if (starName == otherExosystem.getStarName())
	{
		return true;
	}

	return false;
}