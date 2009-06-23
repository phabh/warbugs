#ifndef _CSERVERSOCKETTHREAD_CPP_
#define _CSERVERSOCKETTHREAD_CPP_
/*
 * Server.cpp
 *
 *  Created on: 01/12/2008
 *      Author: kurumim
 */

#include "CServerSocketThread.h"
#include "CClientSocketThread.h"

//CDoubleList<CClientSocketThread *> CServerSocketThread::connectList;
///////////////////////////////////////////////////////////////////////

CServerSocketThread::CServerSocketThread(int port, int numConnections) {
	serverSocket = new CBugSocketServer(port,numConnections);
	this->Start(NULL);
}

CServerSocketThread::~CServerSocketThread() {
	// TODO Auto-generated destructor stub
}

void CServerSocketThread::Execute()
{
	this->createServer();
}
void CServerSocketThread::Setup()
{
        // Do any setup here
}

void CServerSocketThread::createServer(void)
{
	try
	{
	    while ( true )
		{
			//TODO:cria um socket para o cliente
			CBugSocket * newSocket = serverSocket->Accept();
			CClientSocketThread * newClient = new CClientSocketThread(newSocket);
	 	    
			//adiciona na lista
			EnterCriticalSection(&sessaoCritica);
			connectList.push_back(newClient);
			LeaveCriticalSection(&sessaoCritica);

			//inicia o while
			newClient->startReceiveThread();
		  
		}
	}
	catch (...)
	{
		EndThread();
		//std::cout << "Erro para criar o servidor: " << e.description() << "\nSaindo.\n";
	}
}

std::list<CClientSocketThread *> CServerSocketThread::getListClients()
{
	std::list<CClientSocketThread * > listaTemp;

	EnterCriticalSection(&sessaoCritica);
	while(connectList.size() > 0)
	{
		try
		{
			CClientSocketThread * c = connectList.front();
			listaTemp.push_back(c);
			connectList.pop_front();
		}
		catch(...)
		{
			//No caso de erro acho eu que a lista não armazenará o dado
			//isso é so para evitar que eu esteja errado
			listaTemp.pop_back();

			return listaTemp;
		}
	}
	LeaveCriticalSection(&sessaoCritica);

	return listaTemp;

}
#endif