/*
 * NodeList.h
 *
 *  Created on: May 13, 2016
 *      Author: littlegirle
 */

#ifndef NODELIST_H_
#define NODELIST_H_


#include <stdlib.h>
#include "auxiliary.h"



class NodeList
{
// -----------------------------
// Attributes
// -----------------------------
	private:
		int			pointX;
		int			pointY;
		int			previousPointX;
		int			previousPointY;
		int			previousCost;
		int			heuristicCost;
		NodeList	*next;

// -----------------------------
// Builder
// -----------------------------
	public:
		NodeList();
		NodeList(NodeList *newNode);
		~NodeList();

// -----------------------------
// Getter/Setter
// -----------------------------
	public:
		char	isInList			(int x, int y, NodeList **resultList);
		char	isEmpty				();
		int		getPreviousCost		();
		int		getPointX			();
		int		getPointY			();
		int		getPreviousPointX	();
		int		getPreviousPointY	();
		void	setPreviousCost		(int cost);
		void	setPreviousPoint	(int x, int y);

// -----------------------------
// Local methods
// -----------------------------
	public:
		void	insert			(int x, int y, int prevCost, int heurCost);
		void	popFirst		(int *x, int *y, int *prevCost, int *heurCost);
		void	print			();
};


#endif
