#pragma once

#include <string>
#include <sstream>

#include "Node.h"

template <typename T>
class LinkedList
{
protected:
	Node<T>* head;
	int length;
public:
	/*
	Default constructor*/
	LinkedList();
	/*
	Copy constructor*/
	LinkedList(LinkedList<T>& list);
	/*
	Destructor*/
	~LinkedList();

	/*
	Returns a pointer to the list's head*/
	Node<T>* getHead() { return head; };
	/*
	Returns a string representation of this list*/
	string toString() const;
	/*
	Returns the size of this list*/
	int size() { return length; };
	/*
	Adds the specified item to the list, in the correct spot to retain sorted order*/
	Node<T>* add(T& data);
	/*
	Removes the specified item from the list*/
	void remove(T& data);
	/*
	Returns a pointer to an object in the list that matches the specified data*/
	T* search(T& data) const;
};

template<typename T>
inline LinkedList<T>::LinkedList()
{
	head = nullptr;
	length = 0;
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T>& list)
{
	if (list.getHead() == nullptr)
	{
		head = nullptr;
		length = 0;
		return;
	}
	else
	{
		head = new Node<T>(list.getHead()->data, list.getHead()->next);
		length = 1;
	}

	Node<T>* curr = head;
	while (curr->next != nullptr)
	{
		curr->next = new Node<T>(curr->next->data, curr->next->next);
		length++;
		curr = curr->next;
	}
}

template<typename T>
inline Node<T>* LinkedList<T>::add(T& data)
{
	Node<T>* result;
	if (length == 0)
	{
		head = new Node<T>(data);
		result = head;
	}
	else
	{
		if (data < head->data)
		{
			head = new Node<T>(data, head);
			result = head;
		}
		else
		{
			Node<T>* prev = head;
			while (prev->next != nullptr && prev->next->data < data)
			{
				prev = prev->next;
			}

			prev->next = new Node<T>(data, prev->next);
			result = prev->next;
		}
	}

	length++;
	return result;
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	Node<T>* current = head;
	Node<T>* next;
	while (current != nullptr)
	{
		next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
inline void LinkedList<T>::remove(T& data)
{
	if (length == 0)
	{
		throw LinkedListElementNotFoundException();
	}
	else
	{
		Node<T>* temp;

		if (head->data == data)
		{
			temp = head->next;
			delete head;
			head = temp;
		}
		else
		{
			Node<T>* prev = head;
			while (prev->next != nullptr && prev->next->data != data)
			{
				prev = prev->next;
			}

			if (prev->next == nullptr)
			{
				throw LinkedListElementNotFoundException();
			}
			else
			{
				temp = prev->next->next;
				delete prev->next;
				prev->next = temp;
			}
		}

		length--;
	}
}

template<typename T>
inline string LinkedList<T>::toString() const
{
	ostringstream os;

	Node<T>* temp = head;
	while (temp != nullptr)
	{
		os << temp->data;
		temp = temp->next;
	}

	return os.str();
}

template<typename T>
inline T* LinkedList<T>::search(T& data) const
{
	Node<T>* temp = head;
	while (temp != nullptr && temp->data != data)
	{
		temp = temp->next;
	}

	if (temp == nullptr)
	{
		return nullptr;
	}

	return &temp->data;
}

class LinkedListException : public exception {};
class LinkedListElementNotFoundException : public LinkedListException {};