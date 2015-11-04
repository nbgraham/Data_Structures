#pragma once

#include "LinkedList.h"
#include "Exoplanet.h"
#include "LinkedListIterator.h"

class ExoplanetHashTable
{
private:
	LinkedList<string>** arr;
	int hash(string name);
	int size;
public:
	ExoplanetHashTable();
	ExoplanetHashTable(int size);
	~ExoplanetHashTable();

	int length() const { return size; };
	string* search(string name);
	void add(string& data);
	void remove(string& data);
	void debug();
};

inline ExoplanetHashTable::ExoplanetHashTable()
{
	size = 10;
	arr = new LinkedList<string>*[10];
	for (int i = 0; i < size; i++)
	{
		arr[i] = nullptr;
	}
}

inline ExoplanetHashTable::ExoplanetHashTable(int size)
{
	this->size = size;
	arr = new LinkedList<string>*[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = nullptr;
	}
}

inline ExoplanetHashTable::~ExoplanetHashTable()
{
	delete[] arr;
}

inline int ExoplanetHashTable::hash(string name)
{
	int sum = 0;

	for (int i = 0; i < name.length(); i++)
	{
		sum += name.at(i);
	}

	return sum%size;
}

inline void ExoplanetHashTable::add(string & data)
{
	int index = hash(data);
	
	if (arr[index] == nullptr)
	{
		arr[index] = new LinkedList<string>();
	}

	arr[index]->add(data);
}

inline void ExoplanetHashTable::remove(string & data)
{
	int index = hash(data);

	if (arr[index] == nullptr)
	{
		throw exception("Element not in the hash table.");
	}

	arr[index]->remove(data);
}

inline string* ExoplanetHashTable::search(string name)
{
	int index = hash(name);

	if (arr[index] == nullptr)
	{
		throw exception("Element not in the hash table.");
	}

	return arr[index]->search(name);
}

inline void ExoplanetHashTable::debug()
{
	for (int i = 0; i < size; i++)
	{
		cout << i << ": ";
		if (arr[i] != nullptr)
		{
			LinkedListIterator<string> it(arr[i]);

			while (it.hasNext())
			{
				cout << *it.getNext() << ", ";
			}
		}

		cout << "\n";
	}
}