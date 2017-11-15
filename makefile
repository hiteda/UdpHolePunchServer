all: src/Main.cpp
	g++ -std=gnu++0x -Wall -pthread src/Main.cpp src/Server.cpp -o server

alt: srcAlt/Main.cpp
	g++ -std=gnu++0x -Wall -pthread srcAlt/Main.cpp srcAlt/Server.cpp -o serverAlt

debug: src/Main.cpp src/Server.cpp
	g++ -g -std=gnu++0x -Wall -pthread src/Main.cpp src/Server.cpp src/Client.cpp -o serverDbg

clean:
	rm -f server serverDbg testSocket
