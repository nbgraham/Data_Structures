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
	Exoplanet();
	Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k);

	char getName(void) { return name; };
	double getMsini(void) { return msini; };
	double getA(void) { return a; };
	double getPer(void) { return per; };
	double getEcc(void) { return ecc; };
	double getOm(void) { return om; };
	double getT0(void) { return t0; };
	double getK(void) { return k; };

	void setName(char _name) { name = _name; };
	void setA(double _a) { a = _a; };
	void setPer(double _per) { per = _per; };
	void setECC(double _ecc) { ecc = _ecc; };
	void setOm(double _om) { om = _om; };
	void setT0(double _t0) { t0 = _t0; };
	void setK(double _k) { k = _k; };

	void printPlanet(void);
	string toString(void);
	bool operator==(Exoplanet& otherPlanet);
	int compare(Exoplanet& otherPlanet, char sortingKey);
	friend std::ostream& operator<<(std::ostream& os, Exoplanet& exoplanet)
	{
		os << exoplanet.toString();
		return os;
	};
};