# include "OpenCLSimulation.hpp"

int						main()
{
	OpenCLSimulation	*sim = new OpenCLSimulation(1024);
	
	std::cout << "==OpenCL Simulation==" << std::endl;
	sim->runSimulation();
	std::cout << "==END==" << std::endl;
	delete sim;
	return (0);
}
