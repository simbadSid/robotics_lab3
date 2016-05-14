/*
 * NodeList.cc
 *
 *  Created on: May 13, 2016
 *      Author: littlegirle
 */

#include "nodeList.h"



// -----------------------------
// Builder
// -----------------------------
	NodeList::NodeList()
	{
		this->pointX			= -1;
		this->pointY			= -1;
		this->previousPointX	= -1;
		this->previousPointY	= -1;
		this->previousCost		= -1;
		this->heuristicCost		= -1;
		this->next				= NULL;
	}

	NodeList::NodeList(NodeList *newNode)
	{
		this->pointX			= newNode->pointX;
		this->pointY			= newNode->pointY;
		this->previousPointX	= newNode->previousPointX;
		this->previousPointY	= newNode->previousPointY;
		this->previousCost		= newNode->previousCost;
		this->heuristicCost		= newNode->heuristicCost;
		this->next				= newNode->next;
	}

	NodeList::~NodeList()
	{
	}

// -----------------------------
// Getter/Setter
// -----------------------------
	bool NodeList::isInList(int x, int y, NodeList **resultList)
	{
		if ((x == this->pointX) && (y == this->pointY))
		{
			if (resultList != NULL)
				*resultList = this;
			return true;
		}
		if (this->next == NULL)
			return false;

		return this->next->isInList(x, y, resultList);
	}

	bool NodeList::isEmpty()
	{
		if (this->next != NULL)
			return false;

		return (this->pointX == -1);
	}

	int NodeList::getPreviousCost()
	{
		return this->previousCost;
	}

	int NodeList::getPointX()
	{
		return this->pointX;
	}

	int NodeList::getPointY()
	{
		return this->pointY;
	}

	int NodeList::getPreviousPointX()
	{
		return this->previousPointX;
	}

	int NodeList::getPreviousPointY()
	{
		return this->previousPointY;
	}

	void NodeList::setPreviousCost(int cost)
	{
		this->previousCost = cost;
	}

	void NodeList::setPreviousPoint(int x, int y)
	{
		this->previousPointX = x;
		this->previousPointY = y;
	}

// -----------------------------
// Local methods
// -----------------------------
	void NodeList::insert(int x, int y, int previousX, int previousY, int prevCost, int heurCost)
	{
		if ((this->pointX != -1) && (prevCost > this->previousCost))
		{
			if (this->next == NULL)
				this->next = new NodeList();
			this->next->insert(x, y, previousX, previousY, prevCost, heurCost);
		}
		else
		{
			NodeList *newNode = new NodeList(this);
			this->pointX		= x;
			this->pointY		= y;
			this->previousPointX= previousX;
			this->previousPointY= previousY;
			this->previousCost	= prevCost;
			this->heuristicCost	= heurCost;
			this->next			= newNode;
		}
	}

	void NodeList::popFirst(int *x, int *y, int *previousX, int *previousY, int *prevCost, int *heurCost)
	{
		if (this->isEmpty())
			printFatalError("NodeList::popFirst", "Empty list");

		*x			= this->pointX;
		*y			= this->pointY;
		*previousX	= this->previousPointX;
		*previousY	= this->previousPointY;
		*prevCost	= this->previousCost;
		*heurCost	= this->heuristicCost;

		if (this->next == NULL)
		{
			this->pointX		= -1;
			this->pointY		= -1;
			this->previousPointX= -1;
			this->previousPointY= -1;
			this->previousCost	= -1;
			this->heuristicCost	= -1;
		}
		else
		{
			NodeList *tmpNext = this->next;
			this->pointX		= this->next->pointX;
			this->pointY		= this->next->pointY;
			this->previousPointX= this->next->previousPointX;
			this->previousPointY= this->next->previousPointY;
			this->previousCost	= this->next->previousCost;
			this->heuristicCost	= this->next->heuristicCost;
			this->next			= this->next->next;
			delete (tmpNext);
		}
	}

	void NodeList::print()
	{
		std::cout << "\t Current Point : x = " << this->pointX << ", y = " << this->pointY << "\n";
		std::cout << "\t Previous Point: x = " << this->previousPointX << ", y = " << this->previousPointY << "\n";
		std::cout << "\t Previous cost : " << this->previousCost << "\n";

		if (this->next != NULL)
			this->next->print();
	}

	void NodeList::freeList()
	{
		if (this->next != NULL)
			this->next->freeList();
		delete this->next;
	}
