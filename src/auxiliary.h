/*
 * auxiliary.h
 *
 *  Created on: May 13, 2016
 *      Author: littlegirle
 */

#ifndef AUXILIARY_H_
#define AUXILIARY_H_


#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class PathList
{
// -----------------------------
// Attributes
// -----------------------------
	public:
		int			pointX;
		int			pointY;
		PathList	*next;

// -----------------------------
// Builder
// -----------------------------
	public:
		PathList(int x, int y)
		{
			this->pointX	= x;
			this->pointY	= y;
			this->next		= NULL;
		}
		~PathList()
		{
			if (this->next != NULL)
				delete this->next;
		}
};


	void printFatalError(const char *functionName, const char *errorMsg);


#endif /* AUXILIARY_H_ */
