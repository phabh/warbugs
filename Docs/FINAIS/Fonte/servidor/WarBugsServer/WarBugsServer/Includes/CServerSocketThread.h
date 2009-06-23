/*
 * Server.h
 *
 *  Created on: 01/12/2008
 *      Author: kurumim
 */

#ifndef _CSERVERSOCKETTHREAD_H_
#define _CSERVERSOCKETTHREAD_H_
#include <iostream>
#include <string>
#include <list>
//#include "CDoubleList.h"

#include "CBugSocket.h"
#include "CClientSocketThread.h"
#include "CThread.h"

class CServerSocketThread:public CThread{
private:
	CBugSocketServer * serverSocket;
	void createServer();
protected:
	void Execute();
	void Setup();

public:
	std::list<CClientSocketThread *> connectList;			//contem a lista de sockets com os clientes conectados
	CServerSocketThread(int port, int numConnections);
	virtual ~CServerSocketThread();

	std::list<CClientSocketThread *> getListClients();
};


//////////////////////////////////////////////////////////////////////////////////
#endif /* SERVER_H_ */
