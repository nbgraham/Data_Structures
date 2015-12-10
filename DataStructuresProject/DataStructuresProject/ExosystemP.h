#pragma once

#include <ostream>
#include "Exosystem.h"

class ExosystemP
{
public:
	ExosystemP();
	ExosystemP(Exosystem* p);
	ExosystemP(ExosystemP& other);
	~ExosystemP();

	Exosystem* ptr;

	bool isNull();
	bool operator<(ExosystemP other);
	bool operator>(ExosystemP other);
	friend ostream& operator<<(ostream& os, ExosystemP& p)
	{
		return os << *p.ptr;
	};
};

inline ExosystemP::ExosystemP()
{
	ptr = nullptr;
}

inline ExosystemP::ExosystemP(Exosystem * p)
{
	ptr = p;
}

inline ExosystemP::ExosystemP(ExosystemP & other)
{
	ptr = other.ptr;
}

inline ExosystemP::~ExosystemP()
{
	ptr = nullptr;
}

inline bool ExosystemP::isNull()
{
	return ptr == nullptr;
}

inline bool ExosystemP::operator<(ExosystemP other)
{
	return ptr->getStarName() < other.ptr->getStarName();
}

inline bool ExosystemP::operator>(ExosystemP other)
{
	return ptr->getStarName() > other.ptr->getStarName();

}
