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
#include "ExoplanetLHT.h"
#include "AVLTreeExosystem.h"
#include "AVLTreeIterator.h"
#include "ExosystemP.h"
#include "Debug.h"

class Data
{
private:
	ExoplanetLHT* hashTable;
	AVLTree<ExosystemP>* exosystems;
	Array<Exoplanet*>* planets;
	char isSortedOnKey;
	int numberOfReadPlanets;
	/*
	Adds the planet to the system
	Overwrites if already exists*/
	void merge(Exosystem* system, Exoplanet* planet);
	/*
	Adapted from:
	http://www.algolist.net/Algorithms/Sorting/Quicksort
	*/
	void quickSort(Array<Exoplanet*>& arr, int left, int right, char sortingKey);
	/*
	Implements a binary search
	*/
	Exoplanet* binarySearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const;
	/*
	Implements a linear search
	*/
	Exoplanet* linearSearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const;
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

	bool IsEmpty(void) {return numberOfReadPlanets == 0;};
	/*
	Reads in data from the data file and changes the data based on the type parameter
	type A: adds all items in data file
	type M: merge, updates existing items
	type P: purge, removes all items in the data file from the data
	*/
	void changeDataFromFile(string inputFileName, char type);
	/*
	Sorts the list of planets based on the selected key
	*/
	void sort(char userChoice);
	/*
	Searches through the planets array for a planet that has an equal specified key (sortingKey) as the Exoplanet key
	Returns a pointer to the system that the found planet is in
	Returns nullptr if no planet is found
	*/
	Exosystem* search(Exoplanet& key, char sortingKey) const;

	/*
	Returns a string representation of this object
	*/
	string toString(void) const;

	void write(ostream& os);
	void originalOrdering(ostream& os);
	void list(ostream& os);
	void debug(ostream& os);
};

	