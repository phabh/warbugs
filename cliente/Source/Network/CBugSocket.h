/* 
   CBugSocket.h

	Classe de controle de conexão via socket

	Baseada na Socket.h
   Copyright (C) 2002-2004 René Nyffenegger
   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

   @autor Paulo
*/

#ifndef _CBUGSOCKET_H_
#define _CBUGSOCKET_H_

#include <WinSock2.h>

#include <string>
#include "CBugMessage.h"

enum TypeSocket {BlockingSocket, NonBlockingSocket};

class CBugSocket {
public:

  virtual ~CBugSocket();
  CBugSocket(const CBugSocket&);
  CBugSocket& operator=(CBugSocket&);

  void        ReceiveLine(CBugMessage *m);
  std::string ReceiveBytes();

  void   Close();

  // The parameter of SendLine is not a const reference
  // because SendLine modifes the std::string passed.
  void   SendLine (CBugMessage *mes);

  // The parameter of SendBytes is a const reference
  // because SendBytes does not modify the std::string passed 
  // (in contrast to SendLine).
  void   SendBytes(const std::string&);

protected:
  friend class CBugSocketServer;
  friend class CBugSocketSelect;

  CBugSocket(SOCKET s);
  CBugSocket();


  SOCKET _socket;

  int* _refCounter;

private:
  static void Start();
  static void End();
  static int  _nofSockets;
};

class CBugSocketClient : public CBugSocket {
public:
  CBugSocketClient(const std::string& host, int port);
};

class CBugSocketServer : public CBugSocket {
public:
  CBugSocketServer(int port, int connections, TypeSocket type=BlockingSocket);

  CBugSocket* Accept();
};

// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/wsapiref_2tiq.asp
class CBugSocketSelect {
  public:
    CBugSocketSelect(CBugSocket const * const s1, CBugSocket const * const s2=NULL, TypeSocket type=BlockingSocket);

    bool Readable(CBugSocket const * const s);

  private:
    fd_set fds_;
}; 



#endif
