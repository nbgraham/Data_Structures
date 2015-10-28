/*
Uses quicksort adapted from: http://www.algolist.net/Algorithms/Sorting/Quicksort
*/

#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#include "Exoplanet.h"
#include "Exosystem.h"
#include "Array.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"

class Data
{
private:
	LinkedList<Exosystem>* exosystems;
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
	Reads in data from the data file and changes the data based on the type parameter
	type A: adds all items in data file
	type M: merge, updates existing items
	type P: purge, removes all items in the data file from the data
	*/
	void changeDataFromFile(string inputFileName, char type);
	/*
	Add or merges (Depending on the type) the specified planet to the specified system and the master array of planets
	*/
	void addPlanetToSystem(Exoplanet* planet, Exosystem* system, char type);
	/*
	Removes the specified planet form the specified system and the master array of planets
	*/
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

	