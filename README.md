# UdpHolePunchServer
This server helps clients connect to each other. The first two fields in the datagram (separated by ":&:") are a connection ID and a client ID.
When two datagrams are received that have the same connection ID and different client IDs, the server sends the endpoint data from each client
to the other client, along with the data from the original datagram. It is then up to the clients to use that data and any other data from 
the datagram to connect to each other.

Made to run on Linux machines.

Run "make" to build the server

A simple test script is in the python directory. Run "python socketTest.py --host {SERVER_IP} {SERVER_PORT}" to send a datagram to the server. To simulate two clients, you will need to modify the second field in the message (very rudimentary test script).
