#include<iostream>
#include<bits/stdc++.h>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>  
#include <unistd.h> 

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


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
	// auto logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
	// spdlog::set_default_logger(logger);
	spdlog::info("Calling memory-related {}","dwedwd");

	// spdlog::info("Welcome to spdlog!");
// 	while(1==1){
// 		memory obj1;
// 		cpu obj2;
// 		spdlog::info("Calling memory-related metrics ");
// 		obj1.total();
// 		obj1.used();
// 		obj1.available();
// 		obj1.total_swap();
// 		obj1.available_swap();
// 		spdlog::info("Calling cpu-related metrics ");
// 		obj2.idle();
// 		obj2.busy();
// 		obj2.user();
// 		obj2.system();
// 		obj2.total();
// 		spdlog::debug("Going to sleep for 10 seconds");
// 		logger->flush();
// 		std::this_thread::sleep_for (std::chrono::seconds(2));
// 	}
}
