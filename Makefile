all: 
	g++ -ggdb -Wall PageRequest.cc adapter.cc client_class.cc -o plugin  -lpistache  -lpthread -lyaml-cpp

clean:  
	$(RM) plugin

