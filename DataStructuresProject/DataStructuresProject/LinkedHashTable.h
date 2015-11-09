/*
Code for exception classes adapted from http://www.cplusplus.com/doc/tutorial/exceptions/
*/

#pragma once

#include "Node.h"

template <typename T, typename K>
class LinkedHashTable {
protected:
	/*
	head of the interwoven linked list*/
	Node<T>* head;
	/*
	tail of the interwoven linked list*/
	Node<T>* tail;
	/*
	pointer to the hash table*/
	Node<Node<T>>** arr;
	/*
	calculates the hash for the given key*/
	virtual int hash(K key) = 0;
	/*
	generates the key from the given data*/
	virtual K getKey(T& data) = 0;
	/*
	Determines whether the two objects are equal*/
	virtual bool equal(T& data, T& other) = 0;
	/*
	Returns a string value for the given data*/
	virtual string getStringValue(T& data) = 0;
	/*
	Returns a more complete string value for the given data, defaulted to the same as getStringValue
	Used to show the system data every time on inorder traversal*/
	virtual string getFullStringValue(T& data) { return getStringValue(data); };
	int buckets;
public:
	LinkedHashTable();
	LinkedHashTable(int buckets);
	~LinkedHashTable();

	int size() const;
	T* search(T& data);
	void add(T& data);
	void remove(T& data);
	/*
	Prints a representation of the hashtable to os*/
	void debug(ostream& os);
	/*
	Prints a list of all the items in the hash table based on the insertion order*/
	void inorder(ostream& os);
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
	if (arr != nullptr)
	{
		for (int i = 0; i < buckets; ++i)
		{
			Node<Node<T>>* current = arr[i];
			Node<Node<T>>* next;
			while (current != nullptr)
			{
				next = current->next;
				delete current;
				current = next;
			}
		}

		delete[] arr;
		arr = nullptr;
	}
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

	arr[index] = new Node<Node<T>>(Node<T>(data), arr[index]);
	Node<T>* newNode = &arr[index]->data;

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
inline void LinkedHashTable<T,K>::debug(ostream& os)
{
	int numberWithNull = 0;
	int totalNumberProbes = 0;
	int usedBuckets = 0;

	for (int i = 0; i < buckets; i++)
	{
		os << i << ": ";
		if (arr[i] == nullptr) {
			os << "NULL\n";
			numberWithNull++;
		}
		else
		{
			usedBuckets++;
			Node<Node<T>>* temp = arr[i];

			while (temp != nullptr)
			{
				totalNumberProbes++;
				os << getStringValue(temp->data.data) << ", \n   ";
				temp = temp->next;
			}
		}

		os << "\n";
	}
	os << "Number of empty buckets: " << numberWithNull << " Avg Num Probes for this set of keys: " << (double)totalNumberProbes / usedBuckets << "\n";
}

template<typename T, typename K>
inline void LinkedHashTable<T, K>::inorder(ostream& os)
{
	Node<T>* temp = head;
	while (temp != nullptr) {
		cout << getFullStringValue(temp->data) << ", \n\n\n";
		temp = temp->next;
	}
	cout << "\n";
}

template<typename T, typename K>
inline T * LinkedHashTable<T, K>::search(T& data)
{
	int index = hash(getKey(data));

	Node<Node<T>>* temp = arr[index];

	while (temp != nullptr && !equal(temp->data.data, data))
	{
		temp = temp->next;
	}

	if (temp == nullptr) return nullptr;
	else
	{
		return &temp->data.data;
	}
}

/*
Code for exception classes adapted from http://www.cplusplus.com/doc/tutorial/exceptions/
*/
class LinkedHashTableException : public exception
{
	virtual const char* what() const throw() = 0;
};

class LinkedHashTableElementNotFoundException : public LinkedHashTableException
{
	virtual const char* what() const throw()
	{
		return "Element not found in linked hash table";
	};
};