#include "Exoplanet.h"

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
	system = nullptr;
	starName = "";
}

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
	system = nullptr;
	starName = "";
}

Exoplanet::Exoplanet(char _name, double _msini, double _a, double _per, double _ecc, double _om, double _t0, double _k, Exosystem* _system, string _starName)
{
	name = _name;
	msini = _msini;
	a = _a;
	per = _per;
	ecc = _ecc;
	om = _om;
	t0 = _t0;
	k = _k;
	system = _system;
	starName = _starName;
}

string Exoplanet::toString(void) const
{
	string result = { name };
	result += "," + to_string(msini) + "," + to_string(a) + "," + to_string(per) + "," + to_string(ecc) + "," + to_string(om) + ",";
	result += to_string(t0) + "," + to_string(k);
	return result;
}

bool Exoplanet::operator==(Exoplanet& otherPlanet)
{
	if (name == otherPlanet.name)
	{
		return true;
	}

	return false;
}

int Exoplanet::compare(Exoplanet& otherPlanet, char sortingKey)
{
	int result;
	string thisName;
	string otherName;

	switch (sortingKey)
	{
	case 'N':
		thisName = getFullName();
		otherName = otherPlanet.getFullName();

		if (thisName > otherName)
		{
			result = 1;
		}
		else if (thisName < otherName)
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'M':
		if (msini > otherPlanet.getMsini())
		{
			result = 1;
		}
		else if (msini < otherPlanet.getMsini())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'A':
		if (a > otherPlanet.getA())
		{
			result = 1;
		}
		else if (a < otherPlanet.getA())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'P':
		if (per > otherPlanet.getPer())
		{
			result = 1;
		}
		else if (per < otherPlanet.getPer())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'E':
		if (ecc > otherPlanet.getEcc())
		{
			result = 1;
		}
		else if (ecc < otherPlanet.getEcc())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'O':
		if (om > otherPlanet.getOm())
		{
			result = 1;
		}
		else if (om < otherPlanet.getOm())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'T':
		if (t0 > otherPlanet.getT0())
		{
			result = 1;
		}
		else if (t0 < otherPlanet.getT0())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	case 'K':
		if (k > otherPlanet.getK())
		{
			result = 1;
		}
		else if (k < otherPlanet.getK())
		{
			result = -1;
		}
		else
		{
			result = 0;
		}
		break;
	default:
		throw exception("Invalid choice.");
		result = 0;
		break;
	}

	return result;
}

string Exoplanet::getFullName(void) const
{
	if (starName.length() > 0)
	{
		return starName + " " + name;
	}
	else
	{
		return to_string(name);
	}
}