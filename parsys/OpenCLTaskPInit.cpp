#include "OpenCLTaskPInit.hpp"

OpenCLTaskPInit::OpenCLTaskPInit(int nbParticles) : OpenCLTask(nbParticles)
{
	float			pPerLine;

	pPerLine = std::pow(nbParticles, 1.0f / 3.0f);
	std::cout << "pPerLine = " << pPerLine << std::endl;
	this->_defineOptions.insert(t_makePair("PPERLINE", std::to_string(pPerLine) + "f"));
}

OpenCLTaskPInit::~OpenCLTaskPInit() {}

void			OpenCLTaskPInit::setKernelArg(cl_mem particles)
{
	this->_err = clSetKernelArg(this->_kernel, 0, sizeof(cl_mem), &particles);
	checkCLError(this->_err, "setting kernel arg");
}
