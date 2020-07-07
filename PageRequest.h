/* To limit definition of header files to one instance */
#ifndef PAGEREQUEST_H
#define PAGEREQUEST_H

class PageRequest
{

  public:

  std::string page ;
  std::string out_file;

  /* Unparameterized constructor */
  PageRequest();

  /* Parameterized constructor (default)*/
  PageRequest(std:: string query);

  /* The function that sends requests and outputs the response*/
  void run();

};

#endif