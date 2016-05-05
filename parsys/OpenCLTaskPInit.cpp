#include "OpenCLTaskPInit.hpp"

OpenCLTaskPInit::OpenCLTaskPInit(int nbParticles) : OpenCLTask(nbParticles) {}

OpenCLTaskPInit::~OpenCLTaskPInit() {}

void			OpenCLTaskPInit::setKernelArg(cl_mem particles)
{
	this->_err = clSetKernelArg(this->_kernel, 0, sizeof(cl_mem), &particles);
	checkCLError(this->_err, "setting kernel arg");
}
