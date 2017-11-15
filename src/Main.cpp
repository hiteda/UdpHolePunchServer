/******************************************************************
@file:        Main.cpp
@author:      David Hite
@created:     11/14/2017
@description: Launches the hole punch server
*******************************************************************/
#include "Server.h"

int main(int argc, char* argv[])
{
  GoopsPuncher::Server theServer;
  
  theServer.Run();
  
  return 0;
}