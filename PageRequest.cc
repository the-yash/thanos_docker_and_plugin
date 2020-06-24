#include <atomic>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <pistache/client.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include "rapidjson/document.h"

#include <iostream> 
#include <string>
#include <bits/stdc++.h>
#include <typeinfo>
#include "PageRequest.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


using namespace Pistache;
using namespace Pistache::Http;
using namespace rapidjson;


PageRequest::PageRequest(){  // simple constructor in case no parameters are passed
    
  page =  "http://localhost:10904/api/v1/labels";
  // std::cout<<"Unparamterized constructor called"<<std::endl
           // << page <<std::endl;       
}  


PageRequest::PageRequest(std:: string query){ // when paramteres are passed
  page = query;
}


void PageRequest :: run(){ // the run function to send the request and receive the json
  
  // auto file_logger = spdlog::get("daily_logger");
  // spdlog::set_default_logger(file_logger); 

  int count = 1;
  Http::Client client;
  // std::cout<<"Check "<<page<<std::endl;
  auto opts = Http::Client::options().threads(1).maxConnectionsPerHost(8);
  client.init(opts);

  std::vector<Async::Promise<Http::Response>> responses;

  std::atomic<size_t> completedPageRequests(0);
  std::atomic<size_t> failedPageRequests(0);
  auto start = std::chrono::system_clock::now();

  for (int i = 0; i < count; ++i) {
    auto resp = client.get(page).cookie(Http::Cookie("FOO", "bar")).send();
    resp.then(
        [&](Http::Response response) {
          ++completedPageRequests;
          std::cout << "Response code = " << response.code() << std::endl ;
          // << decltype(response.code()) << std::endl;
          spdlog::info("Request received {0:d}",response.code());
          auto body = response.body();
          // auto body_str = response.body().c_str(); //This does not work 

          if (!body.empty()){ //The rapidjson implementation ->
            std::cout << "Response body = " << body ;
            // std::cout << "Response body string = " << body_str << std::endl;

            const char* json = new char[response.body().length()+1];
            json = ((response.body()).c_str());
            //The confusing statement which makes this work->
            std::string test_variable = response.body();
            
            Document d;
            d.Parse(json); //the json variable is being used
            // d.Parse(body_str); //the auto variable which is used in line 56


            // 2. Modify it by DOM.
            // Value& s = d["status"];
            // s.SetString("error");

            // 3. Stringify the DOM
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);

            // Output check
            // std::cout <<" CHECK "<< buffer.GetString() <<" CHECK "<< std::endl;
            // std::cout <<" SCHECKSCHECK "<<response.body()<< std::endl;
            // std::cout <<" test_variable ="<<test_variable<< std::endl;
            // std::cout <<" json ="<<json<< std::endl;
            // std::cout <<" CHECK "<< buffer.GetString() <<" CHECK "<< std::endl;
          }//rapidjson part ends


        },
        [&](std::exception_ptr exc) {
          ++failedPageRequests;
          PrintException excPrinter;
          excPrinter(exc);
          // std::cout<<"SSS"<<std::endl;
          spdlog::warn("Failed request");
        });
    responses.push_back(std::move(resp));
  }

  auto sync = Async::whenAll(responses.begin(), responses.end());
  Async::Barrier<std::vector<Http::Response>> barrier(sync);
  barrier.wait_for(std::chrono::seconds(5));

  auto end = std::chrono::system_clock::now();
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
  spdlog::debug("Total time of execution {0:d} milliseconds",std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
  client.shutdown();
}
