#include<iostream>
#include<bits/stdc++.h>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>  
#include <unistd.h> 

/*spdlog library for logging feature*/
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/* yaml-cpp library for using config files*/
#include "yaml-cpp/yaml.h"
#include "adapter.h"

//Memory class for calling memory-related metrics from client side.
class memory{
	public:
	
	adapter_mem obj;

	void set(std::string url){
		obj.page = url;
	}

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

//CPU class for calling CPU-related metrics from client side.


class cpu{

	public:

	adapter_cpu obj;

	void set(std::string url){
		obj.page = url;
	}	

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
	//Objects of metric-related classes
	memory obj1;
	cpu obj2;

	//Loading the config file
	YAML::Node config = YAML::LoadFile("config.yaml");	

	//Reading the relative location of log files				
    std::string log_loc = config["LOGGER_LOCATION"].as<std::string>(); 

    //Reading the base query URL
	std::string query_url = config["BASE_QUERY_URL"].as<std::string>(); 

	//Reading the t_perioduency of requests (in seconds)
	int t_period = config["TIME_PERIOD_IN_SECONDS"].as<int>();


    //Setting the log file
	auto logger = spdlog::daily_logger_mt("daily_logger", log_loc, 2, 30); 
	spdlog::set_default_logger(logger);

	/*Change the logging level to debug to see more info*/
	// spdlog::set_level(spdlog::level::debug);

	/* Passing the base query url to the objects */
	obj1.set(query_url);
	obj2.set(query_url);

	/* Infinite loop which sends the request every t_period seconds */
	while(1==1){
		
		spdlog::info("Calling memory-related metrics ");
		obj1.total();
		obj1.used();
		obj1.available();
		obj1.total_swap();
		obj1.available_swap();
		spdlog::info("Calling cpu-related metrics ");
		obj2.idle();
		obj2.busy();
		obj2.user();
		obj2.system();
		obj2.total();
		spdlog::debug("Going to sleep for {0:d} seconds",t_period);
		spdlog::set_level(spdlog::level::info);
		/* Flushing the logging data to the file */
		logger->flush(); 
		/* Will sleep for t_period seconds before calling the metrics again */
		std::this_thread::sleep_for (std::chrono::seconds(t_period));
	}
}
