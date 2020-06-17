// #include <atomic>

// #include <pistache/client.h>
// #include <pistache/http.h>
// #include <pistache/net.h>
// #include "rapidjson/document.h"

// #include <iostream> 
// #include <string>
// #include <bits/stdc++.h>
// #include <typeinfo>

// using namespace Pistache;
// using namespace Pistache::Http;
#ifndef PAGEREQUEST_H
#define PAGEREQUEST_H

class PageRequest
{

  public:

  std::string page ;

  // PageRequest(){
    
  //   page =  "http://localhost:9090/api/v1/labels";
  //   std::cout<<"Unparamterized constructor called"<<std::endl
  //            << page <<std::endl;       
  // }  
  PageRequest();
  PageRequest(std:: string query);
  void run();

};

#endif