CC=clang++
CFLAGS=-Wall

all: server client

server: server.o mongoose.o
	$(CC) -Wall server.o mongoose.o -o server

client: client.o
	$(CC) -Wall client.o -o client

server.o: server.cpp
	$(CC) -c $(CFLAGS) server.cpp

mongoose.o: mongoose.c
	$(CC) -c $(CFLAGS) mongoose.c

client.o: client.cpp
	$(CC) -c $(CFLAGS) client.cpp


clean:
	rm -rf *o server

