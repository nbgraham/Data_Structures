/*
Inspired from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node/
*/

#pragma once
#include <string>
#include <exception>

#ifdef DEBUG
#define dbg  printf
#else
#define dbg   if(0)
#endif

class AVLTreeException : public exception {};
class AVLItemNotFound : AVLTreeException {};
class AVLWrongParent : AVLTreeException {};
class AVLEmptyTree : AVLTreeException {};

template <typename T>
class AVLTree
{
protected:
	/*
	A structure for each node in an AVL Tree of type T*/
	struct node {
		T* data;
		/*
		height on right minus height on left*/
		int diff;
		node* left;
		node* right;
		node* parent;
	};

	/*
	The root of this tree*/
	node* root;
	/*
	Number of entries in this tree*/
	int size;

	/*
	Returns the root of this tree*/
	node* getRoot() { return root; };
	/*
	Returns true if the the pointer is null or the node has no data*/
	bool isEmpty(node* n);

	/*
	Compares two values of type T
	Returns -1 if item < other
	Returns 0 if item == other
	Returns 1 if item > other*/
	virtual int compare(T& item, T& other);
	/*
	Returns the max of two numbers*/
	int max(int a, int b);

	/*
	Updates all diffs below the specified node*/
	void updateTreeDiffs(node* n);
	/*
	Updates the diff at the specified node*/
	int updateNodeDiff(node* n);
	/*
	Gets the height of the tree starting at the specified node*/
	int getHeight(node* n);
	/*
	Fixes any imbalance, based on the situation represented by the ancestor and added nodes
	Adapted from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node/*/
	void fixImbalance(node* ancestor, node* added);

	/*
	Creates a child node of _parent with _data as the data and places it in child (output)*/
	void makeChildNode(node** child, node* _parent, T* _data);
	

	/*
	Finds the node that contains itema and places it in result (output)*/
	void find(T& item, node** result);
	/*
	Finds the node with the greatest value less than n and places it in result (output)*/
	void findGreatestLesserValue(node* n, node** result);
	
	/*
	Recurisve call inorder on the specified node, buidling up current*/
	string inorder(string current, node* n);

	/*
	Swaps the values in the two memory locations*/
	void swap(T* ptrData, T* other);
	/*
	Clockwise rotation about n
	left left case*/
	void zig(node* n);
	/*
	Counter-clockwise rotation about n
	right right case*/
	void zag(node* n);
	/*
	left right case*/
	void zigzag(node* n);
	/*
	right left case*/
	void zagzig(node * n);
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
	Returns a pointer to the data item that is equal to the specified item according to the compare method*/
	T* search(T& item);
	/*
	Adds the specified item to the tree
	Adapted from https://cskill.wordpress.com/2012/09/02/avl-tree-with-parent-node/*/
	void add(T& item);
	/*
	Removes the specified item from the tree*/
	void remove(T& item);

	/*
	Returns a string representation of this tree inorder*/
	string inorder();
};

template<typename T>
inline int AVLTree<T>::compare(T & item, T & other)
{
	if (item < other) return -1;
	else if (item > other) return 1;
	else return 0;
}

template<typename T>
inline void AVLTree<T>::updateTreeDiffs(node* n)
{
	if (isEmpty(n)) return;

	updateTreeDiffs(n->left);
	updateNodeDiff(n);
	updateTreeDiffs(n->right);
}

template<typename T>
inline int AVLTree<T>::updateNodeDiff(node * n)
{
	if (isEmpty(n)) return 0;

	n->diff = getHeight(n->right) - getHeight(n->left);
	return n->diff;
}

template<typename T>
inline int AVLTree<T>::getHeight(node * n)
{
	if (isEmpty(n)) return 0;

	return (1 + max(getHeight(n->left), getHeight(n->right)));
}

template<typename T>
inline void AVLTree<T>::fixImbalance(node * ancestor, node * added)
{
	dbg("ancestor data:%d added data:%d\n", *ancestor->data, *added->data);
	if (compare(*ancestor->data, *added->data) < 0) {
		//Added node is on right of ancestor
		node * r = ancestor->right;
		if (compare(*r->data, *added->data) < 0) {
			dbg("right right heavy\n");
			zag(ancestor);
		}
		else if (compare(*r->data, *added->data) > 0) {
			dbg("right left heavy\n");
			zagzig(ancestor);
		}
	}
	else if (compare(*ancestor->data, *added->data) > 0) {
		//Added node is on left of ancestor
		node * l = ancestor->left;
		if (compare(*l->data, *added->data) < 0) {
			dbg("left right heavy\n");
			zigzag(ancestor);
		}
		else if (compare(*l->data, *added->data) > 0) {
			dbg("left left heavy\n");
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
inline void AVLTree<T>::makeChildNode(node** child, node* _parent, T* _data)
{
	node* result = new node;
	result->parent = _parent;
	result->data = _data;
	result->diff = 0;
	result->left = nullptr;
	result->right = nullptr;
	*child = result;
}

template<typename T>
inline bool AVLTree<T>::isEmpty(node * n)
{
	if (n == nullptr) return true;
	if (n->data == nullptr) return true;
	return false;
}


template<typename T>
inline string AVLTree<T>::inorder(string current, node* n)
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
inline void AVLTree<T>::zig(node* n)
{
	if (isEmpty(n))
	{
		dbg("Called zig on empty tree\n");
		return;
	}
	if (isEmpty(n->left))
	{
		dbg("Called zig on %d, but left was empty\n", *n->data);
		return;
	}

	node* leftChild = (node*) n->left;

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
inline void AVLTree<T>::zag(node* n)
{
	if (isEmpty(n))
	{
		dbg("Called zag on empty tree\n");
		return;
	}
	if (isEmpty(n->right))
	{
		dbg("Called zag on %d, but right is empty\n",*n->data);
		return;
	} 
	
	node* rightChild = new node(*n->right);

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
inline void AVLTree<T>::zigzag(node* n)
{
	if (isEmpty(n))
	{
		dbg("Called zigzag on empty node\n");
		return;
	}
	zag(n->left);
	zig(n);
}

/*
Adapted from lecture slides*/
template<typename T>
inline void AVLTree<T>::zagzig(node* n)
{
	if (isEmpty(n))
	{
		dbg("Called zagzig on empty node");
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
inline T * AVLTree<T>::search(T & item)
{
	node* result;
	find(item, &result);
	return result->data;
}

template<typename T>
inline void AVLTree<T>::add(T & item)
{
	if (root == nullptr)
	{
		dbg("Adding %d at root of tree\n", item);
		makeChildNode(&root, nullptr, new T(item));
	}
	else
	{
		node* n = root;
		while (n != nullptr)
		{
			if (compare(item, *n->data) < 0)
			{
				if (n->left == nullptr)
				{
					dbg("Adding %d to left of %d\n", item, *n->data);
					makeChildNode(&n->left, n, new T(item));
					n = n->left;
					break;
				}
				n = n->left;
			}
			else if (compare (item, *n->data) > 0)
			{
				if (n->right == nullptr)
				{
					dbg("Adding %d to right of %d\n", item, *n->data);
					makeChildNode(&n->right, n, new T(item));
					n = n->right;
					break;
				}
				n = n->right;
			}
			else
			{
				dbg("Node %d exists\n", *n->data);
				break;
			}
		}

		updateTreeDiffs(root);

		node* ancestor = n->parent;

		while (ancestor != nullptr)
		{
			int diff = updateNodeDiff(ancestor);
			if (diff <= -2 || diff >= 2)
			{
				dbg("Imbalance %d at ancestor %d because of added item %d\n", diff, *ancestor->data, *n->data);
				fixImbalance(ancestor, n);
			}
			ancestor = ancestor->parent;
		}

		updateTreeDiffs(root);
	}
	size++;
}

template<typename T>
inline void AVLTree<T>::remove(T & item)
{
	node* itemNode;
	find(item, &itemNode);

	node* p = itemNode->parent;

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
		node* greatestLesserValue;
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
inline void AVLTree<T>::find(T & item, node** result)
{
	if (root == nullptr)
	{
		throw AVLItemNotFound();
	}
	else
	{
		node* n = root;
		while (n != nullptr)
		{
			if (compare(item, *n->data) < 0)
			{
				n = n->left;
			}
			else if (compare(item, *n->data) > 0)
			{
				n = n->right;
			}
			else
			{
				*result = n;
				return;
			}
		}
	}
}

template<typename T>
inline void AVLTree<T>::findGreatestLesserValue(node * n, node ** result)
{
	node* c = n->left;
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