/*
 * environment.cc
 *
 *  Created on: May 2, 2016
 *      Author: littlegirle
 */

#include "environment.h"




// -----------------------------
// Builder
// -----------------------------
	Environment::Environment(const char *fileName)
	{
		FILE *fic;
		int x, y;

		fic = fopen(fileName, "r");
		if (fic == NULL)
		{
			printFatalError("Environment", "Can't find the input environment file");
		}

		fscanf(fic, "%d %d\n", &this->dimX, &this->dimY);
		this->matrix = (char*)malloc ((this->dimX*this->dimY) * sizeof(char));

		for (y=0; y<this->dimY; y++)
		{
			for (x=0; x<this->dimX; x++)
			{
				fscanf(fic, "%c ", this->getCellAddr(x, y));
			}
		}
		fclose(fic);

		this->initialPositionX	= -1;
		this->initialPositionY	= -1;
		this->finalPositionX	= -1;
		this->finalPositionY	= -1;
		this->pathList			= NULL;

	}

	Environment::~Environment()
	{
		free(this->matrix);
		if (this->pathList != NULL)
			delete this->pathList;
	}

// -----------------------------
// Getter / Setter
// -----------------------------
	void Environment::setObjective(int initialX, int initialY, int finalX, int finalY)
	{
		if (!this->isInEnvironment(initialX, initialY))
			printFatalError("SetObjective", "Initial point out of the environment");
		if (!this->isInEnvironment(finalX, finalY))
			printFatalError("SetObjective", "Final point out of the environment");
		if (this->isObstacle(initialX, initialY))
			printFatalError("SetObjective", "Initial point on obstacle");

		this->initialPositionX	= initialX;
		this->initialPositionY	= initialY;
		this->finalPositionX	= finalX;
		this->finalPositionY	= finalY;
	}

	char Environment::isInEnvironment(int x, int y)
	{
		if ((x < 0) || (x >= this->dimX)) return 0;
		if ((y < 0) || (y >= this->dimY)) return 0;
		return 1;
	}

	char Environment::isObstacle(int x, int y)
	{
		return (this->getCellValue(x, y) == CHAR_OBSTACLE);
	}

	char Environment::isInitialPoint(int x, int y)
	{
		return ((x == this->initialPositionX) && (y == this->initialPositionY));
	}

	char Environment::isFinalPoint(int x, int y)
	{
		return ((x == this->finalPositionX) && (y == this->finalPositionY));
	}

	int Environment::getDimX()
	{
		return this->dimX;
	}

	int Environment::getDimY()
	{
		return this->dimY;
	}

// -----------------------------
// Local methods
// -----------------------------
	/**
	 * Find an optimal path between the source and the destination points.
	 * Uses the A* algorithm.
	 * Put the result path TODO
	 */
	int Environment::findPath()
	{
		NodeList *openList	= new NodeList();
		NodeList *closeList	= new NodeList(), *neighborNode;
		int x, y, previousX, previousY, previousCost, heuristicCost, i, xNeighbor, yNeighbor;
		char neighborShiftX[] = NEIGHBOR_SHIFT_X;
		char neighborShiftY[] = NEIGHBOR_SHIFT_Y;

		openList->insert(this->initialPositionX, this->initialPositionY, -1, -1, 0, this->heuristic(this->initialPositionX, this->initialPositionY));

		while(!openList->isEmpty())
		{
			openList->popFirst(&x, &y, &previousX, &previousY, &previousCost, &heuristicCost);
			closeList->insert(x, y, previousX, previousY, previousCost, heuristicCost);
			if (this->isFinalPoint(x, y))
			{

				this->pathList = this->buildPath(closeList, x, y);
				openList->freeList();
				closeList->freeList();
				delete openList;
				delete closeList;
				return 1;
			}
			for (i =0; i<NBR_NEIGHBOR; i++)
			{
				xNeighbor = x + neighborShiftX[i];
				yNeighbor = y + neighborShiftY[i];
				if ((!this->isInEnvironment(xNeighbor, yNeighbor)) || (this->isObstacle(xNeighbor, yNeighbor)))
				{
					continue;
				}
				if (closeList->isInList(xNeighbor, yNeighbor, NULL))
				{
					continue;
				}

				int	neighborHeuristic	= this->heuristic(xNeighbor, yNeighbor);
				int	neighborCost		= previousCost + this->getCellValue(xNeighbor, yNeighbor);
				bool test				= openList->isInList(xNeighbor, yNeighbor, &neighborNode);
				if (!test)
				{
					openList->insert(xNeighbor, yNeighbor, x, y, neighborCost, neighborHeuristic);
				}
				else if (neighborNode->getPreviousCost() > neighborCost)
				{
					neighborNode->setPreviousCost(neighborCost);
					neighborNode->setPreviousPoint(x, y);
				}
			}
		}

		return 0;
	}

	/**
	 * Return the value of a cell of the environment
	 */
	char Environment::getCellValue(int x, int y)
	{
		return *(this->getCellAddr(x, y));
	}

	/**
	 * Return the address within the matrix of a cell of the environment
	 */
	char* Environment::getCellAddr(int x, int y)
	{
		return (this->matrix + (y*this->dimX) + x);
	}

	/**
	 * Return an approximation of the path from the input point to the destination.
	 */
	int Environment::heuristic (int pointX, int pointY)
	{
		int x = this->finalPositionX - pointX;
		int y = this->finalPositionY - pointY;

		return sqrt(x*x + y*y);
	}

	/**
	 * Print the hole environment
	 */
	void Environment::print()
	{
		int x, y;

		if (this->finalPositionX < 0)
		{
			std::cout << "- Not initialized\n";
		}
		else
		{
			std::cout << "- Initial Position: (x = " << this->initialPositionX << ", \ty = " << this->initialPositionY << ")\n";
			std::cout << "- Final Position:   (x = " << this->finalPositionX << ", \ty = " << this->finalPositionY << ")\n";
		}
		std::cout << "- Environment: \n";
		for(y=0; y<this->dimY; y++)
		{
			std::cout << "\t";
			for(x=0; x<this->dimX; x++)
			{
				if (this->isInitialPoint(x, y))
					std::cout << CHAR_INITIAL << " ";
				else if (this->isFinalPoint(x, y))
					std::cout << CHAR_FINAL << " ";
				else
					std::cout << this->getCellValue(x, y) << " ";
			}
			std::cout << "\n";
		}
	}

	void Environment::printPath()
	{
		if (this->finalPositionX < 0)
		{
			std::cout << "- Not initialized\n";
			return;
		}
		if (this->pathList == NULL)
		{
			std::cout << "- No path computed\n";
		}
		else
		{
			std::cout << "- Optimal path in term of distance and quality\n";
			int x, y;
			for(y=0; y<this->dimY; y++)
			{
				std::cout << "\t";
				for(x=0; x<this->dimX; x++)
				{
					if (this->isInitialPoint(x, y))
						std::cout << CHAR_INITIAL << " ";
					else if (this->isFinalPoint(x, y))
						std::cout << CHAR_FINAL << " ";
					else if (this->isInPath(x, y))
						std::cout << CHAR_PATH << " ";
					else
						std::cout << this->getCellValue(x, y) << " ";
				}
				std::cout << "\n";
			}
		}
	}

// -----------------------------
// Auxiliary methods
// -----------------------------
	PathList* Environment::buildPath(NodeList *closeList, int x, int y)
	{
		PathList *res = new PathList(x, y);
		NodeList *previousNodeList = NULL;

		if (!this->isInEnvironment(x, y))
		{
			printFatalError("buildPath", "Point out of the environment");
		}

		if (!this->isInitialPoint(x, y))
		{
			char test = closeList->isInList(x, y, &previousNodeList);
			if (!test)
			{
				printFatalError("buildPath", "Can't find the previous point");
			}
			int previousPointX = previousNodeList->getPreviousPointX();
			int previousPointY = previousNodeList->getPreviousPointY();
			res->next = this->buildPath(closeList, previousPointX, previousPointY);
		}

		return res;
	}

	char Environment::isInPath(int x, int y)
	{
		PathList *list = this->pathList;

		while(list != NULL)
		{
			if ((x == list->pointX) && (y == list->pointY))
				return 1;
			list = list->next;
		}

		return 0;
	}
