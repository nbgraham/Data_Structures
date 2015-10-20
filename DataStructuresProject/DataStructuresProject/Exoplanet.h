#pragma once
#include <string>
#include <iostream>
using namespace std;

class Exosystem;

class Exoplanet
{
private:
	char name;
	double msini;
	double a;
	double per;
	double ecc;
	double om;
	double t0;
	double k;
	Exosystem* system;
	string starName;
public:
	//Constructors
	/*
	Default constructor sets values to 0
	*/
	Exoplanet();
	Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k);
	/*
	Constructor that sets all the values of the planet
	*/
	Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k, Exosystem* _system, string _starName);
	/*
	Empty destructor
	*/
	~Exoplanet() {};

	//Accessors
	char getName(void) const { return name; };
	double getMsini(void) const { return msini; };
	double getA(void) const { return a; };
	double getPer(void) const { return per; };
	double getEcc(void) const { return ecc; };
	double getOm(void) const { return om; };
	double getT0(void) const { return t0; };
	double getK(void) const { return k; };
	Exosystem* getSystemPointer(void) const	{ return system; };
	string getFullName(void) const;

	//Mutators
	void setName(char _name) { name = _name; };
	void setA(double _a) { a = _a; };
	void setPer(double _per) { per = _per; };
	void setECC(double _ecc) { ecc = _ecc; };
	void setOm(double _om) { om = _om; };
	void setT0(double _t0) { t0 = _t0; };
	void setK(double _k) { k = _k; };
	void setSystemPointer(Exosystem* ptr) { system = ptr; };

	/*
	Returns a string representation of this planet
	*/
	string toString(void) const;
	/*
	Overrides the == operator for searching through Array<Exoplanet>. Compares solely on planetName
	@param otherPlanet	the planet to compare this to
	*/
	bool operator==(Exoplanet& otherPlanet);
	bool operator<(Exoplanet& otherPlanet);
	bool operator>(Exoplanet& otherPlanet);
	/*
	Compares this planet with otherPlanet based on the sortingKey value
	Returns -1 if this comes before
	Returns 1 if this comes aftet
	Returns 0 if this and otherPlanet are equal
	*/
	int compare(Exoplanet& otherPlanet, char sortingKey);
	/*
	Prints the string representation of the specified exoplanet to the os output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, Exoplanet& exoplanet)
	{
		os << exoplanet.toString();
		return os;
	};
};