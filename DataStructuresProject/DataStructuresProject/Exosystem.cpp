#include "Exosystem.h"

Exosystem::Exosystem(void)
{
	starName = "";
	numberOfPlanets = 0;
	planets = new Array<Exoplanet*>();
}

Exosystem::Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
	planets = new Array<Exoplanet*>(_numberOfPlanets);
}

Exosystem::~Exosystem()
{
	if (planets != nullptr)
	{
		delete planets;
		planets = nullptr;
	}
}

void Exosystem::addPlanet(Exoplanet* _exoplanet)
{
	if (planets->size() == numberOfPlanets)
	{
		throw exception("Too many planets listed for this system.");
	}

	if (nameExists(_exoplanet->getName()))
	{
		throw exception("Planet name is not unique within the system.");
	}

	planets->add(_exoplanet);
}

double Exosystem::calculateAverageMsini(void) const
{
	double sum = 0;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		sum += planets->at(i)->getMsini();
	}

	return sum / numberOfPlanets;

}

double Exosystem::calculateMaxPer(void) const
{
	//The orbital period of the planet in days will always be positive so the minimum value is 0
	double max = 0;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets->at(i)->getPer();
		if (per > max)
		{
			max = per;
		}
	}

	return max;
}

double Exosystem::calculateMinPer(void) const
{
	//Set to the largest possible double
	double min = DBL_MAX;
	double per;
	int i;

	for (i = 0; i < numberOfPlanets; ++i)
	{
		per = planets->at(i)->getPer();
		if (per < min)
		{
			min = per;
		}
	}

	return min;
}

string Exosystem::toString(void) const
{
	string result;
	result += starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	result += "\n";

	int i;
	for (i = 0; i < numberOfPlanets; i++)
	{
		result += planets->at(i)->toString();
		result += "\n";
	}
	//Two line space between systems
	result += "\n\n";
	return result;
}

bool Exosystem::operator==(Exosystem otherExosystem) const
{
	if (starName == otherExosystem.getStarName())
	{
		return true;
	}

	return false;
}

bool Exosystem::nameExists(char name) const
{
	for (int i = 0; i < planets->size(); i++)
	{
		if (planets->at(i)->getName() == name) return true;
	}

	return false;
}