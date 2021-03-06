/******************************************************************
@file:        ServerSocket.cpp
@author:      David Hite
@created:     05/09/2018
*******************************************************************/
#include "ServerSocket.h"
#include "..\IpEndpoint.h"
#include <string.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <ws2tcpip.h>

using namespace UdpPuncher;

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
std::string ServerSocket::GetErrorString() const
{
  std::string errString("");
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

/** CloseSocket
If the socket is open, closes it
*/
void ServerSocket::CloseSocket()
{
  if (m_Socket != INVALID_SOCKET)
    closesocket(m_Socket);
}

/** Receive
Listens for a message on the socket, then assigns the
received data to receivedString

@param receivedString : [out] string to populate with received data
@return   true if successful, otherwise false
*/
bool ServerSocket::Receive(std::string& receivedString)
{
  memset(m_Buffer, '\0', s_BUFFER_LENGTH);
  
  if (recvfrom(m_Socket, m_Buffer, s_BUFFER_LENGTH, 0, (struct sockaddr*)(&m_AddrInOther), &m_OtherLength) == SOCKET_ERROR)
  {
    m_ErrorCode = EErrType::RecvFrom;
    return false;
  }
  receivedString.assign(m_Buffer, strlen(m_Buffer));
  return true;
}

/** GetOtherEndpoint
Translates endpoint data from m_AddrInOther (sockaddr_in)
to an IpEndpoint and returns the IpEndpoint object

@return  IpEndpoint object with endpoint data from m_AddrInOther
*/
IpEndpoint ServerSocket::GetOtherEndpoint() const
{
  char ipStr[INET6_ADDRSTRLEN];
  memset(ipStr, 0, INET6_ADDRSTRLEN);
  IN_ADDR ipSockAddr = m_AddrInOther.sin_addr;
  void* pAddr = &(ipSockAddr);
  auto result = inet_ntop(m_AddrInOther.sin_family, pAddr, (PSTR)(ipStr), strlen(ipStr));

  std::string ipAddress;
  if (result == NULL) // In release mode, inet_ntop returns NULL on localhost
    ipAddress = "127.0.0.1";
  else
    ipAddress.assign(ipStr, strlen(ipStr));

  // Initialize and return IpEndpoint object.
  // Note: compiling with C++11 or higher, move semantics will help with return efficiency
  IpEndpoint otherEndpoint(ipAddress, ntohs(m_AddrInOther.sin_port));
  return otherEndpoint;
}

/** SendClientMessage
Sends the data in msg to the client given by clientEndpoint

@param clientEndpoint : [in] endpoint data of client to send to
@param msg            : [in] data to send
*/
void ServerSocket::SendClientMessage(const IpEndpoint& clientEndpoint, const std::string& msg)
{
  struct sockaddr_in clientAddress;
  memset((char*) &clientAddress, 0, sizeof(clientAddress));
  
  clientAddress.sin_family  = AF_INET;
  clientAddress.sin_port    = htons(clientEndpoint.m_Port);
  std::cout << clientEndpoint.m_Address << ":" << clientEndpoint.m_Port << std::endl;
  inet_pton(AF_INET, (PCSTR)(clientEndpoint.m_Address.c_str()), &(clientAddress.sin_addr));
  if (sendto(m_Socket, msg.c_str(), msg.length()+1, 0, (struct sockaddr*)(&clientAddress), sizeof(clientAddress)) < 0)
    std::cout << "Oh no! Send failure!" << std::endl;
}

/** InitSocket
Initializes and binds the server socket on the number set
by portNum.

@param  portNum : [in] port number to use
@return EErrType type of error that occurred
*/
EErrType ServerSocket::InitSocket(const int portNum)
{
  WSADATA wsa;
  
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    return EErrType::SocketOpen;
  
  m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (m_Socket == INVALID_SOCKET)
    return EErrType::SocketOpen;
  
  memset((char*) &m_AddrInMe, 0, sizeof(m_AddrInMe));
  m_AddrInMe.sin_family       = AF_INET;
  m_AddrInMe.sin_port         = htons(portNum);
  m_AddrInMe.sin_addr.s_addr  = htonl(INADDR_ANY);
  
  // attempt to bind to socket
  if ((bind(m_Socket, (struct sockaddr*)(&m_AddrInMe), sizeof(m_AddrInMe))) == SOCKET_ERROR)
    return EErrType::Bind;
  
  return EErrType::None;
}