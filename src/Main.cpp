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
using namespace std;

/** InterruptHandler
If an interrupt signal is received and a socket is
open, closes the socket.

@param s  : [in] signal type
*/
void InterruptHandler(int s)
{
  cout << "Interrupt received! Closing the socket...\n";
  Server::GetInstance().CloseSocket();
  exit(1);
}

/** InitializeInterruptHandler
Connects InterruptHandler() to SIGINT
*/
void InitializeInterruptHandler()
{
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = &InterruptHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
}

int main(int argc, char* argv[])
{
  int portNumber = 55176;
  if (argc == 2)
    portNumber = atoi(argv[1]);
  
  InitializeInterruptHandler();
  
  if (!Server::GetInstance().SetPortNumber(portNumber))
  {
    cout << "Invalid port number. Please select a port between 1024 and 65535." << endl;
    return 1;
  }
  if (!Server::GetInstance().Run())
    return 1;
  
  return 0;
}
