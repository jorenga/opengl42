#include "OpenCLTask.hpp"

OpenCLTask::OpenCLTask(int nbParticle) : _nbParticle(nbParticle) {}

OpenCLTask::~OpenCLTask() {
	clReleaseMemObject(this->_particles);
}

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
	this->_err = clBuildProgram(this->_program, 0, NULL, "-Werror", NULL, NULL);
	if (this->_err != CL_SUCCESS) {
		clGetProgramBuildInfo(this->_program, device, CL_PROGRAM_BUILD_LOG, sizeof(log), log, NULL);
		std::cerr << "Error on compilation(" << "program.cl" << "):" << std::endl;
		std::cerr << log << std::endl;
	}
}

void			OpenCLTask::createKernel(std::string fnName, cl_device_id device)
{
	this->_kernel = clCreateKernel(this->_program, fnName.c_str(), &(this->_err));
	checkCLError(this->_err, "creating kernel");
	this->_err = clGetKernelWorkGroupInfo(
			this->_kernel,
			device,
			CL_KERNEL_WORK_GROUP_SIZE,
			sizeof(this->_localWorkSize),
			&(this->_localWorkSize),
			NULL);
	checkCLError(this->_err, "Getting work group info");

	this->_nbWorkGroup = this->_nbParticle / this->_localWorkSize + 1;
	this->_globalWorkSize = this->_nbWorkGroup * this->_localWorkSize;
}

void			OpenCLTask::setKernelArg(cl_context ctx, GLuint vbo)
{
	std::cout << "create buffer: "<< vbo  << std::endl;
	this->_particles = clCreateFromGLBuffer(ctx, CL_MEM_READ_WRITE, vbo, &(this->_err));
//	this->_particles = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizeof(cl_float) * 1024, NULL, &(this->_err));
	checkCLError(this->_err, "creating buffer");

	std::cout << "set arg" << std::endl;
	this->_err = clSetKernelArg(this->_kernel, 0, sizeof(cl_mem), &(this->_particles));
	checkCLError(this->_err, "setting kernel arg");
}

void			OpenCLTask::launchKernel(cl_command_queue queue)
{
//	size_t									global_size = nbParticle;

	printf("global: %lu\nlocal: %lu\n", (this->_globalWorkSize), (this->_localWorkSize));
	this->_err = clEnqueueNDRangeKernel(queue, this->_kernel, 1, NULL,
										&(this->_globalWorkSize), &(this->_localWorkSize),
										0, NULL, NULL); 
	checkCLError(this->_err, "enqueuing kernel");
}

void			OpenCLTask::acquireGLObject(cl_command_queue queue)
{
	clEnqueueAcquireGLObjects(queue, 1, &(this->_particles), 0, NULL, NULL);
}

void			OpenCLTask::releaseGLObject(cl_command_queue queue)
{
	clEnqueueReleaseGLObjects(queue, 1, &(this->_particles), 0, NULL, NULL);
}

void			OpenCLTask::readMem(cl_command_queue queue, GLuint nbParticle)
{
	std::vector<float>	out(nbParticle*4);

	this->_err = clEnqueueReadBuffer(queue, this->_particles, CL_TRUE, 0, 
			sizeof(float)*4*nbParticle, out.data(), 0, NULL, NULL);
	checkCLError(this->_err, "reading buffer");

	for (float f : out) {
		for (int i = 0 ; i < 4 ; i++) {
			std::cout << f << " ";
		}
		std::cout << std::endl;
	}
}
