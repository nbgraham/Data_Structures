#pragma once

#include "LinkedHashTable.h"

class IntLinkedHashTable : public LinkedHashTable<int, int>
{
protected:
	int hash(int key) override;
	int getKey(int& data) override;
public:
	IntLinkedHashTable() : LinkedHashTable<int, int>() {};
	IntLinkedHashTable(int buckets) : LinkedHashTable<int, int>(buckets) {};
};

int IntLinkedHashTable::hash(int key)
{
	return key%buckets;
}

inline int IntLinkedHashTable::getKey(int& data)
{
	return data;
}


