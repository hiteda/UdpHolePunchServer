/******************************************************************
@file:        Server.cpp
@author:      David Hite
@created:     11/14/2017
*******************************************************************/
#include "Server.h"
#include <iostream>

using namespace GoopsPuncher;
using std::string;

Server::Server()
: m_pClientMap(std::unique_ptr<ClientMap>(new ClientMap()))
{
}

void Server::Run()
{
  std::cout << "Hey there!" << std::endl;
}