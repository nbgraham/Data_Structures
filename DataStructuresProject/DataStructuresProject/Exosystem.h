#pragma once
#include <string>
#include <iostream>
#include <exception>

using namespace std;

#include "Exoplanet.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"

class ExosystemException : public exception {};
class ExosystemTooManyPlanetsException : public ExosystemException {};
class ExosystemPlanetNameNotUniqueException : public ExosystemException {};
class ExosystemPlanetNotFoundException : public ExosystemException {};

class Exosystem
{
private:
	string starName;
	bool hasSingleStar;
	int numberOfPlanets;
	LinkedList<Exoplanet>* planets;
public:
	/*
	Default constructor*/
	Exosystem();
	/*
	Constructor that sets the values of exosystem*/
	Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar);
	/*
	Copy constructor*/
	Exosystem(const Exosystem& other);
	/*
	Destructor
	Deletes the two arrays that were created in the constructor*/
	~Exosystem();

	//Accessors
	string getStarName(void) const { return starName; };
	bool getHasSingleStar(void) const { return hasSingleStar; };
	int getNumberOfPlanets(void) const { return numberOfPlanets; };
	int getCurrentNumberOfPlanets(void) const { return planets->size(); };
	LinkedList<Exoplanet>& getPlanets (void) const {return *planets; };

	//Mutators
	void setStarName(string _starName) { starName = _starName; };
	void setHasSingleStar(bool _single) { hasSingleStar = _single; };
	void setNumberOfPlanets(int number) { numberOfPlanets = number; };

	/*
	Validates that the system has not reached its specified number of planets and _exoplanet is unique in the system
	Then adds the planet to the list of planets
	@param _exoplanet	the planet to be added*/
	void addPlanet(Exoplanet* _exoplanet);
	/*
	Removes the specified planet from this systems planet list*/
	void removePlanet(Exoplanet* _exoplanet);
	/*
	Replaces the planet in the list of the same name with the specified planet*/
	void overwritePlanet(Exoplanet* planet);

	/*
	Iterates over the planets in this system and calculates the average msini*/
	double calculateAverageMsini(void) const;
	/*
	Iterates over the planets in this system and calculates the max per*/
	double calculateMaxPer(void) const;
	/*
	Iterates over the planets in this system and calculates the average msini*/
	double calculateMinPer(void) const;
	/*
	Returns a string representation of the Exosystem, calling the toString method on all its planets*/
	string toString(void) const;
	string systemDataString(void) const;
	/*
	Overrides the == operator for searching through Array<Exosystem>. Compares solely on starName
	@param otherExosystem	the system to compare this to*/
	bool operator==(Exosystem& otherExosystem) const;
	/*
	Compares on starName*/
	bool operator!=(Exosystem& otherExosystem) const;
	/*
	Compares on starName*/
	bool operator<(Exosystem& otherExosystem) const;
	/*
	Compares on starName*/
	bool operator>(Exosystem& otherExosystem) const;
	/*
	Returns true if there is a planet in this system with the specified name
	Else returns false*/
	bool nameExists(char name) const;
	/*
	Prints the string representation of the specified exosystem to the os output stream*/
	friend ostream& operator<<(ostream& os, Exosystem& exosystem)
	{
		os << exosystem.toString();
		return os;
	};
};

