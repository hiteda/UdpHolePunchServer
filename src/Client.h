/******************************************************************
@file:        Client.h
@author:      David Hite
@created:     11/14/2017
@description: Struct for holding client data
*******************************************************************/
#pragma once
#include <string>
#include <ctime>

namespace GoopsPuncher
{
  struct IpEndpoint
  {
    std::string m_Address;
    int         m_Port;
    
    IpEndpoint(const std::string& address, const int port)
    : m_Address(address)
    , m_Port(port)
    {
    }
  };
  
  struct Client
  {
    //Client(const std::string& data,
    //        const std::string& extAddress,
    //        const std::string& extPort);
    
    std::string m_Username;
    std::string m_DeviceId;
    std::string m_Data;
    IpEndpoint  m_EndPoint;
    time_t      m_CreatedTime;
  };
}