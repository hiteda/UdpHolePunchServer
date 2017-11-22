/******************************************************************
@file:        ClientMap.h
@author:      David Hite
@created:     11/14/2017
@description: Contains a map of client data
*******************************************************************/
#pragma once
#include <map>
#include <string>
#include <memory>

namespace UdpPuncher
{
struct Client;
typedef std::shared_ptr<Client> SPClient;

class ClientMap
{
public:
  ClientMap(){}
  ~ClientMap(){}
  
  SPClient  GetMatch(SPClient pNewClient);
  void      PrintClients() const;
  
private:
  std::map<std::string, SPClient> m_Clients;
};
}
