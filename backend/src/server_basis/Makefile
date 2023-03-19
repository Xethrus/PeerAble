CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

all: echo_server server_client

echo_server: echo_server.cpp
	$(CXX) $(CXXFLAGS) -o echo_server echo_server.cpp

server_client: server_client.cpp
	$(CXX) $(CXXFLAGS) -o server_client server_client.cpp

run_server:
	./echo_server

run_client:
	./server_client

clean:
	rm -f echo_server server_client

