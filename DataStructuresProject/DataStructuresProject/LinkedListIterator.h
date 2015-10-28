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
	Create an iterator over the specified list*/
	LinkedListIterator(LinkedList<T>* list);
	/*
	Returns true if there is another item, false otherwise*/
	bool hasNext() const;
	/*
	Returns a pointer to the next item*/
	const T* getNext();
};

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
inline const T* LinkedListIterator<T>::getNext()
{
	if (currNode == nullptr) throw exception("End of list.");
	T* temp = &currNode->data;
	currNode = currNode->next;
	return temp;
}