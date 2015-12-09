#pragma once
using namespace std;
#include <string>
#include <exception>
#include "Array.h"
#include "Debug.h"

/*
Inspired from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node/
*/

class AVLTreeException : public exception {};
class AVLItemNotFound : AVLTreeException {};
class AVLWrongParent : AVLTreeException {};
class AVLEmptyTree : AVLTreeException {};

/*
A structure for each node in an AVL Tree of type T*/
template <typename T>
struct node {
	T* data;
	/*
	height on right minus height on left*/
	int diff;
	node<T>* left;
	node<T>* right;
	node<T>* parent;
};

template <typename T>
class AVLTree
{
private:
	/*
	The root of this tree*/
	node<T>* root;
	/*
	Number of entries in this tree*/
	int size;

	/*
	Returns true if the the pointer is null or the node has no data*/
	bool isEmpty(node<T>* n);

	/*
	Returns the max of two numbers*/
	int max(int a, int b);

	/*
	Updates all diffs below the specified node*/
	void updateTreeDiffs(node<T>* n);
	/*
	Updates the diff at the specified node*/
	int updateNodeDiff(node<T>* n);
	/*
	Gets the height of the tree starting at the specified node*/
	int getHeight(node<T>* n);
	/*
	Fixes any imbalance, based on the situation represented by the ancestor and added nodes
	Adapted from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node<T>/*/
	void fixImbalance(node<T>* ancestor, node<T>* added);

	/*
	Creates a child node of _parent with _data as the data and places it in child (output)*/
	void makeChildNode(node<T>** child, node<T>* _parent, T* _data);
	

	/*
	Finds the node that contains itema and places it in result (output)*/
	void find(T& item, node<T>** result);
	/*
	Finds the node with the greatest value less than n and places it in result (output)*/
	void findGreatestLesserValue(node<T>* n, node<T>** result);
	
	/*
	Recurisve call inorder on the specified node, buidling up current*/
	string inorder(string current, node<T>* n);

	/*
	Swaps the values in the two memory locations*/
	void swap(T* ptrData, T* other);
	/*
	Clockwise rotation about n
	left left case*/
	void zig(node<T>* n);
	/*
	Counter-clockwise rotation about n
	right right case*/
	void zag(node<T>* n);
	/*
	left right case*/
	void zigzag(node<T>* n);
	/*
	right left case*/
	void zagzig(node<T> * n);
public:
	/*
	Default constructor*/
	AVLTree();
	/*
	Copy constructor*/
	AVLTree(AVLTree& other);
	/*
	Destructor*/
	~AVLTree();

	/*
	Returns true if this tree has no data*/
	bool isEmpty() { return root == nullptr; };
	/*
	Returns the size of this tree*/
	int getSize() { return size; }
	/*
	Returns the root of this tree*/
	node<T>* getRoot() { return root; };

	/*
	Returns a pointer to the data item that is equal to the specified item according to the compare method*/
	T* search(T& item);
	T* searchItemAtMemoryLocation(T*item);

	/*
	Adds the specified item to the tree
	Adapted from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node/*/
	T* add(T& item);
	T* addItemAtMemoryLocation(T* item);
	/*
	Removes the specified item from the tree*/
	void remove(T& item);
	void removeItemAtMemoryLocation(T* item);

	/*
	Returns a string representation of this tree inorder*/
	string inorder();
};

template<typename T>
inline void AVLTree<T>::updateTreeDiffs(node<T>* n)
{
	if (isEmpty(n)) return;

	updateTreeDiffs(n->left);
	updateNodeDiff(n);
	updateTreeDiffs(n->right);
}

template<typename T>
inline int AVLTree<T>::updateNodeDiff(node<T> * n)
{
	if (isEmpty(n)) return 0;

	n->diff = getHeight(n->right) - getHeight(n->left);
	return n->diff;
}

template<typename T>
inline int AVLTree<T>::getHeight(node<T> * n)
{
	if (isEmpty(n)) return 0;

	return (1 + max(getHeight(n->left), getHeight(n->right)));
}

template<typename T>
inline void AVLTree<T>::fixImbalance(node<T> * ancestor, node<T> * added)
{
	if (*ancestor->data < *added->data) {
		//Added node is on right of ancestor
		node<T> * r = ancestor->right;
		if (*r->data < *added->data) {
			dbg "right right heavy\n";
			zag(ancestor);
		}
		else if (*r->data > *added->data) {
			dbg "right left heavy\n";
			zagzig(ancestor);
		}
	}
	else if (*ancestor->data > *added->data) {
		//Added node is on left of ancestor
		node<T> * l = ancestor->left;
		if (*l->data < *added->data) {
			dbg "left right heavy\n";
			zigzag(ancestor);
		}
		else if (*l->data > *added->data) {
			dbg "left left heavy\n";
			zig(ancestor);
		}
	}
}

template<typename T>
inline int AVLTree<T>::max(int a, int b)
{
	if (b > a)
	{
		return b;
	}
	return a;
}

template<typename T>
inline void AVLTree<T>::makeChildNode(node<T>** child, node<T>* _parent, T* _data)
{
	node<T>* result = new node<T>;
	result->parent = _parent;
	result->data = _data;
	result->diff = 0;
	result->left = nullptr;
	result->right = nullptr;
	*child = result;
}

template<typename T>
inline bool AVLTree<T>::isEmpty(node<T> * n)
{
	if (n == nullptr) return true;
	if (n->data == nullptr) return true;
	return false;
}


template<typename T>
inline string AVLTree<T>::inorder(string current, node<T>* n)
{
	if (!isEmpty(n))
	{
		if (n->left != nullptr)
		{
			current += inorder("", n->left);
		}
		current += to_string(*n->data) + ",";
		if (n->right != nullptr)
		{
			current += inorder("", n->right);
		}
	}
	return current;
}

template<typename T>
inline void AVLTree<T>::swap(T * ptrData, T * other)
{
	T temp = *ptrData;
	*ptrData = *other;
	*other = temp;
}

/*
Adapted from notes */
template<typename T>
inline void AVLTree<T>::zig(node<T>* n)
{
	if (isEmpty(n))
	{
		dbg "Called zig on empty tree\n";
		return;
	}
	if (isEmpty(n->left))
	{
		dbg "Called zig on "; dbg *n->data; dbg "but left was empty\n";
		return;
	}

	node<T>* leftChild = (node<T>*) n->left;

	n->left = leftChild->left;
	if (leftChild->left != nullptr) leftChild->left->parent = n;

	leftChild->left = leftChild->right;

	leftChild->right = n->right;
	if (n->right != nullptr) n->right->parent = leftChild;

	n->right = leftChild;
	if (leftChild != nullptr) leftChild->parent = n;

	swap(n->data, leftChild->data);
}

/*
Adapted from notes*/
template<typename T>
inline void AVLTree<T>::zag(node<T>* n)
{
	if (isEmpty(n))
	{
		dbg "Called zag on empty tree\n";
		return;
	}
	if (isEmpty(n->right))
	{
		dbg "Called zag on "; dbg *n->data; ", but right is empty\n";
		return;
	} 
	
	node<T>* rightChild = new node<T>(*n->right);

	n->right = rightChild->right;
	if (rightChild->right != nullptr) rightChild->right->parent = n;

	rightChild->right = rightChild->left;

	rightChild->left = n->left;
	if (n->left != nullptr) n->left->parent = rightChild;

	n->left = rightChild;
	if (rightChild != nullptr) rightChild->parent = n;

	swap(n->data, rightChild->data);
}
/*
Adapted from lectures slides*/
template<typename T>
inline void AVLTree<T>::zigzag(node<T>* n)
{
	if (isEmpty(n))
	{
		dbg "Called zigzag on empty node\n";
		return;
	}
	zag(n->left);
	zig(n);
}

/*
Adapted from lecture slides*/
template<typename T>
inline void AVLTree<T>::zagzig(node<T>* n)
{
	if (isEmpty(n))
	{
		dbg "Called zagzig on empty node";
		return;
	}
	zig(n->right);
	zag(n);
}

template<typename T>
inline AVLTree<T>::AVLTree()
{
	root = nullptr;
	size = 0;
}

template<typename T>
inline AVLTree<T>::AVLTree(AVLTree & other)
{
	root = other.getRoot();
	size = other.getSize();
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
}

template<typename T>
inline T* AVLTree<T>::search(T & item)
{
	node<T>* result;
	try
	{
		find(item, &result);
	}
	catch (AVLItemNotFound e)
	{
		return nullptr;
	}
	return result->data;
}

template<typename T>
inline T* AVLTree<T>::searchItemAtMemoryLocation(T * item)
{
	return search(*item);
}

template<typename T>
inline T* AVLTree<T>::add(T & item)
{
	T* result = nullptr;
	if (root == nullptr)
	{
		dbg "Adding "; dbg item; dbg " at root of tree\n";
		makeChildNode(&root, nullptr, new T(item));
		result = root->data;
	}
	else
	{
		node<T>* n = root;
		while (n != nullptr)
		{
			if (item < *n->data)
			{
				if (n->left == nullptr)
				{
					dbg "Adding "; dbg item; dbg " to left of "; dbg *n->data; dbg "\n";
					makeChildNode(&n->left, n, new T(item));
					n = n->left;
					result = n->data;
					break;
				}
				n = n->left;
			}
			else if (item > *n->data)
			{
				if (n->right == nullptr)
				{
					dbg "Adding "; dbg item; dbg " to right of "; dbg *n->data; dbg "\n";
					makeChildNode(&n->right, n, new T(item));
					n = n->right;
					result = n->data;
					break;
				}
				n = n->right;
			}
			else
			{
				dbg "Node "; dbg *n->data; dbg "exists\n";
				result = n->data;
				break;
			}
		}

		updateTreeDiffs(root);

		node<T>* ancestor = n->parent;

		while (ancestor != nullptr)
		{
			int diff = updateNodeDiff(ancestor);
			if (diff <= -2 || diff >= 2)
			{
				dbg "Imbalance "; dbg diff; dbg " at ancestor "; dbg *ancestor->data; dbg " because of added item "; dbg  *n->data; dbg "\n";
				fixImbalance(ancestor, n);
			}
			ancestor = ancestor->parent;
		}

		updateTreeDiffs(root);
	}
	size++;

	return result;
}

template<typename T>
inline T* AVLTree<T>::addItemAtMemoryLocation(T * item)
{
	return add(*item);
}

template<typename T>
inline void AVLTree<T>::remove(T & item)
{
	node<T>* itemNode;
	find(item, &itemNode);

	node<T>* p = itemNode->parent;

	if (itemNode->left == nullptr && itemNode->right == nullptr)
	{
		if (p != nullptr)
		{
			if (p->left == itemNode) p->left = nullptr;
			else if (p->right == itemNode) p->right = nullptr;
			else throw AVLWrongParent();
		}

		delete itemNode;
	}
	else if (itemNode->left == nullptr)
	{
		*itemNode = *itemNode->right;
		itemNode->parent = p;
	}
	else if (itemNode->right == nullptr)
	{
		*itemNode = *itemNode->left;
		itemNode->parent = p;
	}
	else
	{
		node<T>* greatestLesserValue;
		findGreatestLesserValue(itemNode, &greatestLesserValue);
		itemNode->data = greatestLesserValue->data;

		p = greatestLesserValue->parent;
		if (p != nullptr)
		{
			if (p->left == greatestLesserValue) p->left = nullptr;
			else if (p->right == greatestLesserValue) p->right = nullptr;
			else throw AVLWrongParent();
		}

		delete greatestLesserValue;
	}

	updateTreeDiffs(root);

	size--;
}

template<typename T>
inline void AVLTree<T>::removeItemAtMemoryLocation(T * item)
{
	remove(*item);
}

template<typename T>
inline void AVLTree<T>::find(T & item, node<T>** result)
{
	if (root == nullptr)
	{
		throw AVLItemNotFound();
	}
	else
	{
		node<T>* n = root;
		while (n != nullptr)
		{
			if (item < *n->data)
			{
				n = n->left;
			}
			else if (item > *n->data)
			{
				n = n->right;
			}
			else
			{
				*result = n;
				return;
			}
		}
		throw AVLItemNotFound();
	}
}

template<typename T>
inline void AVLTree<T>::findGreatestLesserValue(node<T> * n, node<T> ** result)
{
	node<T>* c = n->left;
	while (c->right != nullptr)
	{
		c = c->right;
	}
	*result = c;
}


template<typename T>
inline string AVLTree<T>::inorder()
{
	string result = inorder("[", root);
	result.at(result.size() - 1) = ']';

	return result;
}