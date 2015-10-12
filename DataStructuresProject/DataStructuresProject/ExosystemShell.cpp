#include <string>
#include <iostream>

using namespace std;

#include "ValidationException.h"
#include "ExosystemShell.h"
#include "Exoplanet.h"

ExosystemShell::ExosystemShell(void)
{
	starName = "";
	numberOfPlanets = 0;
	allPlanets = nullptr;
}

ExosystemShell::ExosystemShell(string _starName, int _numberOfPlanets, bool _hasSingleStar, MyArray<Exoplanet>* _planets)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
	allPlanets = _planets;
}

void ExosystemShell::addPlanetIndex(int indexOfPlanet)
{
	if (planetIndices.length() == numberOfPlanets)
	{
		string message = "Exceeded number of planets in " + starName + " system";
		throw ValidationException(message);
	}

	if (planetIndices.indexOf(indexOfPlanet) >= 0)
	{
		string message = "Planet is not unique within the system " + starName;
		throw ValidationException(message);
	}

	planetIndices.add(indexOfPlanet);
}

double ExosystemShell::calculateAverageMsini(void)
{
	double sum = 0;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		sum += allPlanets->at(i).getMsini();
	}

	return sum / numberOfPlanets;

}

double ExosystemShell::calculateMaxPer(void)
{
	//The orbital period of the planet in days will always be positive so the minimum value is 0
	double max = 0;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = allPlanets->at(i).getPer();
		if (per > max)
		{
			max = per;
		}
	}

	return max;
}

double ExosystemShell::calculateMinPer(void)
{
	//Set to the largest possible double
	double min = DBL_MAX;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = allPlanets->at(i).getPer();
		if (per < min)
		{
			min = per;
		}
	}

	return min;
}

void ExosystemShell::printExosystemShell(void)
{
	cout << starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	cout << "\n";

	int i;
	for (i = 0; i < numberOfPlanets; i++)
	{
		allPlanets->at(i).printPlanet();
		cout << "\n";
	}
	//Two line space between systems
	cout << "\n\n";
	return;
}

string ExosystemShell::toString(void)
{
	string result;
	result += starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	result += "\n";
	result += planetIndices.toString();
	return result;
}

bool ExosystemShell::operator==(ExosystemShell otherExosystemShell)
{
	if (starName == otherExosystemShell.getStarName())
	{
		return true;
	}

	return false;
}