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
#include "CBugThread.h"
#include "CDoubleList.h"


enum TypeSocket {BlockingSocket, NonBlockingSocket};

class CBugSocket : public CBugThread
{
public:

	virtual ~CBugSocket();
	CBugSocket(const CBugSocket&);
	CBugSocket& operator=(CBugSocket&);

	void ReceiveLine(CBugMessage * m);
	std::string ReceiveBytes();

	void   Close();

	bool   run();

	CDoubleList<CBugMessage> * bufferMensagens;

	void   SendLine(CBugMessage * m);

	void   SendBytes(const std::string&);

	void  limpaBufferMensagens();

protected:
	friend class CBugSocketServer;
	friend class CBugSocketSelect;

	CBugSocket(SOCKET s);
	CBugSocket();


	SOCKET _socket;

	int* _refCounter;

private:
	static void Inicia();
	static void Finaliza();
	static int  _nofSockets;

};


class CBugSocketClient : public CBugSocket 
{
public:
  CBugSocketClient(const std::string& host, int port);
};

class CBugSocketServer : public CBugSocket 
{
public:

	CDoubleList<CBugSocket> * bufferConexoes;

	void  limpaBufferConexoes();

    CBugSocketServer(int port, int connections, TypeSocket type=BlockingSocket);

    CBugSocket* Accept();

	bool run();
};


class CBugSocketSelect 
{
  public:
    CBugSocketSelect(CBugSocket const * const s1, CBugSocket const * const s2=NULL, TypeSocket type=BlockingSocket);

    bool Readable(CBugSocket const * const s);

  private:
    fd_set fds_;
}; 



#endif
