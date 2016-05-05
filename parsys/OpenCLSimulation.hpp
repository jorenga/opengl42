#ifndef OPENCLSIMULATION_HPP
# define OPENCLSIMULATION_HPP

# include <vector>
# include <string>
# include "OpenGLManager.hpp"
# include "OpenGLScene.hpp"
# include "OpenCLInc.hpp"
# include "OpenCLError.hpp"
# include "OpenCLTaskPInit.hpp"

class							OpenCLSimulation
{
	public:
								OpenCLSimulation(int nbParticles);
								~OpenCLSimulation();

		void					initSimulation();
		void					launchSimulation();
		void					runSimulation();

	private:
		void					createContext();
		void					acquireGLObject();
		void					releaseGLObject();
		void					initCLMem(GLuint vbo);

	private:
		cl_int					_err;
		cl_context				_ctx;
		cl_command_queue		_queue;
		cl_device_id			_device;
		cl_int					_deviceNb;
		cl_mem					_particles;
		OpenCLTaskPInit*		_task;
		OpenGLManager*			_glMan;
		OpenGLScene*			_glScene;
		OpenGLMatrix			_viewMatrix;

		int						_nbParticles;
};

# endif
