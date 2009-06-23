/* 
   CBugSocket.h

	Classe de controle de conexão via socket

	Baseada na Socket.h
   Copyright (C) 2002-2004 René Nyffenegger
   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

   @autor Paulo
*/

#pragma warning(push)
#pragma warning(disable:4996)

#include "CBugSocket.h"
#include <iostream>

using namespace std;

int CBugSocket::_nofSockets = 0;

void CBugSocket::Start() {
  if (!_nofSockets) {
    WSADATA info;
    if (WSAStartup(MAKEWORD(2,0), &info)) {
      throw "Could not start WSA";
    }
  }
  ++_nofSockets;
}

void CBugSocket::End() {
  WSACleanup();
}

CBugSocket::CBugSocket() : _socket(0) {
  Start();
  // UDP: use SOCK_DGRAM instead of SOCK_STREAM
  _socket = socket(AF_INET,SOCK_STREAM,0);

  if (_socket == INVALID_SOCKET) {
    throw "INVALID_SOCKET";
  }

  _refCounter = new int(1);
}

CBugSocket::CBugSocket(SOCKET s) : _socket(s) {
  Start();
  _refCounter = new int(1);
};

CBugSocket::~CBugSocket() {
  if (! --(*_refCounter)) {
    Close();
    delete _refCounter;
  }

  --_nofSockets;
  if (!_nofSockets) End();
}

CBugSocket::CBugSocket(const CBugSocket& o) {
  _refCounter=o._refCounter;
  (*_refCounter)++;
  _socket         =o._socket;

  _nofSockets++;
}

CBugSocket& CBugSocket::operator=(CBugSocket& o) {
  (*o._refCounter)++;

  _refCounter=o._refCounter;
  _socket         =o._socket;

  _nofSockets++;

  return *this;
}

void CBugSocket::Close() {
  closesocket(_socket);
}

std::string CBugSocket::ReceiveBytes() {
  std::string ret;
  char buf[1024];
 
  while (1) {
    u_long arg = 0;
    if (ioctlsocket(_socket, FIONREAD, &arg) != 0)
      break;

    if (arg == 0)
      break;

    if (arg > 1024) arg = 1024;

    int rv = recv (_socket, buf, arg, 0);
    if (rv <= 0) break;

    std::string t;

    t.assign (buf, rv);
    ret += t;
  }
 
  return ret;
}

void CBugSocket::ReceiveLine(CBugMessage * m) {
  while (1) {
    char r;

    switch(recv(_socket, &r, 1, 0)) {
      case 0: // not connected anymore;
              // ... but last line sent
              // might not end in \n,
              // so return ret anyway.
        return;
      case -1:
        return;
//      if (errno == EAGAIN) {
//        return ret;
//      } else {
//      // not connected anymore
//      return "";
//      }
    }

	m->_data += r;
    if (r == '\n')
	{
		return;
	}
  }
}

void CBugSocket::SendLine(CBugMessage * m) {
	//std::string s;
	//send(_socket,s.c_str(),s.length(),0);
	m->_data += '\n';

	send(_socket,m->_data.c_str(), m->getSize(), 0);
  
}

void CBugSocket::SendBytes(const std::string& s) {
  send(_socket,s.c_str(),s.length(),0);
}

CBugSocketServer::CBugSocketServer(int port, int connections, TypeSocket type) {
  sockaddr_in sa;

  memset(&sa, 0, sizeof(sa));

  sa.sin_family = PF_INET;             
  sa.sin_port = htons(port);          
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket == INVALID_SOCKET) {
    throw "INVALID_SOCKET";
  }

  if(type==NonBlockingSocket) {
    u_long arg = 1;
    ioctlsocket(_socket, FIONBIO, &arg);
  }

  /* bind the socket to the internet address */
  if (bind(_socket, (sockaddr *)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
    closesocket(_socket);
    throw "INVALID_SOCKET";
  }
  
  listen(_socket, connections);                               
}

CBugSocket* CBugSocketServer::Accept() {
  SOCKET new_sock = accept(_socket, 0, 0);
  if (new_sock == INVALID_SOCKET) {
    int rc = WSAGetLastError();
    if(rc==WSAEWOULDBLOCK) {
      return 0; // non-blocking call, no request pending
    }
    else {
      throw "Invalid Socket";
    }
  }

  CBugSocket* r = new CBugSocket(new_sock);
  return r;
}

CBugSocketClient::CBugSocketClient(const std::string& host, int port) : CBugSocket() {
  std::string error;

  hostent *he;
  if ((he = gethostbyname(host.c_str())) == 0) {
	  error = strerror(errno);
    throw error;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = *((in_addr *)he->h_addr);
  memset(&(addr.sin_zero), 0, 8); 

  if (::connect(_socket, (sockaddr *) &addr, sizeof(sockaddr))) {
    error = strerror(WSAGetLastError());
    throw error;
  }
}

CBugSocketSelect::CBugSocketSelect(CBugSocket const * const s1, CBugSocket const * const s2, TypeSocket type) {
  FD_ZERO(&fds_);
  FD_SET(const_cast<CBugSocket*>(s1)->_socket,&fds_);
  if(s2) {
    FD_SET(const_cast<CBugSocket*>(s2)->_socket,&fds_);
  }     

  TIMEVAL tval;
  tval.tv_sec  = 0;
  tval.tv_usec = 1;

  TIMEVAL *ptval;
  if(type==NonBlockingSocket) {
    ptval = &tval;
  }
  else { 
    ptval = 0;
  }

  if (select (0, &fds_, (fd_set*) 0, (fd_set*) 0, ptval) == SOCKET_ERROR) 
    throw "Error in select";
}

bool CBugSocketSelect::Readable(CBugSocket const* const s) {
  if (FD_ISSET(s->_socket,&fds_)) return true;
  return false;
}

#pragma warning(pop)
