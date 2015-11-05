#pragma once
#include <string>
using namespace std;
#include "LinkedHashTable.h"

class TestObj
{
public:
	string s;
	int n;
	double d;

	TestObj() {
		n = 0;
		d = 0;
		s = "";
	};
	TestObj(int n, double d, string s) {
		this->n = n;
		this->s = s;
		this->d = d;
	};

	bool operator!=(TestObj& other) const {
		if (n == other.n && d == other.d && s == other.s) return false;
		return true;
	}

	bool operator==(TestObj& other) const {
		if (n == other.n && d == other.d && s == other.s) return true;
		return false;
	}

	friend ostream& operator<<(ostream& os, TestObj& obj)
	{
		os << obj.n << " " << obj.d << " " << obj.s;
		return os;
	};
};

class TestLH : public LinkedHashTable<TestObj, string>
{
protected:
	int hash(string key) override;
	string getKey(TestObj& data) override;
public:
	TestLH() : LinkedHashTable<TestObj, string>() {};
	TestLH(int buckets) : LinkedHashTable<TestObj, string>(buckets) {};
};

string TestLH::getKey(TestObj & data)
{
	return data.s;
}

inline int TestLH::hash(string key)
{
	unsigned long hash = 5381;
	int c;

	for (unsigned int i = 0; i < key.length(); ++i)
	{
		c = key[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash%buckets;
}
