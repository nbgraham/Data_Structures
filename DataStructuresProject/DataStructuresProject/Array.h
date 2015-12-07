#pragma once
#include <exception>
#include <sstream>
using namespace std;

template <typename dataType>
class Array
{
private:
	dataType* arr;
	int sze;
	int capacity;
	void resize();
public:
	/*
	Default constructor*/
	Array(void);
	/*
	Constructor that specifies the initial capacity
	@param _capacity	the initial capacity*/
	Array(int _capacity);
	/*
	Destructor*/
	~Array(void);

	/*
	Adds the element to the end of the array
	If the array is full, it allocates a new array with twice the size, copies over the old elements and adds the new one
	@param newElement	the element to be added*/
	void add(dataType newElement);
	/*
	Removes the specified element from the array and shifts all the elements accordingly
	@param element	the element to be removed*/
	void remove(dataType element);
	/*
	Removes the element at the specified index and shifts all the elements accordingly
	@param index	the specified index*/
	void removeAt(int index);
	/*
	Returns the element at the specified index.
	@param index	the specified index
	@return	the value at that index*/
	dataType at(int index) const;
	/*
	Returns the index of the specified element, or -1 if it is not in the array
	@param element	the specified element
	@return	the index of the specified element*/
	int indexOf(dataType element) const;
	/*
	Returns the current length of this array*/
	int size(void) { return sze; };
	/*
	Returns a string representation of this array*/
	string toString(void) const;
	/*
	Returns the element at the specified index*/
	dataType operator[](int index) const;
	/*
	Swaps the elements in the two specified positions*/
	void swap(int index0, int index1);
};

template <typename dataType>
Array<dataType>::Array()
{
	sze = 0;
	capacity = 10;
	arr = new dataType[10];
}

template <typename dataType>
Array<dataType>::Array(int _capacity)
{
	sze = 0;
	capacity = _capacity;
	arr = new dataType[capacity];
}

template<typename dataType>
Array<dataType>::~Array(void)
{
	if (arr != NULL)
	{
		delete[] arr;
		arr = NULL;
	}
}

template <typename dataType>
void Array<dataType>::add(dataType newElement)
{
	if (sze == capacity)
	{
		resize();
	}

	arr[sze++] = newElement;
}

template<typename dataType>
void Array<dataType>::resize()
{
	dataType* temp = arr;
	arr = new dataType[capacity * 2];
	if (arr == nullptr)
	{
		throw ArrayMemoryException();
	}

	for (int i = 0; i < sze; i++)
	{
		arr[i] = temp[i];
	}
	delete[] temp;
	capacity *= 2;
}

template <typename dataType>
void Array<dataType>::remove(dataType element)
{
	int i = indexOf(element);

	if (i == -1) throw ArrayElementNotFoundException();

	while (i < sze - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	sze--;
}

template <typename dataType>
void Array<dataType>::removeAt(int index)
{
	if (index < 0 || index >= sze) throw ArrayIndexOutOfBoundsException;

	while (index < sze - 1)
	{
		arr[index] = arr[index + 1];
		index++;
	}
	sze--;
}

template<typename dataType>
dataType Array<dataType>::at(int index) const
{
	if (index < 0 || index >= sze) throw ArrayIndexOutOfBoundsException();
	return arr[index];
}

template<typename dataType>
int Array<dataType>::indexOf(dataType element) const
{
	for (int i = 0; i < sze; i++)
	{
		if (arr[i] == element)
		{
			return i;
		}
	}

	//If element was not found, return -1
	return -1;
}

template<typename dataType>
string Array<dataType>::toString(void) const
{
	ostringstream os;
	os << "[";

	for (int i = 0; i < sze - 1; i++)
	{
		os << arr[i];
		os << ",";
	}
	os << arr[sze - 1];

	os << "]";

	return os.str();
}

template<typename dataType>
dataType Array<dataType>::operator[](int index) const
{
	return arr[index];
}

template<typename dataType>
void Array<dataType>::swap(int index0, int index1)
{
	dataType temp = arr[index0];
	arr[index0] = arr[index1];
	arr[index1] = temp;
}

class ArrayException : public exception {};
class ArrayIndexOutOfBoundsException : public ArrayException {};
class ArrayMemoryException : public ArrayException {};
class ArrayElementNotFoundException : public ArrayException {};