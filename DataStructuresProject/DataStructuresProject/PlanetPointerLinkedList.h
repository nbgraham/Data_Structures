#pragma once

#include "LinkedListPtrs.h"
#include "Exoplanet.h"

class PlanetPointerLinkedList: public LinkedListPtrs<Exoplanet>
{
public:
	PlanetPointerLinkedList() : LinkedListPtrs<Exoplanet>() {};

	void overwritePlanet(Exoplanet* planet)
	{
		Node<Exoplanet*>* curr = head;
		while (curr != nullptr)
		{
			if (curr->data->getName() == planet->getName())
			{
				curr->data = planet;
				break;
			}
			curr = curr->next;
		}
		if (curr == nullptr) throw exception("Specified planet name was not in the linked list.");
	};
	bool removePlanet(Exoplanet* planet)
	{
		if (head->data->getName() == planet->getName())
		{
			Node<Exoplanet*>* temp = head->next;
			delete head;
			head = temp;

			length--;
			return true;
		}
		else
		{
			Node<Exoplanet*>* prev = head;
			while (prev->next != nullptr)
			{
				if (prev->next->data->getName() == planet->getName())
				{
					Node<Exoplanet*>* temp = prev->next->next;
					delete prev->next;
					prev->next = temp;

					length--;
					return true;
				}
				prev = prev->next;
			}
		}

		return false;
	};
	double calculateMaxPer(void) const
	{
		double maxPer = 0;
		double currPer;
		Node<Exoplanet*>* curr = head;
		while (curr != nullptr)
		{
			currPer = curr->data->getPer();
			if (currPer > maxPer)
			{
				maxPer = currPer;
			}
			curr = curr->next;
		}

		return maxPer;
	};
	double calculateMinPer(void) const
	{
		double minPer = DBL_MAX;
		double currPer;
		Node<Exoplanet*>* curr = head;
		while (curr != nullptr)
		{
			currPer = curr->data->getPer();
			if (currPer < minPer)
			{
				minPer = currPer;
			}
			curr = curr->next;
		}

		return minPer;
	};
	double calculateAverageMsini(void) const
	{
		double sum = 0;
		Node<Exoplanet*>* curr = head;
		while (curr != nullptr)
		{
			sum += curr->data->getMsini();
			curr = curr->next;
		}

		return sum/length;
	};
	bool nameExists(char name) const
	{
		Node<Exoplanet*>* curr = head;
		while (curr != nullptr)
		{
			if (curr->data->getName() == name) return true;
			curr = curr->next;
		}
		return false;
	};
};