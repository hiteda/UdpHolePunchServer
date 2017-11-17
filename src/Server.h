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
//class ClientMap;
//class ServerSocket;

typedef std::unique_ptr<ClientMap>    UPClientMap;
typedef std::unique_ptr<ServerSocket> UPServerSocket;

class Server
{
public:
  Server();
  
  bool Run();
  
private:
  const static int m_PortNum = 55176;
  
  UPClientMap     m_pClientMap;
  UPServerSocket  m_pServerSocket;
};
}
