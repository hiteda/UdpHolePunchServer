/******************************************************************
@file:        ServerSocket.h
@author:      David Hite
@created:     05/09/2018
@description: Socket wrapper for handling server connections in Windows
*******************************************************************/
#pragma once
#include <winsock2.h>
#include <string>

namespace UdpPuncher
{
struct IpEndpoint;  

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
  void        CloseSocket();

  bool        Receive(std::string& receivedString);
  IpEndpoint  GetOtherEndpoint() const;
  void        SendClientMessage(const IpEndpoint& clientEndpoint, const std::string& msg);
  
private:
  const static int    s_BUFFER_LENGTH = 512;

  struct sockaddr_in  m_AddrInMe;
  struct sockaddr_in  m_AddrInOther;
  int                 m_OtherLength;
  SOCKET              m_Socket;  
  EErrType            m_ErrorCode;
  char                m_Buffer[s_BUFFER_LENGTH];
  
  EErrType InitSocket(const int portNum);
};
}