#include <iostream> 
#include <string>
#include <bits/stdc++.h>
#include "PageRequest.h"
#include "adapter.h"

//This is the adapter file with function defintions. The queries that have to be sent to the API are hardcoded here. For each function, a different query is required to be hardcoded.

// adapter_mem class funtion definitions

adapter_mem::adapter_mem(){
	page = "http://localhost:10904/api/v1/query?query=" ; /*This is the base page of the API. It is initialized in the constructor. 
							       It is common to all queries. The queries have to be concatenated with this
							       string stored in page variable. */
}

void adapter_mem::total(){
	obj.page = page +"node_memory_MemTotal_bytes";
	obj.run();
}
void adapter_mem::used(){
	obj.page = page +"node_memory_MemTotal_bytes-node_memory_MemAvailable_bytes";
	obj.run();
}
void adapter_mem::available(){
	obj.page = page +"node_memory_MemAvailable_bytes";
	obj.run();
}
void adapter_mem::total_swap(){
	obj.page = page +"node_memory_SwapTotal_bytes";
	obj.run();		

}
void adapter_mem::used_swap(){
	obj.page = page +"node_memory_SwapTotal_bytes-node_memory_SwapFree_bytes";
	obj.run();
}
void adapter_mem::available_swap(){
	obj.page = page +"node_memory_SwapFree_bytes";
	obj.run();
}

//adapter_cpu class function definitions

adapter_cpu::adapter_cpu(){
	page = "http://localhost:10904/api/v1/query?query=" ; /*This is the base page of the API. It is initialized in the constructor. 
							       It is common to all queries. The queries have to be concatenated with this
							       string stored in page variable. */
}	

void adapter_cpu::busy(){
	obj.page = page +"(1-(sum(irate(node_cpu_seconds_total{mode=\"idle\"}[5m]))/sum(irate(node_cpu_seconds_total{}[5m]))))*100";
	obj.run();
}

void adapter_cpu::user(){
	obj.page = page +"((sum(irate(node_cpu_seconds_total{mode=\"user\"}[5m]))/sum(irate(node_cpu_seconds_total{}[5m]))))*100";
	obj.run();
}

void adapter_cpu::total(){
	obj.page = page +"(sum(irate(node_cpu_seconds_total{}[5m])))";
	obj.run();
}

void adapter_cpu::idle(){
	obj.page = page +"((sum(irate(node_cpu_seconds_total{mode=\"idle\"}[5m]))/sum(irate(node_cpu_seconds_total{}[5m]))))*100";
	// std::cout<<obj.page<<std::endl;
	obj.run();
}
void adapter_cpu::system(){
	obj.page = page +"((sum(irate(node_cpu_seconds_total{mode=\"system\"}[5m]))/sum(irate(node_cpu_seconds_total{}[5m]))))*100";
	obj.run();
}


