/******************************************************************
@file:        Server.cpp
@author:      David Hite
@created:     11/14/2017
*******************************************************************/
#include "Server.h"
#include "Client.h"
#include "IpEndpoint.h"
#include <iostream>
#include <cstring>

using namespace UdpPuncher;

static const char* s_DELIMITER = ":&:";

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
  std::cout << "Starting server on port " << m_PortNum << "..." << std::endl;
  
  m_pServerSocket = UPServerSocket(new ServerSocket(m_PortNum));
  std::string errString = m_pServerSocket->GetErrorString();
  if (!errString.empty())
  {
    std::cout << errString << std::endl;
    return false;
  }
  
  std::cout << "Listening on port " << m_PortNum << "..." << std::endl;
  
  while (1)
  {
    std::string receivedString("");
    if (m_pServerSocket->Receive(receivedString))
    {
      // Extract client data from the received message
      SPClient pClient = ParseMessage(receivedString);
      // If a valid client is returned, check if another client
      // is trying to connect to it
      if (pClient)
      {
        std::cout << "Received data from " << pClient->m_DeviceId << std::endl;
        SPClient pClientMatch = m_pClientMap->GetMatch(pClient);
        // If the clients are trying to connect to each other,
        // send them each other's data
        if (pClientMatch)
        {
          std::cout << "Match!" << std::endl;
          SendClientMessages(pClient, pClientMatch);
        }

        m_pClientMap->PrintClients(); // Print list of clients (for debugging)
      }
      else
        std::cout << "No client!" << std::endl;
    }
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

/** ParseMessage
Parses the given string and moves its data
to a new client pointer. If data is not valid,
returns a null pointer.

@param msg  : [in] string to parse
@return Shared pointer to a new Client object
*/
SPClient Server::ParseMessage(const std::string& msg) const
{
  SPClient pClient = nullptr;
  size_t delimPos = 0;
  std::string clientId = Tokenize(msg, s_DELIMITER, delimPos);
  if (!clientId.empty())
  {
    std::string clientDeviceId = Tokenize(msg, s_DELIMITER, delimPos);
    if (!clientDeviceId.empty())
    {
      std::string connectDeviceId = Tokenize(msg, s_DELIMITER, delimPos);
      if (!connectDeviceId.empty())
      {
        std::string otherData = Tokenize(msg, s_DELIMITER, delimPos);
        if (!otherData.empty()) // make sure there is some other data
        {
          IpEndpoint endPoint = m_pServerSocket->GetOtherEndpoint();
          pClient = SPClient(new Client(clientId, clientDeviceId, connectDeviceId, msg, endPoint));
        }
      }
    }
  }
  
  return pClient;
}

/** Tokenize
Tokenizes the given string using the position
and delimiter.

@param msg    : [in] string to tokenize
@param delim  : [in] delimiter
@param pos    : [in/out] position to begin from
@return The first substring before the given delimeter and after pos
*/
std::string Server::Tokenize(const std::string& msg, const char* delim, size_t& pos) const
{
  size_t newPos = msg.find(delim, pos);
  std::string token("");
  if (newPos != std::string::npos)
    token = msg.substr(pos, newPos - pos);
  else
    token = msg.substr(pos);
  pos = newPos + strlen(delim);
  return token;
}

/** SendClientMessage
Sends the data from pClient1 to pClient2, and vice versa

@param pClient1: [in] pointer to a Client object
@param pClient2: [in] pointer to a Client object
*/
void Server::SendClientMessages(const SPClient pClient1, const SPClient pClient2)
{
  m_pServerSocket->SendClientMessage(pClient1->m_EndPoint, pClient2->m_Data);
  m_pServerSocket->SendClientMessage(pClient2->m_EndPoint, pClient1->m_Data);
}