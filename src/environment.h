/*
 * environment.h
 *
 *  Created on: May 2, 2016
 *      Author: littlegirle
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "auxiliary.h"
#include "nodeList.h"





#define NBR_NEIGHBOR		4
#define NEIGHBOR_SHIFT_X	{0,  -1, 1, 0}
#define NEIGHBOR_SHIFT_Y	{-1, 0,  0, 1}

#define CHAR_OBSTACLE		'0'
#define CHAR_PATH			'+'


class Environment
{
// -----------------------------
// Attributes
// -----------------------------
	private:
		int			initialPositionX;
		int			initialPositionY;
		int			finalPositionX;
		int			finalPositionY;
		int			dimX;
		int			dimY;
		char*		matrix;
		PathList	*pathList;

// -----------------------------
// Builder
// -----------------------------
	public:
		Environment(const char *fileName);
		~Environment();

// -----------------------------
// Getter / Setter
// -----------------------------
	public:
		char		isFinalPoint	(int x, int y);
		char		isInitialPoint	(int x, int y);
		char		isObstacle		(int x, int y);
		char		isInEnvironment	(int x, int y);
		void		setObjective	(int initialX, int initialY, int finalX, int finalY);
		int			getDimX			();
		int			getDimY			();

// -----------------------------
// Local methods
// -----------------------------
	public:
		int 		findPath		();
		char		getCellValue	(int x, int y);
		char*		getCellAddr		(int x, int y);
		int			heuristic		(int pointX, int pointY);
		void		print			();
		void		printPath		();

// -----------------------------
// Auxiliary methods
// -----------------------------
	private:
		PathList*	buildPath		(NodeList *closeList);
		char		isInPath		(int x, int y);
};


#endif
