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

class TestLH : public LinkedHashTable<TestObj, int>
{
protected:
	int hash(int key) override;
	int getKey(TestObj& data) override;
public:
	TestLH() : LinkedHashTable<TestObj, int>() {};
	TestLH(int buckets) : LinkedHashTable<TestObj, int>(buckets) {};
};

int TestLH::getKey(TestObj & data)
{
	return data.n;
}

inline int TestLH::hash(int key)
{
	return key%buckets;
}
