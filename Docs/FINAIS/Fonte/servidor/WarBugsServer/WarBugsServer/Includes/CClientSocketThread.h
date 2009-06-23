#ifndef _CLIENTSOCKETTHREAD_H_
#define _CLIENTSOCKETTHREAD_H_

#include "CBugSocket.h"
#include "CThread.h"
//#include "CDoubleList.h"
#include <list>

class CClientSocketThread : public CThread
{
private:
	CBugSocket * clientSocket;

public:
	bool _connected;
	
	std::list<CBugMessage> bufferMessage;

	CClientSocketThread(CBugSocket *s);
	CClientSocketThread(std::string host, int port);
	~CClientSocketThread();
	void Execute();
	void Setup();

	void startReceiveThread();

	void close();

	void receiveMessage();
	void sendMessage(CBugMessage * msg);


	std::list<CBugMessage> getListMessage();
	
};
#endif