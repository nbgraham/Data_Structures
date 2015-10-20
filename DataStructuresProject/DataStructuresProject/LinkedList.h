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
	LinkedList();
	~LinkedList();
	void add(T& data);
	bool remove(T& data);
	Node<T>* getHead() { return head };
	string toString() const;
	int size() { return length; };
	T search(T& data) const;
};

template<typename T>
inline LinkedList<T>::LinkedList()
{
	head = nullptr;
	length = 0;
}

template<typename T>
inline void LinkedList<T>::add(T& data)
{
	if (length == 0)
	{
		head = new Node<T>(data);
	}
	else
	{
		if (data < head->data)
		{
			head = new Node<T>(data, head);
		}
		else
		{
			Node<T>* prev = head;
			while (prev->next != nullptr && prev->next->data < data)
			{
				prev = prev->next;
			}

			prev->next = new Node<T>(data, prev->next);
		}
	}

	length++;
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
inline bool LinkedList<T>::remove(T& data)
{
	if (length == 0)
	{
		return false;
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
				return false;
			}
			else
			{
				temp = prev->next->next;
				delete prev->next;
				prev->next = temp;
			}
		}

		length--;
		return true;
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
inline T LinkedList<T>::search(T& data) const
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
	return temp->data;
}