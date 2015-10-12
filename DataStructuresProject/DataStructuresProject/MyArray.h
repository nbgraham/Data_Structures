#pragma once
#include <exception>
#include <sstream>
using namespace std;

template <typename dataType>
class MyArray
{
private:
	dataType* arr;
	int size;
	int capacity;
	void resize();
public:
	//Constructors
	/*
	Default constructor
	*/
	MyArray(void);
	/*
	Constructor that specifies the initial capacity
	@param _capacity	the initial capacity
	*/
	MyArray(int _capacity);
	~MyArray(void);

	/*
	Adds the element to the end of the array
	If the array is full, it allocates a new array with twice the size, copies over the old elements and adds the new one
	@param newElement	the element to be added
	*/
	void add(dataType newElement);
	/*
	Removes the specified element from the array and shifts all the elements accordingly
	@param element	the element to be removed
	*/
	void remove(dataType element);
	/*
	Removes the element at the specified index and shifts all the elements accordingly
	@param index	the specified index
	*/
	void removeAt(int index);
	/*
	Returns the element at the specified index.
	@param index	the specified index
	@return	the value at that index
	*/
	dataType at(int index);
	/*
	Returns the index of the specified element, or -1 if it is not in the array
	@param element	the specified element
	@return	the index of the specified element
	*/
	int indexOf(dataType element);
	/*
	Returns the current length of this array
	*/
	int length(void) { return size; };
	/*
	Returns a string representation of this array
	*/
	string toString(void);
	/*
	Returns the element at the specified index
	*/
	dataType operator[](int index);
	/*
	Swaps the elements in the two specified positions
	*/
	void swap(int index0, int index1);
};

template <typename dataType>
MyArray<dataType>::MyArray()
{
	size = 0;
	capacity = 10;
	arr = new dataType[10];
}

template <typename dataType>
MyArray<dataType>::MyArray(int _capacity)
{
	size = 0;
	capacity = _capacity;
	arr = new dataType[capacity];
}

template<typename dataType>
MyArray<dataType>::~MyArray(void)
{
	cout << "Myarray destructor called\n";
	if (arr != NULL)
	{
		delete arr;
		arr = NULL;
	}
}

template <typename dataType>
void MyArray<dataType>::add(dataType newElement)
{
	if (size == capacity)
	{
		resize();
	}
	arr[size++] = newElement;
}

template<typename dataType>
void MyArray<dataType>::resize()
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

template<typename dataType>
dataType MyArray<dataType>::at(int index)
{
	if (index < 0 || index >= size) throw exception("Index out of range.");

	return arr[index];
}

template<typename dataType>
int MyArray<dataType>::indexOf(dataType element)
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

template<typename dataType>
string MyArray<dataType>::toString(void)
{
	ostringstream os;
	os << "[";

	for (int i = 0; i < size - 1; i++)
	{
		os << arr[i];
		os << ",";
	}
	os << arr[size - 1];

	os << "]";

	return os.str();
}

template<typename dataType>
dataType MyArray<dataType>::operator[](int index)
{
	return at(index);
}

template<typename dataType>
void MyArray<dataType>::swap(int index0, int index1)
{
	dataType temp = arr[index0];
	arr[index0] = arr[index1];
	arr[index1] = temp;
}

