/******************************************************************
@file:        Server.cpp
@author:      David Hite
@created:     11/14/2017
*******************************************************************/
#include "Server.h"
#include <iostream>

using namespace UdpPuncher;
using std::string;
using std::cout;
using std::endl;

Server::Server()
: m_pClientMap(UPClientMap(new ClientMap()))
{
}

void Server::Run()
{
  cout << "Starting server on port " << m_PortNum << endl;
  m_pServerSocket = UPServerSocket(new ServerSocket(m_PortNum));
  cout << m_pServerSocket->GetErrorString() << endl;
}
