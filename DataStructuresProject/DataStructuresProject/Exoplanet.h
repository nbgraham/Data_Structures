#pragma once
using namespace std;

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
public:
	//Constructors
	/*
	Default constructor sets values to 0
	*/
	Exoplanet();
	/*
	Constructor that sets all the values of the planet
	*/
	Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k);

	//Accessors
	char getName(void) { return name; };
	double getMsini(void) { return msini; };
	double getA(void) { return a; };
	double getPer(void) { return per; };
	double getEcc(void) { return ecc; };
	double getOm(void) { return om; };
	double getT0(void) { return t0; };
	double getK(void) { return k; };

	//Mutators
	void setName(char _name) { name = _name; };
	void setA(double _a) { a = _a; };
	void setPer(double _per) { per = _per; };
	void setECC(double _ecc) { ecc = _ecc; };
	void setOm(double _om) { om = _om; };
	void setT0(double _t0) { t0 = _t0; };
	void setK(double _k) { k = _k; };

	/*
	Prints the information of the planet in comma separated format
	*/
	void printPlanet(void);
	/*
	Returns a string representation of this planet
	*/
	string toString(void);
	/*
	Overrides the == operator for searching through MyArray<Exoplanet>. Compares solely on planetName
	@param otherPlanet	the planet to compare this to
	*/
	bool operator==(Exoplanet& otherPlanet);
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