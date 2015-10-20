#pragma once
#include "LinkedList.h"

template <typename T>
class LinkedListPtrs : public LinkedList<T*>
{
public:
	LinkedListPtrs() : LinkedList<T*>() {};
	string toString() const
	{
		ostringstream os;

		Node<T*>* temp = head;
		while (temp != nullptr)
		{
			os << *temp->data << "\n";
			temp = temp->next;
		}

		return os.str();
	};
	T* search(T* data) const
	{
		Node<T*>* temp = head;
		while (temp != nullptr && *temp->data != *data)
		{
			temp = temp->next;
		}

		if (temp == nullptr)
		{
			return nullptr;
		}
		return temp->data;
	};
	void add(T* data)
	{
		if (length == 0)
		{
			head = new Node<T*>(data);
		}
		else
		{
			if (*data < *head->data)
			{
				head = new Node<T*>(data, head);
			}
			else
			{
				Node<T*>* prev = head;
				while (prev->next != nullptr && *prev->next->data < *data)
				{
					prev = prev->next;
				}

				prev->next = new Node<T*>(data, prev->next);
			}
		}

		length++;
	};
};