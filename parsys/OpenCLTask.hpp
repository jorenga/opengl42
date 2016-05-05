#ifndef OPENCLTASK_HPP
# define OPENCLTASK_HPP

# include <string>
# include <fstream>
# include <iostream>
# include <vector>
# include "OpenGLInc.hpp"
# include "OpenCLInc.hpp"
# include "OpencLError.hpp"

class							OpenCLTask
{
	public:
								OpenCLTask(int nbParticle);
								~OpenCLTask();
		void					createProgram(std::string filename, cl_context ctx, cl_device_id device);
		void					createKernel(std::string fnName, cl_device_id device);
		void					setKernelArg(cl_context ctx, GLuint vbo, cl_mem particles);
		void					launchKernel(cl_command_queue queue);
	//	void					acquireGLObject(cl_command_queue queue);
	//	void					releaseGLObject(cl_command_queue queue);

	private:
		cl_int					_err;
		cl_program				_program;
		cl_kernel				_kernel;
//		cl_mem					_particles;
		int						_nbParticle;
		size_t					_localWorkSize;
		size_t					_globalWorkSize;
		size_t					_nbWorkGroup;
};

#endif
