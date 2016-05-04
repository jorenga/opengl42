#include "OpenCLSimulation.hpp"

OpenCLSimulation::OpenCLSimulation(int nbParticle) : _nbParticle(nbParticle)
{
	std::cout << "Init OpenGL Manager" << std::endl;
	this->_glMan = new OpenGLManager(1024, 1024, "ps goodness");
	std::cout << "Init OpenGL Scene" << std::endl;
	this->_glScene = new OpenGLScene(nbParticle);
	std::cout << "Create Shader Program" << std::endl;
	this->_glScene->createShaderProg("vs.glsl", "fs.glsl");
	std::cout << "Init Vbo" << std::endl;
	this->_glScene->initVbo();
	std::cout << "Create CL Context" << std::endl;
	this->createContext();
	std::cout << "Init Simulation" << std::endl;
	this->initSimulation();
	std::cout << "Simulation Initialized" << std::endl;
}

OpenCLSimulation::~OpenCLSimulation()
{
	delete this->_task;
	clReleaseCommandQueue(this->_queue);
	clReleaseContext(this->_ctx);
	delete this->_glScene;
	delete this->_glMan;

}

void							OpenCLSimulation::createContext()
{
//	cl_uint						platformIdCount = 0;
//	cl_uint						deviceIdCount = 0;
	cl_int						err;
//	std::vector<cl_platform_id>				platformIds;
//	std::vector<cl_device_id>				deviceIds;
	CGLContextObj					kCGLContext = CGLGetCurrentContext();
    CGLShareGroupObj				kCGLShareGroup = CGLGetShareGroup(kCGLContext);

	/*	Get Platform And Device		*/
/*	clGetPlatformIDs(0, nullptr, &platformIdCount);
	platformIds.resize(platformIdCount);
	clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);

	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceIdCount);
	deviceIds.resize(deviceIdCount);
	clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, deviceIdCount, deviceIds.data(), nullptr);
	this->_device = deviceIds[0];
*/
	/*	Create context		*/
	cl_context_properties			properties[] =
	{
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kCGLShareGroup,
		0
	};

/*	this->_ctx = clCreateContext(properties, 1, &(this->_device),
									nullptr, nullptr, &error);
	checkCLError(error, "building context");
*/


    this->_ctx = clCreateContext(properties, 0, 0, NULL, NULL, &err);
    checkCLError(err, "building context");
    err = clGetContextInfo(this->_ctx,
                CL_CONTEXT_NUM_DEVICES,
                sizeof(cl_int),
                &(this->_deviceNb),
                NULL);
	checkCLError(err, "context info");

    if (this->_deviceNb < 1) {
		checkCLError(-1, "not enough devices");
    }

    err = clGetContextInfo(this->_ctx,
                CL_CONTEXT_DEVICES,
                sizeof(cl_device_id),
                &(this->_device),
                NULL);
	checkCLError(err, "binding context to device");

	/*	Create Command Queue	*/
	this->_queue = clCreateCommandQueue(this->_ctx, this->_device, 0, &err);
	checkCLError(err, "creating command queue");
}

void					OpenCLSimulation::initSimulation()
{
	std::cout << "Create new Task" << std::endl;
	this->_task = new OpenCLTask(this->_nbParticle);
	std::cout << "Create Program" << std::endl;
	this->_task->createProgram("program.cl", this->_ctx, this->_device);
	std::cout << "Create Kernel" << std::endl;
	this->_task->createKernel("init", this->_device);
	std::cout << "Set Kernel Arg" << std::endl;
	this->_task->setKernelArg(this->_ctx, this->_glScene->getVbo());
}

void					OpenCLSimulation::launchSimulation()
{
	this->_task->acquireGLObject(this->_queue);
	this->_task->launchKernel(this->_queue);
//	this->_task->launchKernel(this->_queue, this->_nbParticle);
//	this->_task->readMem(this->_queue, this->_nbParticle);
	this->_task->releaseGLObject(this->_queue);
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
