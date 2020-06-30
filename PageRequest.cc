#include <atomic>
#include <iostream> 
#include <string>
#include <bits/stdc++.h>
#include <typeinfo>

/* Rapidjson libraries */
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"

/* Pistache libraries*/
#include <pistache/client.h>
#include <pistache/http.h>
#include <pistache/net.h>

/* spdlog libraries */
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


#include "PageRequest.h"

using namespace Pistache;
using namespace Pistache::Http;
using namespace rapidjson;



/* Simple constructor in case no parameters are passed. 
Will set the query URL to fetch labels (metrics that are currently monitored) */
PageRequest::PageRequest(){  
    
  page =  "http://localhost:10904/api/v1/labels";
  // std::cout<<"Unparamterized constructor called"<<std::endl
           // << page <<std::endl;       
}  

/* Parameterized constructor with URL as the parameter */
PageRequest::PageRequest(std:: string query){ // when paramteres are passed
  page = query;
}

/* Function to send the request and receive the json response */
void PageRequest :: run(){ 
  
  /*To set the number of times to send a request. Here it is 1*/
  int count = 1;
  Http::Client client;

  /* Only one thread will be used */
  auto opts = Http::Client::options().threads(1).maxConnectionsPerHost(8);
  client.init(opts);
  std::vector<Async::Promise<Http::Response>> responses;
  std::atomic<size_t> completedPageRequests(0);
  std::atomic<size_t> failedPageRequests(0);
  
  /*To time the requests*/
  auto start = std::chrono::system_clock::now();

  for (int i = 0; i < count; ++i) {
    auto resp = client.get(page).cookie(Http::Cookie("FOO", "bar")).send();
    resp.then(
        [&](Http::Response response) {
          ++completedPageRequests;
          std::cout << "Response code = " << response.code() << std::endl ;
          spdlog::info("Request received {0:d}",response.code());
          auto body = response.body();
          // auto body_str = response.body().c_str(); //This does not work 

          /* The rapidjson implementation -> */
          if (!body.empty()){
            std::cout << "Response body = " << body ;
            // std::cout << "Response body string = " << body_str << std::endl;

            /* 1. Parse a JSON string into DOM.*/
            const char* json = new char[response.body().length()+1];
            json = ((response.body()).c_str());
            //The confusing statement which makes this work->
            std::string test_variable = response.body();
            
            Document d;
            d.Parse(json); //the json variable is being used
            
            // d.Parse(body_str); //the auto variable which is used in line 56


            /* 2. Modify it by DOM. */
            // Value& s = d["status"];
            // s.SetString("error");

            // 3. Stringify the DOM
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);

            /* Output the modified json */
            // std::cout << buffer.GetString() << std::endl;

            /* Debugging */
            // std::cout <<" SCHECKSCHECK "<<response.body()<< std::endl;
            // std::cout <<" test_variable ="<<test_variable<< std::endl;
            // std::cout <<" json ="<<json<< std::endl;
            // std::cout <<" CHECK "<< buffer.GetString() <<" CHECK "<< std::endl;
          }
        /*End of rapidjson part*/  


        },
        /* If a page request fails */
        [&](std::exception_ptr exc) {
          ++failedPageRequests;
          PrintException excPrinter;
          excPrinter(exc);
          spdlog::warn("Failed request");
        });
    responses.push_back(std::move(resp));
  }

  auto sync = Async::whenAll(responses.begin(), responses.end());
  Async::Barrier<std::vector<Http::Response>> barrier(sync);
  barrier.wait_for(std::chrono::seconds(5));

  auto end = std::chrono::system_clock::now();
  spdlog::debug("Total time of execution {0:d} milliseconds",std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
  
  /* Analytics of a page request*/
  // std::cout << "Summary of execution" << std::endl
  //           << "Total number of PageRequests sent     : " << count << std::endl
  //           << "Total number of responses received: "
  //           << completedPageRequests.load() << std::endl
  //           // << "Total number of PageRequests failed   : " << failedPageRequests.load()
  //           // << std::endl
  //           << "Total time of execution           : "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << "ms" << std::endl;
  
  client.shutdown();
}
