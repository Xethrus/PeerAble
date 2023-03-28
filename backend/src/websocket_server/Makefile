CC=g++
CFLAGS=-c -Wall

all: server

server: server.o mongoose.o
	$(CC) server.o mongoose.o -o server

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

mongoose.o: mongoose.cpp
	$(CC) $(CFLAGS) mongoose.cpp


clean:
	rm -rf *o server

