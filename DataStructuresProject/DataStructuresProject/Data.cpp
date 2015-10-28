#include "Data.h"

Data::Data()
{
	isEmpty = true;
	isSortedOnKey = 0;
	planets = new Array<Exoplanet*>();
	exosystems = new LinkedList <Exosystem>();
}

Data::~Data() {
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
}

string Data::toString(void) const
{
	string result = "";

	LinkedListIterator<Exosystem> it = LinkedListIterator<Exosystem>(exosystems);
	while (it.hasNext())
	{
		result += it.getNext()->toString();
		result += "\n\n";
	}

	if (result.length() > 1) return result;
	else return "--Empty--\n";
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
	if (isSortedOnKey == sortingKey)
	{
		result = binarySearch(key, *planets, sortingKey);
	}
	else
	{
		result = linearSearch(key, *planets, sortingKey);
	}

	if (result == nullptr) return nullptr;

	Exosystem* resultP = result->getSystemPointer();
	return resultP;
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
	Exosystem* currentSystem = nullptr;
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
		for (int i = 0; i < count; i++)
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

		Exosystem* match = exosystems->search(*currentSystem);
		if (match == nullptr)
		{//No match in system
			if (type == 'P')
			{
				rslt << "Line " << lineNumber << ": no such system named " + starName + " in data\n";
				continue;
			}
			else
			{
				exosystems->add(*currentSystem);
			}
		}
		else
		{
			currentSystem = match;
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
			try
			{
				removePlanetFromSystem(currentPlanet, currentSystem);
			}
			catch (exception e)
			{
				rslt << "Line " << lineNumber << ": planet " << currentPlanet->getFullName() << e.what() << "\n";
			}
		}
		else
		{
			//add the current planet to the current exosystem
			try
			{
				addPlanetToSystem(currentPlanet, currentSystem, type);
			}
			catch (exception e)
			{
				//Planet was not added because of validition error
				planets->remove(currentPlanet);
				rslt << "Line " << lineNumber << ": planet was excluded because " << e.what() << '\n';
			}
		}
	}

	inputData.close();

	isEmpty = false;

	cout << "\n";

	//output any information messages
	cout << rslt.str();
}

void Data::addPlanetToSystem(Exoplanet* planet, Exosystem* system, char type)
{
	Exoplanet* match;
	if (isSortedOnKey == 'N')
	{
		match = binarySearch(*planet, *planets, 'N');
	}
	else
	{
		match = linearSearch(*planet, *planets, 'N');
	}

	if (match == nullptr)
	{
		//Add planet
		planets->add(planet);
		system->addPlanet(planet);
	}
	else if (type == 'M')
	{
		//Update the planet
		*match = *planet;
		system->overwritePlanet(planet);
		cout << "Planet " + planet->getFullName() + " was overwritten\n";
	}
	else
	{
		cout << "Planet name " + planet->getFullName() + " is not unique within the system and was excluded.\n";
	}
}

void Data::removePlanetFromSystem(Exoplanet* planet, Exosystem* system)
{
	Exoplanet* match;
	if (isSortedOnKey == 'N')
	{
		match = binarySearch(*planet, *planets, 'N');
	}
	else
	{
		match = linearSearch(*planet, *planets, 'N');
	}

	if (match == nullptr)
	{
		throw exception(" was not found in the data.");
	}
	else
	{
		planets->remove(match);

		system->removePlanet(planet);

		if (system->getCurrentNumberOfPlanets() == 0)
		{
			exosystems->remove(*system);
		}
	}
}