#pragma once
#include <string>
using namespace std;

#include "MyArray.h"
#include "Exoplanet.h"


class Exosystem
{
private:
	string starName;
	bool hasSingleStar;
	int numberOfPlanets;
	MyArray<Exoplanet> planets;
public:
	//Constructors
	/*
	Default constructor
	*/
	Exosystem();
	/*
	Constructor that sets the values of exosystem
	*/
	Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar);

	//Accessors
	string getStarName(void) { return starName; };
	bool getHasSingleStar(void) { return hasSingleStar; };
	int getNumberOfPlanets(void) { return numberOfPlanets; };
	int getCurrentNumberOfPlanets(void) { return planets.length(); };
	MyArray<Exoplanet> getPlanets(void) { return planets; };

	//Mutators
	void setStarName(string _starName) { starName = _starName; };
	void setHasSingleStar(bool _single) { hasSingleStar = _single; };
	void setNumberOfPlanets(int number) { numberOfPlanets = number; };

	/*
	Validates that the system has not reached its specified number of planets and _exoplanet is unique in the system
	Then adds the planet to the list of planets
	@param _exoplanet	the planet to be added
	*/
	void addPlanet(Exoplanet _exoplanet);
	/*
	Iterates over the planets in this system and calculates the average msini
	*/
	double calculateAverageMsini(void);
	/*
	Iterates over the planets in this system and calculates the max per
	*/
	double calculateMaxPer(void);
	/*
	Iterates over the planets in this system and calculates the average msini
	*/
	double calculateMinPer(void);
	/*
	Prints an exosystem summary and then iterates over all the planets, calling their print methods
	*/
	void printExosystem(void);
	/*
	Returns a string representation of the Exosystem, calling the toString method on all its planets
	*/
	string toString(void);
	/*
	Overrides the == operator for searching through MyArray<Exosystem>. Compares solely on starName
	@param otherExosystem	the system to compare this to
	*/
	bool operator==(Exosystem otherExosystem);
	/*
	Prints the string representation of the specified exosystem to the os output stream
	*/
	friend ostream& operator<<(ostream& os, Exosystem& exosystem)
	{
		os << exosystem.toString();
		return os;
	};
};

