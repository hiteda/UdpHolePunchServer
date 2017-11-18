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

/** SetPortNumber
Validates the given port number and sets the
server's port number.

@param portNumber : [in] port number to set
@return bool  true if success, else false
*/
bool Server::SetPortNumber(const int portNumber)
{
  if (portNumber < 1024 || portNumber > 65535)
    return false;
  m_PortNum = portNumber;
  return true;
}

/** Run
Starts and runs the server

@return bool  true if success, else false
*/
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

/** CloseSocket
If the socket is open, close it
*/
void Server::CloseSocket()
{
  if (m_pServerSocket)
    m_pServerSocket->CloseSocket();
}
