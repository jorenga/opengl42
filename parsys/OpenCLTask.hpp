#ifndef OPENCLTASK_HPP
# define OPENCLTASK_HPP

# include <string>
# include <fstream>
# include <iostream>
# include <vector>
# include "OpenCLInc.hpp"
# include "OpencLError.hpp"

class							OpenCLTask
{
	public:
								OpenCLTask();
								~OpenCLTask();
		void					createProgram(std::string filename, cl_context ctx, cl_device_id device);
		void					createKernel(std::string fnName);
		void					setKernelArg(cl_context ctx);
		void					launchKernel(cl_command_queue queue);
		void					readOut(cl_command_queue queue);

	private:
		cl_int					_err;
		cl_program				_program;
		cl_kernel				_kernel;
		cl_mem					_inBuf;
};

#endif
