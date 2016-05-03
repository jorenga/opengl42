#include "OpenCLTask.hpp"

OpenCLTask::OpenCLTask() {}

OpenCLTask::~OpenCLTask() {}

const char		*getSourceContent(std::string filename)
{
	std::ifstream   ifs(filename);
	std::string     *content;

	content = new std::string(std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>());
	return content->c_str();
}

void			OpenCLTask::createProgram(std::string filename, cl_context ctx, cl_device_id device)
{
	const char	*content;
	char		log[16384];

	content = getSourceContent(filename);
	this->_program = clCreateProgramWithSource(ctx, 1, &content, NULL, &(this->_err));
	checkCLError(this->_err, "creating program");
	this->_err = clBuildProgram(this->_program, 0, NULL, NULL, NULL, NULL);
	if (this->_err != CL_SUCCESS) {
		clGetProgramBuildInfo(this->_program, device, CL_PROGRAM_BUILD_LOG, sizeof(log), log, NULL);
		std::cerr << "Error on compilation(" << "program.cl" << "):" << std::endl;
		std::cerr << log << std::endl;
	}
}

void			OpenCLTask::createKernel(std::string fnName)
{
	this->_kernel = clCreateKernel(this->_program, fnName.c_str(), &(this->_err));
	checkCLError(this->_err, "creating kernel");
}

void			OpenCLTask::setKernelArg(cl_context ctx, GLuint vbo)
{

	this->_particles = clCreateFromGLBuffer(ctx, CL_MEM_READ_WRITE, vbo, &(this->_err));
	checkCLError(this->_err, "creating buffer");

	// Kernel arg
	this->_err = clSetKernelArg(this->_kernel, 0, sizeof(cl_mem), &(this->_particles));
	checkCLError(this->_err, "setting kernel arg");
}

void			OpenCLTask::launchKernel(cl_command_queue queue, GLuint nbParticle)
{
	size_t									global_size = nbParticle;

	this->_err = clEnqueueNDRangeKernel(queue, this->_kernel, 1, NULL, &global_size, 
			NULL, 0, NULL, NULL); 
	checkCLError(this->_err, "enqueuing kernel");
}
