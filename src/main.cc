#include "environment.h"
#include <string.h>


#define ENVIRONMENT_DEFAULT	"resource/default"

#define COMMANDE_SET_ENV			"set_env"
#define COMMANDE_SET_LIMIT_POINT	"set_limit_point"
#define COMMANDE_PRINT				"print"





int main()
{
	Environment *env = new Environment(ENVIRONMENT_DEFAULT);
	char command[100], test;
	int xInit	= env->getDimX()-1;
	int yInit	= env->getDimY()-1;
	int xFin	= 0;
	int yFin	= 0;

	env->setObjective(xInit, yInit, xFin, yFin);
	test = env->findPath();
	while (true)
	{
		if (!test)
		{
			std::cout << "The objective is not reachable\n\n";
		}
		std::cout << "\n\n-----------------------------------------\n";
		std::cout << "Please enter one of the commands:\n";
		std::cout << "\t- " << COMMANDE_PRINT << "\n";
		std::cout << "\t- " << COMMANDE_SET_ENV << "\n";
		std::cout << "\t- " << COMMANDE_SET_LIMIT_POINT << "\n";
		std::cout << "\n\n\tChoice: ";

		scanf("%s", command);
		std::cout << "\n";
		if (!strcmp(command, COMMANDE_SET_ENV))
		{
			scanf("%s", command);
			delete env;
			env = new Environment(command);
			test = env->findPath();
		}
		else if (!strcmp(command, COMMANDE_SET_LIMIT_POINT))
		{
			std::cout << "\t\tInitial Point x = ";
			scanf("%d", &xInit);
			std::cout << "\t\tInitial Point y = ";
			scanf("%d", &yInit);
			std::cout << "\t\tFinal Point x   = ";
			scanf("%d", &xFin);
			std::cout << "\t\tFinal Point y   = ";
			scanf("%d", &yFin);
			env->setObjective(xInit, yInit, xFin, yFin);
			test = env->findPath();
		}
		else if (!strcmp(command, COMMANDE_PRINT))
		{
			env->print();
			env->findPath();
			env->printPath();
		}
		else
		{
			std::cout << "Unknown command";
		}
	}


	delete env;
	return 0;


}
