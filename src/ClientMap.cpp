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
    pair<string, SPClient> newClientPair(pNewClient->m_Username, pNewClient);
    m_Clients.insert(newClientPair);
    // Auto cleanup the client if it times out
	  thread cleanupThread(&ClientMap::AutoCleanUp, this, pNewClient->m_Username);
    cleanupThread.detach();
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

/** AutoCleanup
Pauses the current thread for 10 seconds, then attempts to
erase the client given by the key.

@param key : [in] Key to client in map
@return void
*/
void ClientMap::AutoCleanUp(const string& key)
{
  this_thread::sleep_for(chrono::seconds(10));
  EraseClient(key);
}

/** EraseClient
Attempts to erase a client in a thread-safemanner.

@param key : [in] Key to client in map to erase
@return void
*/
void ClientMap::EraseClient(const string& key)
{
  string clientDevice;
  {
    lock_guard<mutex> lock(m_MapMutex);
    auto pClient = m_Clients[key];
    if (pClient)
      clientDevice = pClient->m_DeviceId;
    m_Clients.erase(key);
  }
  if (!clientDevice.empty())
    cout << clientDevice << " erased" << endl;
}