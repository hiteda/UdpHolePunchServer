/******************************************************************
@file:        ClientMap.h
@author:      David Hite
@created:     11/21/2017
*******************************************************************/
#include "ClientMap.h"
#include "Client.h"
#include <iostream>
#include <ctime>

using namespace UdpPuncher;
using namespace std;

/** GetMatch
Checks for a match in the client map. If a matching
key exists and the device name is different, returns
that map value and removes the item from the map.

@param pNewClient : [in] Client being compared
@return Pointer to matched client, or nullptr
*/
SPClient ClientMap::GetMatch(SPClient pNewClient)
{
  SPClient pOldClient = nullptr;
  auto clientIter = m_Clients.find(pNewClient->m_Username);
  if (clientIter != m_Clients.end()) // Username has a match
  {
    // If the client was created more than 10 minutes ago, delete it
    time_t now = time(nullptr);
    if (difftime(now, clientIter->second->m_CreatedTime) > 600)
    {
      m_Clients.erase(clientIter->first);
      return nullptr;
    }
    // The incoming Client's ID must not match the existing Client's ID,
    // it must be trying to connect to the existing Client, and the existing
    // Client must be trying to connect to it
    if ((clientIter->second->m_DeviceId != pNewClient->m_DeviceId) &&
        (clientIter->second->m_ConnectDeviceId == pNewClient->m_DeviceId) &&
        (clientIter->second->m_DeviceId == pNewClient->m_ConnectDeviceId))
    {
      // Device is not the same. Return client and remove from list
      pOldClient = clientIter->second;
      m_Clients.erase(pNewClient->m_Username);
    }
  }
  else // No match, add the new client
  {
    pair<string, SPClient> newClientPair(pNewClient->m_Username, pNewClient);
    m_Clients.insert(newClientPair);
  }
  
  return pOldClient;
}

/** PrintClients
Prints out all of the existing clients (for debugging)
*/
void ClientMap::PrintClients() const
{
  int counter = 1;
  cout << endl;
  for (auto client : m_Clients)
  {
    cout << counter << ". " << client.first << ": " << client.second->m_DeviceId << endl;
    counter++;
  }
}