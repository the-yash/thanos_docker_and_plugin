all: http_client.cc
	g++ -ggdb -Wall PageRequest.cc adapter.cc client_class.cc -o combine  -lpistache  -lpthread

clean:  
	$(RM)  demo

