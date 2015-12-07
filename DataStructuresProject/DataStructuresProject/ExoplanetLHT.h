#pragma once

#include <string>
using namespace std;
#include "LinkedHashTable.h"
#include "Exoplanet.h"

class ExoplanetLHT : public LinkedHashTable<Exoplanet*, string>
{
protected:
	/*
	Hash function for hash table of exoplanets*/
	int hash(string key) override;
	/*
	Gets the key for the exoplanet (the full name) */
	string getKey(Exoplanet*& data) override {
		return data->getFullName();
	};
	/*
	Returns true if the two planets are equal (by name) */
	bool equal(Exoplanet*& data, Exoplanet*& other) override;
	/*
	Gets the name of this planet*/
	string getStringValue(Exoplanet*& data) override;
	/*
	Gets the exosystem and planet name for this planet*/
	string getFullStringValue(Exoplanet*& data) override;
public:
	/*
	Default constructor*/
	ExoplanetLHT() : LinkedHashTable<Exoplanet*, string>() {};
	/*
	Constructor that specifies the number of buckets*/
	ExoplanetLHT(int buckets) : LinkedHashTable<Exoplanet*, string>(buckets) {};
};

inline int ExoplanetLHT::hash(string key)
{
	unsigned long hash = 5381;
	int c;

	for (unsigned int i = 0; i < key.length(); ++i)
	{
		c = key[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash % buckets;
}

inline bool ExoplanetLHT::equal(Exoplanet *& data, Exoplanet *& other)
{
	return data->getFullName() == other->getFullName();
}

inline string ExoplanetLHT::getStringValue(Exoplanet *& data)
{
	return data->toString();
}

inline string ExoplanetLHT::getFullStringValue(Exoplanet *& data)
{
	return data->getSystemPointer()->systemDataString() + "\n" + data->toString();
}

