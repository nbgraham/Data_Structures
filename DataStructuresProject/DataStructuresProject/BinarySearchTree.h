#pragma once
#include <exception>

class BinaryTreeException : public exception {};
class BSTItemNotFound : BinaryTreeException {};
class BSTEmptyTree : BinaryTreeException {};

template <typename T>
class BinarySearchTree
{
protected:
	T* data;
	BinarySearchTree<T>* left;
	BinarySearchTree<T>* right;
	BinarySearchTree<T>* findGreatestValue(BinarySearchTree<T>* tree);
	void clear();
	string inorder(string current);
public:
	BinarySearchTree();
	BinarySearchTree(BinarySearchTree<T>& other);
	~BinarySearchTree();

	bool isEmpty() { return data == nullptr; };

	T* getData() { return data; };
	BinarySearchTree<T>* getLeft() { return left; };
	BinarySearchTree<T>* getRight() { return right; };

	void setData(T* _data) { data = _data; };
	void setLeft(BinarySearchTree<T>* _left) { left = _left; };
	void setRight(BinarySearchTree<T>* _right) { right = _right; };

	void add(T& item);
	void remove(T& item);
	BinarySearchTree<T>* find(T& item);

	string inorder();
};

template<typename T>
inline BinarySearchTree<T>* BinarySearchTree<T>::findGreatestValue(BinarySearchTree<T>* tree)
{		
		BinarySearchTree<T>* result = tree;
		while (result->getRight() != nullptr)
		{
			result = result->getRight();
		}
		return result;
}

template<typename T>
inline void BinarySearchTree<T>::clear()
{
	data = nullptr;
	left = nullptr;
	right = nullptr;
}

template<typename T>
inline string BinarySearchTree<T>::inorder(string current)
{
	if (!isEmpty())
	{
		if (left != nullptr)
		{
			current += left->inorder("");
		}
		current += to_string(*data) + ",";
		if (right != nullptr)
		{
			current += right->inorder("");
		}
	}
	return current;
}

template<typename T>
inline BinarySearchTree<T>::BinarySearchTree()
{
	data = nullptr;
	left = nullptr;
	right = nullptr;
}

template<typename T>
inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& other)
{
	data = other.getData();
	left = other.getLeft();
	right = other.getRight();
}

template<typename T>
inline BinarySearchTree<T>::~BinarySearchTree()
{
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
	if (left != nullptr)
	{
		delete left;
		left = nullptr;
	}
	if (right != nullptr)
	{
		delete right;
		right = nullptr;
	}
}

template<typename T>
inline void BinarySearchTree<T>::add(T& item)
{
	if (isEmpty())
	{
		data = new T(item);
	}
	else if (item < *data)
	{
		if (left == nullptr)
		{
			left = new BinarySearchTree<T>();
		}

		left->add(item);
	}
	else if (item > *data)
	{
		if (right == nullptr)
		{
			right = new BinarySearchTree<T>();
		}

		right->add(item);
	}
}

template<typename T>
inline void BinarySearchTree<T>::remove(T & item)
{
	BinarySearchTree<T>* itemNode = find(item);

	if (itemNode->getLeft() == nullptr && itemNode->getRight() == nullptr)
	{
		itemNode->clear();
	}
	else if (itemNode->getLeft() == nullptr)
	{
		*itemNode = *itemNode->getRight();
	}
	else if (itemNode->getRight() == nullptr)
	{
		*itemNode = *itemNode->getLeft();
	}
	else
	{
		BinarySearchTree<T>* greatestLowerValue = findGreatestValue(itemNode->getLeft());
		itemNode->setData(greatestLowerValue->getData());
		greatestLowerValue->clear();
	}
}

template<typename T>
inline BinarySearchTree<T>* BinarySearchTree<T>::find(T & item)
{
	if (data == nullptr)
	{
		throw BSTItemNotFound();
	}
	else if (*data == item)
	{
		return this;
	}
	else if (item < *data)
	{
		left->find(item);
	}
	else
	{
		right->find(item);
	}
}

template<typename T>
inline string BinarySearchTree<T>::inorder()
{
	string result =  inorder("[");
	result.at(result.size() - 1) = ']';
	return result;
}
