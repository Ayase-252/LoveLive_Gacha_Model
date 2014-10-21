#include <iostream>
#include <sstream>
#include "Simulation.h"

int main(unsigned argc, char **argv)
{
	unsigned trialTime = 5000; //default time of trial
	bool isAlwaysSRDeployed = false; //the flag of the mode where you will always get a SR card
	bool isSlienceModeDepolyed = false; //the flag of the mode prevent the echo of gecha
	for (int i = 1; i != argc; /*empty*/)
	{
		if (argv[i][1] == 't') //the option setting the time of trial
		{
			std::stringstream isstrm(argv[++i]);
			if (!(isstrm >> trialTime))
			{
				std::cerr << "Wrong Argument: The argument of -t isn't a number" << std::endl;
				exit(-1);
			}
			++i;
			continue;
		}

		if (argv[i][1] == 's') //the option indicating the deployment of SR Bouns policy
		{
			isAlwaysSRDeployed = true;
			++i;
			continue;
		}

		if (argv[i][1] == 'S') //the option indicating the deployment of Slience mode
		{
			isSlienceModeDepolyed = true;
			++i;
			continue;
		}
	}
	Simulation sim(trialTime);
	if (isSlienceModeDepolyed)
		std::cout << "Trial is running. Please wait for moment" << std::endl;
	if (isAlwaysSRDeployed)
		sim.Start_Always_SR(isSlienceModeDepolyed);
	else
		sim.Start(isSlienceModeDepolyed);
	std::cout << sim;
	return 0;
}
