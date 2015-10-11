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
	MyArray(void);
	MyArray(int _capacity);
	//~MyArray(void);

	dataType* add(dataType& newElement);
	void remove(dataType element);
	void removeAt(int index);
	dataType at(int index);
	int indexOf(dataType element);
	int length(void) { return size; };
	string toString(void);
	dataType operator[](int index);
	void swap(int index0, int index1);
};

