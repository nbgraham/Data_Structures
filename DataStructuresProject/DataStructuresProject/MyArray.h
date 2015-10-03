#pragma once

template <typename dataType>
class MyArray
{
private:
	dataType* arr;
	int size;
	int capacity;
public:
	MyArray(void);
	MyArray(int _capacity);
	void add(dataType newElement);
	void remove(dataType element);
	void removeAt(int index);
	dataType at(int index) const;
	int indexOf(dataType element) const;
	int length(void) const { return size; };
};