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
  
  bool Receive(std::string& receivedString);
  
private:
  const static int    s_BUFFER_LENGTH = 512;

  struct sockaddr_in  m_AddrInMe;
  struct sockaddr_in  m_AddrInOther;
  socklen_t           m_OtherLength;
  int                 m_SocketFileDesc;  
  EErrType            m_ErrorCode;
  char                m_Buffer[s_BUFFER_LENGTH];
  
  EErrType InitSocket(const int portNum);
};
}