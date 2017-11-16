/******************************************************************
@file:        ServerSocket.h
@author:      David Hite
@created:     11/15/2017
@description: Socket wrapper for handling server connections
*******************************************************************/
#pragma once
#include <netinet/in.h>
#include <string>

namespace UdpPuncher
{
enum class EErrType
{
  None,
  SocketOpen,
  Bind,
  SockOpt,
  RecvFrom
};

class ServerSocket
{
public:
  ServerSocket(const int portNum);
  ~ServerSocket();
  
  std::string GetErrorString() const;
  
private:
  struct sockaddr_in  m_AddrInMe;
  struct sockaddr_in  m_AddrInOther;
  int                 m_SocketFileDesc;  
  EErrType            m_ErrorCode;
  
  EErrType InitSocket(const int portNum);
};
}