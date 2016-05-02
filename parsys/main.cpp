# include "OpenCLSimulation.hpp"

int						main()
{
	OpenCLSimulation	*sim = new OpenCLSimulation();
	
	sim->createContext();
	sim->initSimulation();
	sim->launchSimulation();
	sim->printResult();
	return (0);
}
