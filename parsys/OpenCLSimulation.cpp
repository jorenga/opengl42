#include "OpenCLSimulation.hpp"

OpenCLSimulation::OpenCLSimulation(int nbParticles) : _nbParticles(nbParticles)
{
	std::cout << "Init OpenGL Manager" << std::endl;
	this->_glMan = new OpenGLManager(1024, 1024, "ps goodness");
	std::cout << "Init OpenGL Scene" << std::endl;
	this->_glScene = new OpenGLScene(nbParticles);
	this->_glScene->createShaderProg("vs.glsl", "fs.glsl");
	this->_glScene->initVbo();
	std::cout << "Create CL Context" << std::endl;
	this->createContext();
	this->initCLMem(this->_glScene->getVbo());
	this->initSimulation();
	std::cout << "Simulation Initialized" << std::endl;
}

OpenCLSimulation::~OpenCLSimulation()
{
	clReleaseMemObject(this->_particles);
	delete this->_task;
	clReleaseCommandQueue(this->_queue);
	clReleaseContext(this->_ctx);
	delete this->_glScene;
	delete this->_glMan;
}

void							OpenCLSimulation::createContext()
{
	cl_int						err;
	CGLContextObj					kCGLContext = CGLGetCurrentContext();
    CGLShareGroupObj				kCGLShareGroup = CGLGetShareGroup(kCGLContext);

	cl_context_properties			properties[] =
	{
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kCGLShareGroup,
		0
	};

    this->_ctx = clCreateContext(properties, 0, 0, NULL, NULL, &err);
    checkCLError(err, "building context");
    err = clGetContextInfo(this->_ctx, CL_CONTEXT_NUM_DEVICES,
              				sizeof(cl_int), &(this->_deviceNb), NULL);
	checkCLError(err, "context info");

    if (this->_deviceNb < 1) {
		checkCLError(-1, "not enough devices");
    }

    err = clGetContextInfo(this->_ctx,CL_CONTEXT_DEVICES,
						sizeof(cl_device_id), &(this->_device), NULL);
	checkCLError(err, "binding context to device");

	this->_queue = clCreateCommandQueue(this->_ctx, this->_device, 0, &err);
	checkCLError(err, "creating command queue");
}

void					OpenCLSimulation::initSimulation()
{
	std::cout << "Create pInit Task" << std::endl;
	this->_task = new OpenCLTaskPInit(this->_nbParticles);
	this->_task->initTask(this->_ctx, this->_device,
							"kernels/initParticles.cl", "initParticles");
	this->_task->setKernelArg(this->_particles);
}

void					OpenCLSimulation::launchSimulation()
{
	this->acquireGLObject();
	this->_task->execKernel(this->_queue);
	this->releaseGLObject();
	clFinish(this->_queue);
}

void					OpenCLSimulation::runSimulation()
{
	std::cout << "launch Simulation" << std::endl;
	this->launchSimulation();

	std::cout << "Start Loop" << std::endl;
	while (!this->_glMan->shouldClose())
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		this->_glScene->drawScene(this->_viewMatrix, this->_glMan->getProjMat());

		this->_glMan->swap();
		glfwPollEvents();
	}
}

void				OpenCLSimulation::acquireGLObject()
{
	clEnqueueAcquireGLObjects(this->_queue, 1, &(this->_particles), 0, NULL, NULL);
}

void				OpenCLSimulation::releaseGLObject()
{
	clEnqueueReleaseGLObjects(this->_queue, 1, &(this->_particles), 0, NULL, NULL);
}

void				OpenCLSimulation::initCLMem(GLuint vbo)
{
	this->_particles = clCreateFromGLBuffer(this->_ctx, CL_MEM_READ_WRITE, vbo, &(this->_err));
	checkCLError(this->_err, "creating buffer");
}
