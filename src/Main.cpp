/******************************************************************
@file:        Main.cpp
@author:      David Hite
@created:     11/14/2017
@description: Launches the hole punch server
*******************************************************************/
#include "Server.h"
#include <signal.h>
#include <iostream>

/** InterruptHandler
If an interrupt signal is received and a socket is
open, closes the socket.

@param s  : [in] signal type
*/
void InterruptHandler(int s)
{
  std::cout << "Interrupt received! Shutting down..." << std::endl;
  exit(1);
}

int main(int argc, char* argv[])
{
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = &InterruptHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
  
  UdpPuncher::Server theServer;
  
  theServer.Run();
  
  return 0;
}
