#pragma once

#include "LinkedList.h"
#include "Node.h"

template <typename T>
class LinkedListIterator
{
private:
	LinkedList<T>* _list;
	Node<T>* currNode;
public:
	/*
	Default constructor*/
	LinkedListIterator();
	/*
	Create an iterator over the specified list*/
	LinkedListIterator(LinkedList<T>* list);
	/*
	Returns true if there is another item, false otherwise*/
	bool hasNext() const;
	/*
	Returns a pointer to the next item*/
	T* getNext();
};

template<typename T>
inline LinkedListIterator<T>::LinkedListIterator()
{
	_list = nullptr;
	currNode = nullptr;
}

template<typename T>
inline LinkedListIterator<T>::LinkedListIterator(LinkedList<T>* list)
{
	_list = list;
	currNode = list->getHead();
}

template<typename T>
inline bool LinkedListIterator<T>::hasNext() const
{
	if (currNode == nullptr) return false;
	else return true;
}

template<typename T>
inline T* LinkedListIterator<T>::getNext()
{
	if (currNode == nullptr) throw exception("End of list.");
	T* temp = &currNode->data;
	currNode = currNode->next;
	return temp;
}