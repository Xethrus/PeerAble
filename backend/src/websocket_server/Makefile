CC=clang++
CFLAGS=-Wall

all: server client

server: server.o mongoose.o
	$(CC) -Wall server.o mongoose.o -o server

client: client.o mongoose.o
	$(CC) -Wall client.o mongoose.o -o client

server.o: server.cpp
	$(CC) -c $(CFLAGS) server.cpp

client.o: client.cpp
	$(CC) -c $(CFLAGS) client.cpp

mongoose.o: mongoose.c
	$(CC) -c $(CFLAGS) mongoose.c

clean:
	rm -rf *o server client

