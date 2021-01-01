/******************************************************************
@file:        ClientMap.h
@author:      David Hite
@created:     11/21/2017
*******************************************************************/
#include "ClientMap.h"
#include "Client.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace UdpPuncher;

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
  std::lock_guard<std::mutex> lock(m_MapMutex);
  auto clientIter = m_Clients.find(pNewClient->m_Username);
  if (clientIter != m_Clients.end()) // Username has a match
  {
    if ((clientIter->second->m_DeviceId != pNewClient->m_DeviceId) &&
        (clientIter->second->m_ConnectDeviceId == pNewClient->m_DeviceId) &&
        (clientIter->second->m_DeviceId == pNewClient->m_ConnectDeviceId))
    {
      // Device is not the same. Return client and remove from list
      pOldClient = clientIter->second;
      EraseClient(pNewClient->m_Username);
    }
  }
  else // No match, add the new client
  {
    std::pair<std::string, SPClient> newClientPair(pNewClient->m_Username, pNewClient);
    m_Clients.insert(newClientPair);
    // Auto cleanup the client if it times out
    std::thread cleanupThread(&ClientMap::AutoCleanUp, this, pNewClient->m_Username);
    cleanupThread.detach();
  }
  
  return pOldClient;
}

/** PrintClients
Prints out all of the existing clients (for debugging)
*/
void ClientMap::PrintClients()
{
  int counter = 1;
  std::cout << std::endl;
  
  std::lock_guard<std::mutex> lock(m_MapMutex);
  for (auto client : m_Clients)
  {
    std::cout << counter++ << ". " << client.first << ": " << client.second->m_DeviceId << std::endl;
  }
}

/** AutoCleanup
Pauses the current thread for 10 seconds, then attempts to
erase the client given by the key.

@param key : [in] Key to client in map
@return void
*/
void ClientMap::AutoCleanUp(const std::string& key)
{
  std::this_thread::sleep_for(std::chrono::seconds(10));
  EraseClientSafe(key);
}

/** EraseClientSafe
Attempts to erase a client in a thread-safe manner.

@param key : [in] Key to client in map to erase
@return void
*/
void ClientMap::EraseClientSafe(const std::string& key)
{
  std::lock_guard<std::mutex> lock(m_MapMutex);
  EraseClient(key);
}

/** EraseClient
Attempts to erase a client.
NOTE: This method should only be used if the caller has
a lock on m_MapMutex!

@param key : [in] Key to client in map to erase
@return void
*/
void ClientMap::EraseClient(const std::string& key)
{
  std::string clientDevice;
  auto pClient = m_Clients[key];
  if (pClient)
    clientDevice = pClient->m_DeviceId;
  m_Clients.erase(key);
  if (!clientDevice.empty())
    std::cout << clientDevice << " erased" << std::endl;
}