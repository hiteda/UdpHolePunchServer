ifeq($(OS),Windows_NT)
	SOCKETFILE = src/windows/ServerSocket.cpp
else
	SOCKETFILE = src/posix/ServerSocket.cpp
endif

all: src/Main.cpp src/Server.cpp $(SOCKETFILE)
	g++ -std=gnu++0x -Wall src/Main.cpp src/Server.cpp $(SOCKETFILE) src/ClientMap.cpp -o server

debug: src/Main.cpp src/Server.cpp $(SOCKETFILE)
	g++ -g -std=gnu++0x -Wall src/Main.cpp src/Server.cpp $(SOCKETFILE) src/ClientMap.cpp -o serverDbg

clean:
	rm -f server serverDbg
