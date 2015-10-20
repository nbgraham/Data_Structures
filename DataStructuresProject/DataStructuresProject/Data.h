#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#include "Exoplanet.h"
#include "Exosystem.h"
#include "Array.h"
#include "LinkedList.h"

class Data
{
private:
	LinkedListPtrs<Exosystem>* exosystems;
	Array<Exoplanet*>* planets;
	char isSortedOnKey;
	bool isEmpty;
public:
	/*
	Default constructor
	allocates the two arrays in this object
	*/
	Data();
	/*
	Destructor
	deletes the two array in this object
	*/
	~Data();

	bool IsEmpty(void) {return isEmpty;};
	/*
	Reads in data from the data file and fills both arrays in this object
	*/
	void changeDataFromFile(string inputFileName, char type);
	/*
	Adds the specified Exoplanet point to the specified system in the exosystems array in this object
	Adds the specified Exoplanet pointer to the list of planets in this object
	*/
	void addPlanetToSystem(Exoplanet* planet, Exosystem* system, char type);
	void removePlanetFromSystem(Exoplanet* planet, Exosystem* system);

	/*
	Sorts the list of planets based on the selected key
	*/
	void sort(char userChoice);
	/*
	Adapted from:
	http://www.algolist.net/Algorithms/Sorting/Quicksort
	*/
	void quickSort(Array<Exoplanet*>& arr, int left, int right, char sortingKey);
	/*
	Searches through the planets array for a planet that has an equal specified key (sortingKey) as the Exoplanet key
	Returns a pointer to the system that the found planet is in
	Returns nullptr if no planet is found
	*/
	Exosystem* search(Exoplanet& key, char sortingKey) const;
	/*
	Implements a binary search
	*/
	Exoplanet* binarySearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const;
	/*
	Implements a linear search
	*/
	Exoplanet* linearSearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const;
	/*
	Returns a string representation of this object
	*/
	string toString(void) const;
};

	