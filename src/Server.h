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
  static Server& GetInstance()
  {
    static Server instance;
    return instance;
  }

  bool SetPortNumber(const int portNumber);
  bool Run();
  void CloseSocket();
  
private:
  Server();
  Server(Server const&);
  void operator=(Server const&);
  
  std::shared_ptr<Client> ParseMessage(const std::string& msg) const;
  std::string             Tokenize(const std::string& msg, const char* delim, size_t& pos) const;

  int             m_PortNum;
  static Server*  m_pInstance;
  UPClientMap     m_pClientMap;
  UPServerSocket  m_pServerSocket;
};
}
