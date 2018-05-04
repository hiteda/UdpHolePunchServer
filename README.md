# UdpHolePunchServer
This server helps clients connect to each other. The first two fields in the datagram (separated by ":&:") are a connection ID and a client ID.
When two datagrams are received that have the same connection ID and different client IDs, the server sends the endpoint data from each client
to the other client, along with the data from the original datagram. It is then up to the clients to use that data and any other data from 
the datagram to connect to each other.

Made to run on Linux machines.

Run "make" to build the server

The "test" directory contains some basic test scripts. Run testBasic to simulate two clients connecting to the server with no edge cases or 
error cases. You may need to make testBasic executable by running "sudo chmod +x testBasic". As of May 3, 2018, testBasic can only be run
from the "test" directory.
