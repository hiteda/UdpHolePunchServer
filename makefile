all: src/Main.cpp src/Server.cpp src/ServerSocket.cpp
	g++ -std=gnu++0x -Wall src/Main.cpp src/Server.cpp src/ServerSocket.cpp -o server

debug: src/Main.cpp src/Server.cpp
	g++ -g -std=gnu++0x -Wall -pthread src/Main.cpp src/Server.cpp src/Client.cpp -o serverDbg

clean:
	rm -f server serverDbg testSocket
