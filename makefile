ifeq ($(OS),Windows_NT)
	SOCKETFILE = src/windows/ServerSocket.cpp
	DELETE=del /f
	WINFLAGS=-lws2_32
else
	SOCKETFILE = src/posix/ServerSocket.cpp
	DELETE=rm -f
	WINFLAGS=
endif

CC=g++
FLAGS=-std=gnu++0x -Wall

all: server

server: Main.o Server.o ServerSocket.o ClientMap.o
	$(CC) Main.o Server.o ServerSocket.o ClientMap.o $(WINFLAGS) -o server
	
Main.o: src/Main.cpp
	g++ -c $(FLAGS) src/Main.cpp -o Main.o
	
Server.o: src/Server.cpp
	g++ -c $(FLAGS) src/Server.cpp -o Server.o
	
ServerSocket.o: $(SOCKETFILE)
	g++ -c $(FLAGS) $(SOCKETFILE) -o ServerSocket.o
	
ClientMap.o: src/ClientMap.cpp
	g++ -c $(FLAGS) src/ClientMap.cpp -o ClientMap.o
	
debug: src/Main.cpp src/Server.cpp $(SOCKETFILE)
	$(CC) -g -std=gnu++0x -Wall src/Main.cpp src/Server.cpp $(SOCKETFILE) src/ClientMap.cpp -o serverDbg

clean:
	$(DELETE) *.o

clean-all:
	$(DELETE) server serverDbg *.o *.exe
