/******************************************************************
@file:        Main.cpp
@author:      David Hite
@created:     11/14/2017
@description: Launches the hole punch server
*******************************************************************/
#include "Server.h"
#include <iostream>
#include <signal.h>

using namespace UdpPuncher;

int main(int argc, char* argv[])
{
  // Default port number for server to listen on
  int portNumber = 55176;
  // Allow the user to set the server port number from the command line
  if (argc == 2)
    portNumber = atoi(argv[1]);
  
  Server theServer;
  if (!theServer.SetPortNumber(portNumber))
  {
    std::cout << "Invalid port number. Please select a port between 1024 and 65535." << std::endl;
    return 1;
  }
  if (!theServer.Run())
    return 1;
  
  return 0;
}
