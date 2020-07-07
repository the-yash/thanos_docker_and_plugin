/* To limit definition of header files to one instance */
#ifndef ADAPTER_H
#define ADAPTER_H

#include "PageRequest.h"

class adapter_mem{
	public:

	std::string page;
	std::string out_file;
	PageRequest obj;

	adapter_mem();
	void total();
	void used();
	void available();
	void total_swap();	
	void used_swap();
	void available_swap();
};

class adapter_cpu{

	public:

	std::string page ;
	std::string out_file;
	PageRequest obj;	

	adapter_cpu();
	void busy();

	void user();

	void total();

	void idle();
	void system();
};

#endif