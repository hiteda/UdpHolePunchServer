/******************************************************************
@file:        Server.h
@author:      David Hite
@created:     11/14/2017
@description: Hole punching server, helps connect clients to each other
*******************************************************************/
#pragma once
#include <memory>
#include "ClientMap.h"
#include "ServerSocket.h"

namespace UdpPuncher
{

typedef std::unique_ptr<ClientMap>    UPClientMap;
typedef std::unique_ptr<ServerSocket> UPServerSocket;

class Server
{
public:
  Server();

  bool SetPortNumber(const int portNumber);
  bool Run();
  void CloseSocket();
  
private:
  std::shared_ptr<Client> ParseMessage(const std::string& msg) const;
  std::string             Tokenize(const std::string& msg, const char* delim, size_t& pos) const;
  void                    SendClientMessages(const SPClient pClient1, const SPClient pClient2);

  int             m_PortNum = 0;
  static Server*  m_pInstance;
  UPClientMap     m_pClientMap;
  UPServerSocket  m_pServerSocket;
};
}
