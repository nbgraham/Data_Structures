#include <exception>

#include "MyArray.h"
#include "Exoplanet.h"
#include "Exosystem.h"

template MyArray<int>;
template MyArray<Exoplanet>;
template MyArray<Exosystem>;

//Constructors
/*
Default constructor
*/
template <typename dataType>
MyArray<dataType>::MyArray()
{
	size = 0;
	capacity = 10;
	arr = new dataType[10];
}

/*
Constructor that specifies the initial capacity
@param _capacity	the initial capacity
*/
template <typename dataType>
MyArray<dataType>::MyArray(int _capacity)
{
	size = 0;
	capacity = _capacity;
	arr = new dataType[capacity];
}

/*
Adds the element to the end of the array
If the array is full, it allocates a new array with twice the size, copies over the old elements and adds the new one
@param newElement	the element to be added
*/
template <typename dataType>
void MyArray<dataType>::add(dataType newElement)
{
	if (size == capacity)
	{
		dataType* temp = arr;
		arr = new dataType[capacity * 2];
		for (int i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}
		delete[] temp;
		capacity *= 2;
	}
	arr[size++] = newElement;
}

/*
Removes the specified element from the array and shifts all the elements accordingly
@param element	the element to be removed
*/
template <typename dataType>
void MyArray<dataType>::remove(dataType element)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (arr[i] == element)
		{
			break;
		}
	}
	if (i == size) throw exception("Specified element not in the array");

	while (i < size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	size--;
}

/*
Removes the element at the specified index and shifts all the elements accordingly
@param index	the specified index
*/
template <typename dataType>
void MyArray<dataType>::removeAt(int index)
{
	if (index < 0 || index >= size) throw exception("Index out of range.");
	while (index < size - 1)
	{
		arr[index] = arr[index + 1];
		index++;
	}
	size--;
}

/*
Returns the element at the specified index.
@param index	the specified index
@return	the value at that index
*/
template<typename dataType>
dataType MyArray<dataType>::at(int index) const
{
	if (index < 0 || index >= size) throw exception("Index out of range.");

	return arr[index];
}

/*
Returns the index of the specified element, or -1 if it is not in the array
@param element	the specified element
@return	the index of the specified element
*/
template<typename dataType>
int MyArray<dataType>::indexOf(dataType element) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
		{
			return i;
		}
	}

	//If element was not found, return -1
	return -1;
}