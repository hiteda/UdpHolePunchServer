# UdpHolePunchServer
This server helps clients connect to each other. The first two fields in the datagram (separated by ":&:") are a connection ID and a client ID.
When two datagrams are received that have the same connection ID and different client IDs, the server sends the endpoint data from each client
to the other client, along with the data from the original datagram. It is then up to the clients to use that data and any other data from 
the datagram to connect to each other.

## Compiling on Linux
Run "make" to build the server

## Compiling on Windows
If you have Visual Studio 2013 or 2015 installed, run "vs_compile.bat".

## Test Directory
The "test" directory contains some basic test scripts. SocketTest.py contains a module for sending data to the server.
This module is used by basicTest.py, which contains unit tests to test whether the server responds correctly on localhost.
