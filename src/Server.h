/******************************************************************
@file:        Server.h
@author:      David Hite
@created:     11/14/2017
@description: Hole punching server, helps connect clients to each other
*******************************************************************/
#pragma once
#include <memory>
#include "ClientMap.h"

namespace UdpPuncher
{
class ClientMap;

class Server
{
public:
  Server();
  
  void Run();
  
private:
  const static int m_PortNum = 55176;
  
  std::unique_ptr<ClientMap> m_pClientMap;
};
}
