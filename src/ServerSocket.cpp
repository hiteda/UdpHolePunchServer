/******************************************************************
@file:        ServerSocket.cpp
@author:      David Hite
@created:     11/15/2017
*******************************************************************/
#include "ServerSocket.h"
#include "IpEndpoint.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>

using namespace UdpPuncher;
using std::string;

ServerSocket::ServerSocket(const int portNum)
: m_ErrorCode(EErrType::None)
{
  m_ErrorCode   = InitSocket(portNum);
  m_OtherLength = sizeof(m_AddrInOther);
}

ServerSocket::~ServerSocket()
{
  CloseSocket();
}

/** GetErrorString
Returns a string corresponding to the current value
of m_ErrorCode
@return string of error message
*/
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
    case EErrType::None: // fall through
    default:
      break;
  }
  return errString;
}

void ServerSocket::CloseSocket()
{
  if (m_SocketFileDesc > -1)
    close(m_SocketFileDesc);
}

bool ServerSocket::Receive(string& receivedString)
{
  bzero(m_Buffer, s_BUFFER_LENGTH);
  
  if (recvfrom(m_SocketFileDesc, m_Buffer, s_BUFFER_LENGTH, 0, (struct sockaddr*)(&m_AddrInOther), &m_OtherLength) == -1)
  {
    m_ErrorCode = EErrType::RecvFrom;
    return false;
  }
  receivedString.assign(m_Buffer, strlen(m_Buffer));
  return true;
}

IpEndpoint ServerSocket::GetOtherEndpoint() const
{
  string ipAddress(inet_ntoa(m_AddrInOther.sin_addr));
  IpEndpoint otherEndpoint(ipAddress, m_AddrInOther.sin_port);
  return otherEndpoint;
}

/** InitSocket
Initializes the server socket on the number set
by portNum.

@param  portNum : [in] port number to use
@return EErrType type of error that occurred
*/
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