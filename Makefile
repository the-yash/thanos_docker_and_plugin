all: 
	g++ -ggdb -Wall PageRequest.cc adapter.cc client_class.cc -o combine  -lpistache  -lpthread -lyaml-cpp

clean:  
	$(RM)  demo

