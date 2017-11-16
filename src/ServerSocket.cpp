/******************************************************************
@file:        ServerSocket.cpp
@author:      David Hite
@created:     11/15/2017
*******************************************************************/
#include "ServerSocket.h"
#include <unistd.h>
#include <string.h>

using namespace UdpPuncher;
using std::string;

ServerSocket::ServerSocket(const int portNum)
: m_ErrorCode(EErrType::None)
{
  m_ErrorCode = InitSocket(portNum);
}

ServerSocket::~ServerSocket()
{
  if (m_SocketFileDesc > -1)
    close(m_SocketFileDesc);
}

string ServerSocket::GetErrorString() const
{
  string errString("");
  switch(m_ErrorCode)
  {
    case EErrType::SocketOpen:
      errString = "Failed to open socket";
      break;
    case EErrType::Bind:
      errString = "Failed to bind to socket";
      break;
    case EErrType::SockOpt:
      errString = "Failed to set socket options";
      break;
    case EErrType::RecvFrom:
      errString = "Failed to receive message";
      break;
    case EErrType::None:
      errString = "Socket open success!";
      break;
    default:
      break;
  }
  return errString;
}

EErrType ServerSocket::InitSocket(const int portNum)
{
  m_SocketFileDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (m_SocketFileDesc < 0)
    return EErrType::SocketOpen;
  
  memset((char*) &m_AddrInMe, 0, sizeof(m_AddrInMe));
  m_AddrInMe.sin_family       = AF_INET;
  m_AddrInMe.sin_port         = htons(portNum);
  m_AddrInMe.sin_addr.s_addr  = htonl(INADDR_ANY);
  
  // attempt to bind to socket
  if ((bind(m_SocketFileDesc, (struct sockaddr*)(&m_AddrInMe), sizeof(m_AddrInMe))) == -1)
    return EErrType::Bind;
  
  return EErrType::None;
}