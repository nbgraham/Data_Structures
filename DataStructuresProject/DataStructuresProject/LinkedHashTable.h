#pragma once

#include "Node.h"

template <typename T, typename K>
class LinkedHashTable {
protected:
	Node<T>* head;
	Node<T>* tail;
	Node<Node<T>>** arr;
	virtual int hash(K key) = 0;
	virtual K getKey(T& data) = 0;
	int buckets;
public:
	LinkedHashTable();
	LinkedHashTable(int buckets);
	~LinkedHashTable();

	int size() const;
	T* search(T& data);
	void add(T& data);
	void remove(T& data);
	void debug();
	void inorder();
};

template <typename T, typename K>
inline LinkedHashTable<T,K>::LinkedHashTable() : LinkedHashTable(10)
{}

template <typename T, typename K>
inline LinkedHashTable<T,K>::LinkedHashTable(int buckets)
{
	head = nullptr;
	tail = nullptr;
	this->buckets = buckets;
	arr = new Node<Node<T>>*[buckets];

	for (int i = 0; i < buckets; i++) {
		arr[i] = nullptr;
	}
}

template <typename T, typename K>
inline LinkedHashTable<T,K>::~LinkedHashTable()
{
	Node<T>* current = head;
	Node<T>* next;
	while (current != nullptr)
	{
		next = current->next;
		delete current;
		current = next;
	}

	delete[] arr;
}

template<typename T, typename K>
inline int LinkedHashTable<T, K>::size() const
{
	int size = 0;

	Node <Node<T>>* curr;
	for (int i = 0; i < buckets; i++)
	{
		curr = arr[i];

		while (curr != nullptr) {
			curr = curr->next;
			size++;
		}
	}

	return size;
}

template <typename T, typename K>
inline void LinkedHashTable<T,K>::add(T& data)
{
	int index = hash(getKey(data));

	Node<T>* newNode = new Node<T>(data);
	arr[index] = new Node<Node<T>>(*newNode, arr[index]);

	if (tail == nullptr) {
		tail = newNode;
		head = tail;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

template <typename T, typename K>
inline void LinkedHashTable<T,K>::remove(T & data)
{
	if (head->data == data)
	{
		head = head->next;
	}
	else
	{
		Node<T>* prev = head;
		while (prev->next != nullptr && prev->next->data != data) {
			prev = prev->next;
		}

		if (prev->next == nullptr) throw exception("Element could not be found in linked list.");
		else {
			prev->next = prev->next->next;
		}
	}

	int index = hash(getKey(data));

	if (arr[index] == nullptr)
	{
		throw exception("Element not in the hash table.");
	}
	else
	{
		if (arr[index]->data.data == data)
		{
			Node<Node<T>>* temp = arr[index];
			arr[index] = arr[index]->next;
			delete temp;
		}
		else
		{
			Node<Node<T>>* prev = arr[index];

			while (prev->next != nullptr && prev->next->data.data != data) {
				prev = prev->next;
			}

			if (prev->next == nullptr) throw exception("Element could not be found in linked list.");
			else
			{
				Node<Node<T>>* temp = prev->next;
				prev->next = prev->next->next;
				delete temp;
			}
		}
	}	
}

template <typename T, typename K>
inline void LinkedHashTable<T,K>::debug()
{
	for (int i = 0; i < buckets; i++)
	{
		cout << i << ": ";
		if (arr[i] == nullptr) cout << "NULL";
		else
		{
			Node<Node<T>>* temp = arr[i];

			while (temp != nullptr)
			{
				cout << temp->data.data << ", ";
				temp = temp->next;
			}
		}

		cout << "\n";
	}
}

template<typename T, typename K>
inline void LinkedHashTable<T, K>::inorder()
{
	cout << "Inorder: ";

	Node<T>* temp = head;
	while (temp != nullptr) {
		cout << temp->data << ", ";
		temp = temp->next;
	}
	cout << "\n";
}

template<typename T, typename K>
inline T * LinkedHashTable<T, K>::search(T& data)
{
	int index = hash(getKey(data));

	Node<Node<T>>* temp = arr[index];

	while (temp != nullptr && temp->data.data != data)
	{
		temp = temp->next;
	}

	if (temp == nullptr) throw exception("Element not in the hash table.");
	else
	{
		return &temp->data.data;
	}
}

