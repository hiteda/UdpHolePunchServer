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

bool Server::Run()
{
  cout << "Starting server on port " << m_PortNum << "..." << endl;
  
  m_pServerSocket = UPServerSocket(new ServerSocket(m_PortNum));
  string errString = m_pServerSocket->GetErrorString();
  if (!errString.empty())
  {
    cout << errString << endl;
    return false;
  }
  
  cout << "Listening on port " << m_PortNum << "..." << endl;
  
  bool receiveSuccess = true;
  while (1)
  {
    string receivedString("");
    receiveSuccess = m_pServerSocket->Receive(receivedString);
    if (receiveSuccess)
      cout << receivedString << endl;;
  }
  
  return true;
}
