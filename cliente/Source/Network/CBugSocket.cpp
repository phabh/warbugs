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
	char buffer[6]  = "00000";
  int  contAntigo = 0, contAtual = 0;
	//std::string ret;
	//recv(_socket, m._data, 1400, 0);
  int erro;
	
  while (1) {
    char r;
    switch(recv(_socket, &r, 1, 0)) 
	{
	  case 0: // não está conectado
        return;
	  case SOCKET_ERROR: // 
		  {
				erro = WSAGetLastError();

				switch(erro)
				{
				
					case WSANOTINITIALISED:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("need to call WSAStartup to initialize socket system on Window system.");
							break;
						}		
					case WSAENETDOWN:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("The network subsystem has failed.");
							break;
						}
					case WSAHOST_NOT_FOUND:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("Authoritative Answer Host not found.");
							break;
						}
					case WSATRY_AGAIN:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("Non-Authoritative Host not found, or server failure.");
							break;
						}
					case WSANO_RECOVERY:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("Nonrecoverable error occurred.");
							break;
						}
					case WSANO_DATA:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("Valid name, no data record of requested type.");
							break;
						}
					case WSAEINPROGRESS:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.");
							break;
						}
					case WSAEFAULT:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("The name parameter is not a valid part of the user address space.");
							break;
						}
					case WSAEINTR:
						{
							m = new CBugMessage();
							return;
							//errorMsg.append("A blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall.");	
							break;
						}
					case WSAEWOULDBLOCK:
						{
							//m->writeByte(r);
							//Erro comum
							break;						
						}
					default:
						{
							
							if(erro != 0)
							{
								m = new CBugMessage();
								return;
							}
							break;
						}
				}
		  }// case Socket Error;        
    }


    //ret += r;
	m->writeByte(r);

	if(m->getOverFlow())
	{
		m = new CBugMessage();
		return;
	}

	contAtual += 1;


	// |FIM| sinaliza o fim do pacote
	switch(r)
	{
		case '|':
			{
				if(buffer[0] == '0')
				{
					buffer[0] = '|';
					contAntigo = contAtual;
				}
				else if(buffer[4] == '0' && 
					    buffer[3] == 'M' && 
						buffer[2] == 'I' && 
						buffer[1] == 'F' && 
						buffer[0] == '|' &&
						contAntigo == (contAtual-1))
				{
					buffer[4] = '|';
					return;
				}
				else
				{
					strcpy(buffer,"00000");
					contAntigo = 0;
				}
				break;
			}
		case 'F':
			{
				if(buffer[4] == '0' && 
				   buffer[3] == '0' && 
				   buffer[2] == '0' && 
				   buffer[1] == '0' && 
				   buffer[0] == '|' &&
				   contAntigo == (contAtual-1))
				{
					buffer[1] = 'F';
					contAntigo = contAtual;
				}
				else
				{
					strcpy(buffer,"00000");
					contAntigo = 0;
				}
				break;
			}
		case 'I':
			{
				if(buffer[4] == '0' && 
				   buffer[3] == '0' && 
				   buffer[2] == '0' && 
				   buffer[1] == 'F' && 
				   buffer[0] == '|' &&
				   contAntigo == (contAtual-1))
				{
					buffer[2] = 'I';
					contAntigo = contAtual;
				}
				else
				{
					strcpy(buffer,"00000");
					contAntigo = 0;
				}	
				break;
			}
		case 'M':
			{
				if(buffer[4] == '0' && 
				   buffer[3] == '0' && 
				   buffer[2] == 'I' && 
				   buffer[1] == 'F' && 
				   buffer[0] == '|' &&
				   contAntigo == (contAtual-1))
				{
					buffer[3] = 'M';
					contAntigo = contAtual;
				}
				else
				{
					strcpy(buffer,"00000");
					contAntigo = 0;
				}		
				break;
			}
	}
	
/*
    if (r == '|')
	{
		break;
	}
*/
  }
}

void CBugSocket::SendLine(CBugMessage * m) {
  m->writeByte('|');
  m->writeByte('F');
  m->writeByte('I');
  m->writeByte('M');
  m->writeByte('|');
  //s += '\n';
  //send(_socket,s.c_str(),s.length(),0);
	send(_socket,m->_data,m->getSize(),0);
  
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
