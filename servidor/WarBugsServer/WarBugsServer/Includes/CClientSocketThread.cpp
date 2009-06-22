/*
 * Server.cpp
 *
 *  Created on: 01/12/2008
 *      Author: kurumim
 */

#include "CClientSocketThread.h"


CClientSocketThread::CClientSocketThread(CBugSocket *s)
{
	clientSocket = s;
}

CClientSocketThread::CClientSocketThread(std::string host, int port)
{
	clientSocket = new CBugSocketClient( host, port);
}

CClientSocketThread::~CClientSocketThread()
{

}

void CClientSocketThread::Execute()
{
	try
	{
		_connected = true;

	    while ( true )
		{
			receiveMessage();
		}
	}
	catch (...)
	{
		_connected = false;
		EndThread();
		//	std::cout << "Erro para criar o client: " << e.description() << "\nSaindo.\n";
	}
}

void CClientSocketThread::Setup()
{
	
}

void CClientSocketThread::startReceiveThread()
{
	this->Start(NULL);
}

void CClientSocketThread::receiveMessage()
{
	CBugMessage msgTemp;
	//msgTemp.init();

	clientSocket->ReceiveLine(&msgTemp);

	if(msgTemp.getSize() <= 0)
	{
		_connected = false;
		EndThread();
	}

	EnterCriticalSection(&sessaoCritica);
	bufferMessage.push_back(msgTemp);
	LeaveCriticalSection(&sessaoCritica);
}


void CClientSocketThread::sendMessage(CBugMessage * msg)
{
	clientSocket->SendLine(msg);
}


std::list<CBugMessage> CClientSocketThread::getListMessage()
{
	std::list<CBugMessage> tempList;

	EnterCriticalSection(&sessaoCritica);
	while(bufferMessage.size() > 0)
	{
		try
		{
			CBugMessage mes = bufferMessage.front();
			tempList.push_back(mes);
			bufferMessage.pop_front();
		}
		catch(...)
		{
			return tempList;
		}
	}
	LeaveCriticalSection(&sessaoCritica);

	return tempList;

}

void CClientSocketThread::close()
{
	_connected = false;
	EndThread();
}
