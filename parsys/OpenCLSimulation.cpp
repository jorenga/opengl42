#include "OpenCLSimulation.hpp"

OpenCLSimulation::OpenCLSimulation(int nbParticle) : _nbParticle(nbParticle)
{
	this->createContext();
	this->_glMan = new OpenGLManager(1024, 1024, "ps goodness");
	this->_glScene = new OpenGLScene();
	this->_glScene->createShaderProg("vs.glsl", "fs.glsl");
	this->_glScene->initVbo();
	this->initSimulation();
}

OpenCLSimulation::~OpenCLSimulation() {}

void							OpenCLSimulation::createContext()
{
	cl_uint						platformIdCount = 0;
	cl_uint						deviceIdCount = 0;
	cl_int						error;
	std::vector<cl_platform_id>				platformIds;
	std::vector<cl_device_id>				deviceIds;

	/*	Get Platform And Device		*/
	clGetPlatformIDs(0, nullptr, &platformIdCount);
	platformIds.resize(platformIdCount);
	clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);

	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceIdCount);
	deviceIds.resize(deviceIdCount);
	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, deviceIdCount, deviceIds.data(), nullptr);
	this->_device = deviceIds[0];

	/*	Create context		*/
	const cl_context_properties		contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		reinterpret_cast<cl_context_properties>(platformIds[0]),
		0, 0
	};

	this->_ctx = clCreateContext(contextProperties, deviceIdCount, &(this->_device),
									nullptr, nullptr, &error);
	checkCLError(error, "building context");

	/*	Create Command Queue	*/
	this->_queue = clCreateCommandQueue(this->_ctx, this->_device, 0, &error);
	checkCLError(error, "creating command queue");
}

void					OpenCLSimulation::initSimulation()
{
	this->_task = new OpenCLTask();
	this->_task->createProgram("program.cl", this->_ctx, this->_device);
	this->_task->createKernel("init");
	this->_task->setKernelArg(this->_ctx, this->_glScene->getVbo());
}

void					OpenCLSimulation::launchSimulation()
{
	this->_task->launchKernel(this->_queue);
}

void					OpenCLSimulation::runSimulation()
{
	this->launchSimulation();

	while (this->_glMan->shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		this->_glScene->drawScene(this->_viewMatrix, this->_glMan->getProjMat());

		this->_glMan->swap();
		glfwPollEvents();
	}
}
