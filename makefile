CC=g++
FLAGS=-std=gnu++0x -Wall
LINKFLAGS=-pthread

all: server

server: Main.o Server.o ServerSocket.o ClientMap.o
	$(CC) Main.o Server.o ServerSocket.o ClientMap.o $(LINKFLAGS) -o server
	
Main.o: src/Main.cpp
	g++ -c $(FLAGS) src/Main.cpp -o Main.o
	
Server.o: src/Server.cpp
	g++ -c $(FLAGS) src/Server.cpp -o Server.o
	
ServerSocket.o: src/posix/ServerSocket.cpp
	g++ -c $(FLAGS) src/posix/ServerSocket.cpp -o ServerSocket.o
	
ClientMap.o: src/ClientMap.cpp
	g++ -c $(FLAGS) src/ClientMap.cpp -o ClientMap.o
	
debug: src/Main.cpp src/Server.cpp $(SOCKETFILE)
	$(CC) -g -std=gnu++0x -Wall src/Main.cpp src/Server.cpp src/posix/ServerSocket.cpp src/ClientMap.cpp -o serverDbg

clean:
	rm -f *.o

clean-all:
	rm -f server serverDbg *.o *.exe
