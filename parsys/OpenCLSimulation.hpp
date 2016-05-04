#ifndef OPENCLSIMULATION_HPP
# define OPENCLSIMULATION_HPP

# include <vector>
# include <string>
# include "OpenGLManager.hpp"
# include "OpenGLScene.hpp"
# include "OpenCLInc.hpp"
# include "OpenCLError.hpp"
# include "OpenCLTask.hpp"

class							OpenCLSimulation
{
	public:
								OpenCLSimulation(int nbParticle);
								~OpenCLSimulation();
		void					createContext();

		void					initSimulation();
		void					launchSimulation();
		void					runSimulation();

	private:
		cl_context				_ctx;
		cl_command_queue		_queue;
		cl_device_id			_device;
		cl_int					_deviceNb;
		OpenCLTask*				_task;
		OpenGLManager*			_glMan;
		OpenGLScene*			_glScene;
		OpenGLMatrix			_viewMatrix;

		int						_nbParticle;
};

# endif
