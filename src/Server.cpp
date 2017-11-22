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
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;

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
  cout << "Starting server on port " << m_PortNum << "..." << endl;
  
  m_pServerSocket = UPServerSocket(new ServerSocket(m_PortNum));
  string errString = m_pServerSocket->GetErrorString();
  if (!errString.empty())
  {
    cout << errString << endl;
    return false;
  }
  
  cout << "Listening on port " << m_PortNum << "..." << endl;
  
  while (1)
  {
    string receivedString("");
    if (m_pServerSocket->Receive(receivedString))
    {
      SPClient pClient = ParseMessage(receivedString);
      if (pClient)
      {
        SPClient pClientMatch = m_pClientMap->GetMatch(pClient);
        if (pClientMatch)
        {
          // TODO: send their data to each other
          cout << "Match!" << endl;
        }
        m_pClientMap->PrintClients();
      }
      else
        cout << "No client!" << endl;
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
shared_ptr<Client> Server::ParseMessage(const string& msg) const
{
  shared_ptr<Client> pClient = nullptr;
  size_t delimPos = 0;
  string clientId = Tokenize(msg, s_DELIMITER, delimPos);
  if (!clientId.empty())
  {
    string clientDeviceId = Tokenize(msg, s_DELIMITER, delimPos);
    if (!clientDeviceId.empty())
    {
      string otherData = Tokenize(msg, s_DELIMITER, delimPos);
      if (!otherData.empty())
      {
        IpEndpoint endPoint = m_pServerSocket->GetOtherEndpoint();
        pClient = shared_ptr<Client>(new Client(clientId, clientDeviceId, otherData, endPoint));
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
string Server::Tokenize(const std::string& msg, const char* delim, size_t& pos) const
{
  size_t newPos = msg.find(delim, pos);
  string token("");
  if (newPos != string::npos)
    token = msg.substr(pos, newPos - pos);
  else
    token = msg.substr(pos);
  pos = newPos + strlen(delim);
  return token;
}