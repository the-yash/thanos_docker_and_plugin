#include<iostream>
#include<bits/stdc++.h>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>  

#include "adapter.h"

//Memory class for calling memory-related metrics from client side.
class memory{
	public:
	
	adapter_mem obj;

	void total(){
		obj.total();
	}
	void used(){
		obj.used();
	}
	void available(){
		obj.available();
	}
	void total_swap(){
		obj.total_swap();
	}
	void used_swap(){
		obj.used_swap();
	}
	void available_swap(){
		obj.available_swap();
	}
};

//CPU class for calling memory-related metrics from client side.


class cpu{

	public:

	adapter_cpu obj;	

	void busy(){
		obj.busy();
	}

	void user(){
		obj.user();
	}

	void total(){
		obj.total();
	}

	void idle(){
		obj.idle();
	}
	void system(){
		obj.system();
	}
};

//main function for calling the metrics

int main(int argc, char *argv[]) {
	while(1==1){
		memory obj1;
		cpu obj2;
		obj1.total();
		obj1.used();
		obj1.available();
		obj1.total_swap();
		obj1.available_swap();
		obj2.idle();
		obj2.busy();
		obj2.user();
		obj2.system();
		obj2.total();
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
}
