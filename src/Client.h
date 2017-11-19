/******************************************************************
@file:        Client.h
@author:      David Hite
@created:     11/14/2017
@description: Struct for holding client data
*******************************************************************/
#pragma once
#include "IpEndpoint.h"
#include <string>
#include <ctime>

namespace UdpPuncher
{
  struct Client
  {
    Client(const std::string& username,
            const std::string& devicedId,
            const std::string& data,
            const IpEndpoint& endPoint)
    : m_Username(username)
    , m_DeviceId(devicedId)
    , m_Data(data)
    , m_EndPoint(endPoint)
    , m_CreatedTime(time(nullptr))
    {}
    
    std::string m_Username;
    std::string m_DeviceId;
    std::string m_Data;
    IpEndpoint  m_EndPoint;
    time_t      m_CreatedTime;
  };
}
