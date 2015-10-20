#include "Exosystem.h"

Exosystem::Exosystem(void)
{
	starName = "";
	numberOfPlanets = 0;
	planets = new PlanetPointerLinkedList();
}

Exosystem::Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
	planets = new PlanetPointerLinkedList();
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

void Exosystem::overwritePlanet(Exoplanet* _exoplanet)
{
	planets->overwritePlanet(_exoplanet);
}

void Exosystem::removePlanet(Exoplanet* _exoplanet)
{
	planets->removePlanet(_exoplanet);
}

double Exosystem::calculateAverageMsini(void) const
{
	return planets->calculateAverageMsini();
}

double Exosystem::calculateMaxPer(void) const
{
	return planets->calculateMaxPer();
}

double Exosystem::calculateMinPer(void) const
{
	return planets->calculateMinPer();
}

string Exosystem::toString(void) const
{
	string result;
	result += starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
	result += "\n";

	result += planets->toString();

	//Two line space between systems
	result += "\n";
	return result;
}

bool Exosystem::operator==(Exosystem& otherExosystem) const
{
	return starName == otherExosystem.getStarName();
}

bool Exosystem::operator!=(Exosystem& otherExosystem) const
{
	return starName != otherExosystem.getStarName();
}

bool Exosystem::operator<(Exosystem& otherExosystem) const
{
	return starName < otherExosystem.getStarName();
}

bool Exosystem::operator>(Exosystem& otherExosystem) const
{
	return starName > otherExosystem.getStarName();
}

bool Exosystem::nameExists(char name) const
{
	return planets->nameExists(name);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         