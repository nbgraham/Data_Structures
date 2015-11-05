#pragma once

#include <string>
using namespace std;
#include "LinkedHashTable.h"
#include "Exoplanet.h"

class ExoplanetLHT : public LinkedHashTable<Exoplanet*, string>
{
protected:
	int hash(string key) override;
	string getKey(Exoplanet*& data) override;
public:
	ExoplanetLHT() : LinkedHashTable<Exoplanet*, string>() {};
	ExoplanetLHT(int buckets) : LinkedHashTable<Exoplanet*, string>(buckets) {};
};

string ExoplanetLHT::getKey(Exoplanet*& data)
{
	return data->getFullName();
}

inline int ExoplanetLHT::hash(string key)
{
	unsigned long hash = 5381;
	int c;

	for (unsigned int i = 0; i < key.length(); ++i)
	{
		c = key[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash%buckets;
}
