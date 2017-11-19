/******************************************************************
@file:        IpEndpoint.h
@author:      David Hite
@created:     11/18/2017
@description: Struct for holding IP endpoint data
*******************************************************************/
#pragma once
#include <string>

namespace UdpPuncher
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
}