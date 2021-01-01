# UdpHolePunchServer
This server helps clients connect to each other. Clients that wish to connect to each other send specially formatted datagrams to the server, which then passes each client's information to the other client. The first two fields in the datagram (separated by ":&:") are a connection ID and a client ID.
When two datagrams are received that have the same connection ID and different client IDs, the server sends the endpoint data from each client
to the other client, along with the data from the original datagram. It is then up to the clients to use that data and any other data from 
the datagram to connect to each other.

## Compiling on Linux
Run "make" to build the server

## Compiling on Windows
From inside the _build directory, run run_cmake.bat. You may need to modify run_cmake.bat to use your version of Visual Studio.
Once the script has run, you can open _build/UdpHolePunchServer.sln and compile.

## Test Directory
The "test" directory contains some basic test scripts. SocketTest.py contains a module for sending data to the server.
This module is used by basicTest.py, which contains unit tests to test whether the server responds correctly on localhost.
