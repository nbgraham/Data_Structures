#pragma once
#include "AVLTree.h"
#include "Exosystem.h"

class AVLTreeExosystem : public AVLTree<Exosystem*>
{
protected:
	/*
	Compares two Exosystems based on star name
	Returns -1 if item < other
	Returns 0 if item == other
	Returns 1 if item > other*/
	int compare(Exosystem*& item, Exosystem*& other) override;
};

int AVLTreeExosystem::compare(Exosystem* & item, Exosystem* & other)
{
	string items = item->getStarName();
	string others = other->getStarName();

	return items.compare(others);
}
