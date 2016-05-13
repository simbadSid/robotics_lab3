/*
 * auxiliary.cc
 *
 *  Created on: May 13, 2016
 *      Author: littlegirle
 */

#include "auxiliary.h"


void printFatalError(const char *functionName, const char *errorMsg)
{
	std::cout << "*********************************************************\n";
	std::cout << "Fatal error in the function: " << functionName << "\n";
	std::cout << errorMsg << "\n";
	std::cout << "*********************************************************\n";

	exit(0);
}

