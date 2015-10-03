#include <string>
#include <iostream>
using namespace std;

#include "Exoplanet.h"

//Constructors
/*
Default constructor sets values to 0
*/
Exoplanet::Exoplanet()
{
	name = 0;
	msini = 0.0;
	a = 0.0;
	per = 0.0;
	ecc = 0.0;
	om = 0.0;
	t0 = 0.0;
	k = 0.0;
}

/*
Constructor that sets all the values of the planet
*/
Exoplanet::Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k)
{
	name = _name;
	msini = _msini;
	a = _a;
	per = _per;
	ecc = _ecc;
	om = _om;
	t0 = _t0;
	k = _k;
}

//Methods
/*
Prints the information of the planet in comma separated format
*/
void Exoplanet::printPlanet(void)
{
	string planetName = { name };
	cout << planetName + ",";

	//Only include the value if they are positive
	//Reading in the file has set these values to -1.0 if no value was given
	if (msini > 0)
	{
		cout << to_string(msini);
	}
	cout << ",";
	if (a > 0)
	{
		cout << to_string(a);
	}
	cout << ",";
	if (per > 0)
	{
		cout << to_string(per);
	}
	cout << ",";
	if (ecc > 0)
	{
		cout << to_string(ecc);
	}
	cout << ",";
	if (om > 0)
	{
		cout << to_string(om);
	}
	cout << ",";
	if (t0 > 0)
	{
		cout << to_string(t0);
	}
	cout << ",";
	if (k > 0)
	{
		cout << to_string(k);
	}

	return;
}

/*
Overrides the == operator for searching through MyArray<Exoplanet>. Compares solely on planetName
@param otherPlanet	the planet to compare this to
*/
bool Exoplanet::operator==(Exoplanet& otherPlanet)
{
	if (name == otherPlanet.name)
	{
		return true;
	}

	return false;
}