#pragma once
#include "AVLTree.h"

template <typename T>
class AVLTreeIterator
{
private:
	/*
	The tree to iterate through*/
	AVLTree<T>* tree;
	/*
	The node current at in the traversal*/
	node<T>* currNode;
	/*
	Array of visited nodes*/
	Array<node<T>*>* visitedNodes;
public:
	/*
	Constructs an iterator for the specified tree*/
	AVLTreeIterator(AVLTree<T>* _tree);
	/*
	Destructor*/
	~AVLTreeIterator();

	/*
	Returns true if there is another item to get*/
	bool hasNext();
	/*
	Returns the next item*/
	T& getNext();
};

template<typename T>
inline AVLTreeIterator<T>::AVLTreeIterator(AVLTree<T> * _tree)
{
	tree = _tree;
	visitedNodes = new Array<node<T>*>(_tree->getSize());

	currNode = _tree->getRoot();
	while (currNode->left != nullptr) currNode = currNode->left;

	visitedNodes->add(currNode);
}

template<typename T>
inline AVLTreeIterator<T>::~AVLTreeIterator()
{
	if (visitedNodes != nullptr)
	{
		delete visitedNodes;
		visitedNodes = nullptr;
	}
}

template<typename T>
inline bool AVLTreeIterator<T>::hasNext()
{
	return currNode != nullptr;
}

template<typename T>
inline T& AVLTreeIterator<T>::getNext()
{
	T* result = currNode->data;

	while (visitedNodes->indexOf(currNode) >= 0)
	{
		if (currNode->left != nullptr && visitedNodes->indexOf(currNode->left) < 0)
		{
			currNode = currNode->left;
		}
		else if (currNode->right != nullptr && visitedNodes->indexOf(currNode->right) < 0)
		{
			currNode = currNode->right;
		}
		else
		{
			currNode = currNode->parent;
		}
	}
	visitedNodes->add(currNode);

	return *result;

}
