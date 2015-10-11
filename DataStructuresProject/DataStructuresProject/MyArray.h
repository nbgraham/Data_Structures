#pragma once

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
	//~MyArray(void);

	/*
	Adds the element to the end of the array
	If the array is full, it allocates a new array with twice the size, copies over the old elements and adds the new one
	@param newElement	the element to be added
	*/
	dataType* add(dataType& newElement);
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

