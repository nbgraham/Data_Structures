#pragma once

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
	Exoplanet();
	Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k);
	char getName(void) const { return name; };
	double getMsini(void) const { return msini; };
	double getA(void) const { return a; };
	double getPer(void) const { return per; };
	double getEcc(void) const { return ecc; };
	double getOm(void) const { return om; };
	double getT0(void) const { return t0; };
	double getK(void) const { return k; };
	void printPlanet(void);
	bool operator==(Exoplanet& otherPlanet);
};