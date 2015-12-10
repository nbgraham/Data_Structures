#include "Data.h"

Data::Data()
{
	numberOfReadPlanets = 0;
	isSortedOnKey = 0;
	exosystems = new AVLTree<ExosystemP>();
	dbg "Constructed data object\n";
}

Data::~Data() {
	if (hashTable != nullptr)
	{
		delete hashTable;
		hashTable = nullptr;
	}
	if (planets != nullptr)
	{
		delete planets;
		planets = nullptr;
	}

	if (exosystems != nullptr)
	{
		delete exosystems;
		exosystems = nullptr;
	}
	dbg "Destructed data object\n";
}

void Data::sort(char userChoice)
{
	quickSort(*planets, 0, planets->size() - 1, userChoice);
	isSortedOnKey = userChoice;
}

/*
Adapted from:
http://www.algolist.net/Algorithms/Sorting/Quicksort
*/
void Data::quickSort(Array<Exoplanet*>& arr, int left, int right, char sortingKey)
{
	int i = left, j = right;
	Exoplanet* pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		//while (arr[i] < pivot)
		while (arr[i]->compare(*pivot, sortingKey) < 0)
			i++;
		//while (arr[j] > pivot)
		while (arr[j]->compare(*pivot, sortingKey) > 0)
			j--;
		if (i <= j) {
			arr.swap(i, j);
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, left, j, sortingKey);
	if (i < right)
		quickSort(arr, i, right, sortingKey);
}

Exosystem* Data::search(Exoplanet& key, char sortingKey) const
{
	Exoplanet* result;
	if (sortingKey == 'N')
	{
		result = new Exoplanet(key);
		Exoplanet** temp = hashTable->search(result);
		if (temp == nullptr) result = nullptr;
		else result = *temp;
	}
	else if (isSortedOnKey == sortingKey)
	{
		result = binarySearch(key, *planets, sortingKey);
	}
	else
	{
		result = linearSearch(key, *planets, sortingKey);
	}

	if (result == nullptr) return nullptr;

	return result->getSystemPointer();
}

Exoplanet* Data::binarySearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const
{
	int mid = 0;
	int left = 0;
	int right = planets.size() - 1;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (key.compare(*planets[mid], sortingKey) < 0)
		{
			right = mid - 1;
		}
		else if (key.compare(*planets[mid], sortingKey) > 0)
		{
			left = mid + 1;
		}
		else
		{
			return planets[mid];
		}
	}

	return nullptr;
}

Exoplanet* Data::linearSearch(Exoplanet& key, Array<Exoplanet*>& planets, char sortingKey) const
{
	for (int j = 0; j < planets.size(); j++)
	{
		if (key.compare(*planets[j], sortingKey) == 0)
		{
			return planets[j];
		}
	}
	return nullptr;
}

void Data::merge(Exosystem * system, Exoplanet * planet)
{
	if (system->getPlanets().search(*planet) == nullptr)
	{
		system->addPlanet(planet);
	}
	else
	{
		system->overwritePlanet(planet);
	}
}

void Data::changeDataFromFile(string inputFileName, char type)
{
	cout << "Loading";

	ostringstream rslt;
	ifstream inputData;
	inputData.open(inputFileName);

	if (!inputData)
	{
		throw exception("File could not be read.");
	}

	if (type != 'M' && type != 'P' && type != 'A')
	{
		throw exception("Invalid type: " + type);
	}

	string line;
	//Read the header line, but do nothing with it
	getline(inputData, line);

	//Declare necessary data
	Exosystem* currentSystem;
	Exoplanet* currentPlanet = nullptr;
	string starName;
	char planetName;
	int numberOfPlanets;
	double msini, a, per, ecc, om, t0, k;
	bool hasSingleStar;
	string message;
	bool hasAllInfo;

	//Step through each line in the data file until there are no more lines
	int lineNumber = 1;
	while (getline(inputData, line))
	{
		if (lineNumber % 25 == 0) cout << ".";
		lineNumber++;

		//Break line up into an array on commas
		int startIndex = 0;
		int endIndex = 0;
		int count = 0;
		string info[10];
		for (unsigned int i = 0; i < line.length(); i++)
		{
			if (line[i] == ',')
			{
				endIndex = i;
				info[count] = line.substr(startIndex, endIndex - startIndex);
				count++;
				//skip comma
				startIndex = i + 1;
			}
		}
		//Get the section from the last comma to the end
		info[count] = line.substr(startIndex, line.length() - startIndex);

		//Data validation
		hasAllInfo = true;
		if (count < 9)
		{
			hasAllInfo = false;
		}
		if (info[0].at(info[0].length() - 2) != ' ')
		{
			hasAllInfo = false;
		}
		for (int i = 0; i <= count; i++)
		{
			if (info[i].length() < 1)
			{
				//A field is blank
				hasAllInfo = false;
			}
		}

		starName = info[0].substr(0, info[0].length() - 2);

		//Exosystem info
		if (type == 'P')
		{
			currentSystem = new Exosystem(starName, 0, true);
		}
		else if (hasAllInfo)
		{
			hasSingleStar = info[9] == "0";
			numberOfPlanets = stoi(info[1]);
			currentSystem = new Exosystem(starName, numberOfPlanets, hasSingleStar);
		}
		else
		{
			rslt << "Line " << lineNumber << ": planet did not have all the data and was excluded.\n";
			continue;
		}

		if (starName == "Kepler-98")
		{
			int x = 4;
		}

		ExosystemP* match = exosystems->search(ExosystemP(currentSystem));
		if (match == nullptr)
		{//No match in system
			if (type == 'P')
			{
				rslt << "Line " << lineNumber << ": no such system named " + starName + " in data\n";
				continue;
			}
			else
			{
				currentSystem = (*exosystems->add(ExosystemP(currentSystem))).ptr;
			}
		}
		else
		{
			currentSystem = (*match).ptr;
		}

		//Exoplanet info
		if (hasAllInfo)
		{
			msini = stod(info[2]);
			a = stod(info[3]);
			per = stod(info[4]);
			ecc = stod(info[5]);
			om = stod(info[6]);
			t0 = stod(info[7]);
			k = stod(info[8]);
		}

		planetName = info[0].at(info[0].length() - 1);

		currentPlanet = new Exoplanet(planetName, msini, a, per, ecc, om, t0, k, currentSystem, starName);

		if (type == 'P')
		{
			numberOfReadPlanets -= currentSystem->getPlanets().size();
			exosystems->remove(ExosystemP(currentSystem));
		}
		else
		{
			dbg "Adding planet "; dbg currentPlanet->getName(); dbg " to system "; dbg currentSystem->getStarName(); dbg "\n";
			try
			{
				merge(currentSystem, currentPlanet);
				numberOfReadPlanets++;
			}
			catch (ExosystemPlanetNameNotUniqueException e)
			{
				rslt << "Planet name " << currentPlanet->getName() << " not unique within " << currentSystem->getStarName() << "\n";
			}
			catch (ExosystemTooManyPlanetsException e)
			{
				rslt << "Too many planets in exosystem " << currentSystem->getStarName() << "\n";
			}
		}
	}
	
	inputData.close();

	//output any information messages
	cout << "\n" << rslt.str();
	
	if (planets != nullptr)
		delete planets;
	planets = new Array<Exoplanet*>(numberOfReadPlanets);
	if (hashTable != nullptr)
		delete hashTable;
	dbg "Creating new hash table of size "; dbg numberOfReadPlanets; dbg "\n";
	hashTable = new ExoplanetLHT(numberOfReadPlanets);
	
	AVLTreeIterator<ExosystemP> sysIt(exosystems);
	LinkedListIterator<Exoplanet> planIt;
	LinkedList<Exoplanet>* systemPlanets;
	Exoplanet* curr;
	while (sysIt.hasNext())
	{
		dbg "Adding planets to hash table and array: ";
		systemPlanets = new LinkedList<Exoplanet>(sysIt.getNext().ptr->getPlanets());
		planIt = LinkedListIterator<Exoplanet>(systemPlanets);
		while (planIt.hasNext())
		{
			curr = planIt.getNext();
			dbg curr->getFullName(); dbg ", ";
			planets->add(curr);
			hashTable->add(curr);
		}
		dbg "\n";
	}
}

void Data::write(ostream& os)
{	
	if (numberOfReadPlanets == 0)
	{
		os << "--Empty--\n";
		return;
	}
	Exoplanet* curr;
	for (int i = 0; i < planets->size(); ++i)
	{
		curr = planets->at(i);
		os << curr->getSystemPointer()->systemDataString() << "\n";
		os << curr->toString() << "\n\n\n";
	}
}

void Data::originalOrdering(ostream& os)
{
	if (numberOfReadPlanets == 0)
	{
		os << "--Empty--\n";
		return;
	}

	AVLTreeIterator<ExosystemP> it = AVLTreeIterator<ExosystemP>(exosystems);
	while (it.hasNext())
	{
		os << it.getNext().ptr->toString() << "\n\n";
	}

}

void Data::list(ostream& os)
{
	if (numberOfReadPlanets == 0)
	{
		os << "--Empty--\n";
		return;
	}

	hashTable->inorder(os);
}

void Data::debug(ostream & os)
{
	if (numberOfReadPlanets == 0)
	{
		os << "--Empty--\n";
		return;
	}
	hashTable->debug(os);
}