#include "Exosystem.h"

Exosystem::Exosystem(void)
{
	starName = "";
	numberOfPlanets = 0;
	planets = new LinkedList<Exoplanet>();
}

Exosystem::Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar)
{
	starName = _starName;
	numberOfPlanets = _numberOfPlanets;
	hasSingleStar = _hasSingleStar;
	planets = new LinkedList<Exoplanet>();
}

Exosystem::Exosystem(const Exosystem & other)
{
	starName = other.getStarName();
	hasSingleStar = other.getHasSingleStar();
	numberOfPlanets = other.getNumberOfPlanets();
	planets = new LinkedList<Exoplanet>(other.getPlanets());
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
		throw ExosystemTooManyPlanetsException();
	}

	if (nameExists(_exoplanet->getName()))
	{
		throw ExosystemPlanetNameNotUniqueException();
	}

	planets->add(*_exoplanet);
}

void Exosystem::removePlanet(Exoplanet* _exoplanet)
{
	planets->remove(*_exoplanet);
}

double Exosystem::calculateAverageMsini(void) const
{
	double sum = 0;
	Node<Exoplanet>* curr = planets->getHead();
	while (curr != nullptr)
	{
		sum += curr->data.getMsini();
		curr = curr->next;
	}

	return sum / planets->size();
}

double Exosystem::calculateMaxPer(void) const
{
	double maxPer = 0;
	double currPer;
	Node<Exoplanet>* curr = planets->getHead();
	while (curr != nullptr)
	{
		currPer = curr->data.getPer();
		if (currPer > maxPer)
		{
			maxPer = currPer;
		}
		curr = curr->next;
	}

	return maxPer;
}

double Exosystem::calculateMinPer(void) const
{
	double minPer = DBL_MAX;
	double currPer;
	Node<Exoplanet>* curr = planets->getHead();
	while (curr != nullptr)
	{
		currPer = curr->data.getPer();
		if (currPer < minPer)
		{
			minPer = currPer;
		}
		curr = curr->next;
	}

	return minPer;
}
string Exosystem::systemDataString(void) const
{
	return starName + "," + to_string(numberOfPlanets) + "," + to_string(calculateAverageMsini()) + "," + to_string(calculateMaxPer()) + "," + to_string(calculateMinPer());
}

string Exosystem::toString(void) const
{
	string result;
	result += systemDataString();
	result += "\n";

	LinkedListIterator<Exoplanet> it = LinkedListIterator<Exoplanet>(planets);
	while (it.hasNext())
	{
		result += it.getNext()->toString() + "\n";
	}

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
	Node<Exoplanet>* curr = planets->getHead();
	while (curr != nullptr)
	{
		if (curr->data.getName() == name) return true;
		curr = curr->next;
	}
	return false;
}

void Exosystem::overwritePlanet(Exoplanet* planet)
{
	Node<Exoplanet>* curr = planets->getHead();
	while (curr != nullptr)
	{
		if (curr->data.getName() == planet->getName())
		{
			curr->data = *planet;
			break;
		}
		curr = curr->next;
	}
	if (curr == nullptr) throw ExosystemPlanetNotFoundException();
}