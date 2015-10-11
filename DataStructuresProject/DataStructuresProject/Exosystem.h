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
	Exosystem();
	Exosystem(string _starName, int _numberOfPlanets, bool _hasSingleStar);

	string getStarName(void) { return starName; };
	bool getHasSingleStar(void) { return hasSingleStar; };
	int getNumberOfPlanets(void) { return numberOfPlanets; };
	int getCurrentNumberOfPlanets(void) { return planets.length(); };
	MyArray<Exoplanet> getPlanets(void) { return planets; };

	void setStarName(string _starName) { starName = _starName; };
	void setHasSingleStar(bool _single) { hasSingleStar = _single; };
	void setNumberOfPlanets(int number) { numberOfPlanets = number; };

	void addPlanet(Exoplanet _exoplanet);
	double calculateAverageMsini(void);
	double calculateMaxPer(void);
	double calculateMinPer(void);
	void printExosystem(void);
	string toString(void);
	bool operator==(Exosystem otherExosystem);
	friend ostream& operator<<(ostream& os, Exosystem& exosystem)
	{
		os << exosystem.toString();
		return os;
	};
};

