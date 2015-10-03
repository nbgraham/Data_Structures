#pragma once
#include <string>
using namespace std;

#include "Exoplanet.h"
#include "MyArray.h"


class Exosystem
{
private:
	string starName;
	bool hasSingleStar;
	int numberOfPlanets;
	MyArray<Exoplanet> planets;

public:
	Exosystem();
	Exosystem(string _starName, int _numberOfPlanets);
	string getStarName(void) const { return starName; };
	bool getHasSingleStar(void) const { return hasSingleStar; };
	int getNumberOfPlanets(void) const { return numberOfPlanets; };
	int getCurrentNumberOfPlanets(void) const { return planets.length(); };
	MyArray<Exoplanet> getPlanets(void) const { return planets; };
	void addPlanet(Exoplanet& _exoplanet);
	double calculateAverageMsini(void) const;
	double calculateMaxPer(void) const;
	double calculateMinPer(void) const;
	void printExosystem(void);
	bool operator==(Exosystem otherExosystem);
};

