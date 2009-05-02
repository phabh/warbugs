/******************************************************************************************

	Funções da classe dreamServer

*******************************************************************************************/
#include "dreamServer.h"
#include "dreamSock.h"
#include "dreamClient.h"
#include "dreamMessage.h"

dreamServer::dreamServer()
{
	_init			= false;
	_port			= 0;
	_runningIndex	= 1;
	_socket			= 0;
	_clientList		= NULL;
}

dreamServer::~dreamServer()
{
	dreamClient *list = _clientList;
	dreamClient *next;

	while(list != NULL)
	{
		next = list->_next;
		if(list)
		{
			free(list);
		}

		list = next;
	}

	_clientList = NULL;

	dreamSock_CloseSocket(_socket);
}

int dreamServer::initialize(char *localIP, int serverPort)
{

	// Initialize dreamSock if it is not already initialized
	dreamSock_Initialize();

	// Store the server IP and port for later use
	_port = serverPort;

	// Create server socket
	_socket = dreamSock_OpenUDPSocket(localIP, _port);

	if(_socket == DREAMSOCK_INVALID_SOCKET)
	{
		return DREAMSOCK_SERVER_ERROR;
	}

	_init = true;
	return 0;
}

void dreamServer::uninitialize(void)
{
	dreamSock_CloseSocket(_socket);
	_init = false;
}

void dreamServer::sendAddClient(dreamClient *newClient)
{
	// Send connection confirmation
	newClient->_message.init(newClient->_message._outgoingData, sizeof(newClient->_message._outgoingData));

	//-101 = DREAMSOCK_MES_CONNECT
	newClient->_message.writeByte(-101); // type
	newClient->sendPacket();

	// Send 'Add client' message to every client
	dreamClient *client = _clientList;

	// First inform the new client of the other clients
	for(; client != NULL; client = client->_next)
	{
		newClient->_message.init(newClient->_message._outgoingData, sizeof(newClient->_message._outgoingData));
		//-103 = DREAMSOCK_MES_ADDCLIENT
		newClient->_message.writeByte(-103); // type

		if(client == newClient)
		{
			newClient->_message.writeByte(1); // local client
			newClient->_message.writeByte(client->getIndex());
			newClient->_message.writeString(client->getName());
		}
		else
		{
			newClient->_message.writeByte(0); // not local client
			newClient->_message.writeByte(client->getIndex());
			newClient->_message.writeString(client->getName());
		}

		newClient->sendPacket();
	}

	// Then tell the others about the new client
	for(client = _clientList; client != NULL; client = client->_next)
	{
		if(client == newClient)
			continue;

		client->_message.init(client->_message._outgoingData, sizeof(client->_message._outgoingData));
		//-103 = DREAMSOCK_MES_ADDCLIENT
		client->_message.writeByte(-103); // type
		client->_message.writeByte(0);
		client->_message.writeByte(newClient->getIndex());
		client->_message.writeString(newClient->getName());
		client->sendPacket();
	}
}

void dreamServer::sendRemoveClient(dreamClient *client)
{
	int index = client->getIndex();

	// Send 'Remove client' message to every client
	dreamClient *list = _clientList;

	for(; list != NULL; list = list->_next)
	{
		list->_message.init(list->_message._outgoingData, sizeof(list->_message._outgoingData));
		//-104 = DREAMSOCK_MES_REMOVECLIENT
		list->_message.writeByte(-104); // type
		list->_message.writeByte(index); // index
	}

	sendPackets();

	// Send disconnection confirmation
	client->_message.init(client->_message._outgoingData, sizeof(client->_message._outgoingData));
	//-102 = DREAMSOCK_MES_DISCONNECT
	client->_message.writeByte(-102);
	client->sendPacket();
}

void dreamServer::sendPing(void)
{
	// Send ping message to every client
	dreamClient *list = _clientList;

	for(; list != NULL; list = list->_next)
	{
		list->sendPing();
	}
}

void dreamServer::addClient(struct sockaddr *address, char *name)
{
	// First get a pointer to the beginning of client list
	dreamClient *list = _clientList;
	dreamClient *prev;
	dreamClient *newClient;
	//LogString("LIB: Adding client, index %d", _runningIndex);

	// No clients yet, adding the first one
	if(_clientList == NULL)
	{
	//	LogString("LIB: Server: Adding first client");
		_clientList = (dreamClient *) calloc(1, sizeof(dreamClient));
		_clientList->setSocket(_socket);
		_clientList->setSocketAddress(address);
		_clientList->setConnectionState(DREAMSOCK_CONNECTING);
		_clientList->setOutgoingSequence(1);
		_clientList->setIncomingSequence(0);
		_clientList->setIncomingAcknowledged(0);
		_clientList->setIndex(_runningIndex);
		_clientList->setName(name);
		_clientList->_next = NULL;
		newClient = _clientList;
	}
	else
	{
	//	LogString("LIB: Server: Adding another client");
		prev = list;
		list = _clientList->_next;
		while(list != NULL)
		{
			prev = list;
			list = list->_next;
		}
		list = (dreamClient *) calloc(1, sizeof(dreamClient));
		list->setSocket(_socket);
		list->setSocketAddress(address);
		list->setConnectionState(DREAMSOCK_CONNECTING);
		list->setOutgoingSequence(1);
		list->setIncomingSequence(0);
		list->setIncomingAcknowledged(0);
		list->setIndex(_runningIndex);
		list->setName(name);
		list->_next = NULL;
		prev->_next = list;
		newClient = list;
	}

	_runningIndex++;
	sendAddClient(newClient);
}

void dreamServer::removeClient(dreamClient *client)
{
	dreamClient *list = NULL;
	dreamClient *prev = NULL;
	dreamClient *next = NULL;

	int index = client->getIndex();
	//LogString("LIB: Removing client with index %d", index);

	sendRemoveClient(client);

	for(list = _clientList; list != NULL; list = list->_next)
	{
		if(client == list)
		{
			if(prev != NULL)
			{
				prev->_next = client->_next;
			}
			break;
		}

		prev = list;
	}

	if(client == _clientList)
	{
	//	LogString("LIB: Server: removing first client in list");
		if(list) next = list->_next;
		if(client) free(client);
		client = NULL;
		_clientList = next;
	}
	else
	{
	//	LogString("LIB: Server: removing a client");
		if(list) next = list->_next;
		if(client) free(client);
		client = next;
	}
}

void dreamServer::parsePacket(dreamMessage *mes, struct sockaddr *address)
{
	mes->beginReading();

	int type = mes->readByte();

	// Find the correct client by comparing addresses
	dreamClient *clList = _clientList;

	// If we do not have clients yet, skip to message type checking
	if(clList != NULL)
	{
		for(; clList != NULL; clList = clList->_next)
		{
			if(memcmp(clList->getSocketAddress(), address, sizeof(address)) == 0)
			{
				break;
			}
		}

		if(clList != NULL)
		{
			clList->setLastMessageTime(dreamSock_GetCurrentSystemTime());

			// Check if the type is a positive number-> is the packet sequenced
			if(type > 0)
			{
				unsigned short sequence = mes->readShort();
				unsigned short sequenceAck = mes->readShort();

				if(sequence <= clList->getIncomingSequence())
				{
	//				LogString("LIB: Server: Sequence mismatch(sequence: %ld <= incoming seq: %ld)", sequence, clList->getIncomingSequence());
				}

				clList->setDroppedPackets(sequence - (clList->getIncomingSequence() -1));
				clList->setIncomingSequence(sequence);
				clList->setIncomingAcknowledged(sequenceAck);
			}

			// Wait for one message before setting state to connected
			if(clList->getConnectionState() == DREAMSOCK_CONNECTING)
				clList->setConnectionState(DREAMSOCK_CONNECTED);
		}
	}

	// Parse through the system messages
	switch(type)
	{
		//-101 = DREAMSOCK_MES_CONNECT
		case -101:
			addClient(address, mes->readString());
	//		LogString("LIBRARY: Server: a client connected successfully");
			break;

		//-102 = DREAMSOCK_MES_DISCONNECT
		case -102:
			if(clList == NULL)
				break;

			removeClient(clList);
	//		LogString("LIBRARY: Server: a client disconnected");
			break;

		//-105 = DREAMSOCK_MES_PING
		case -105:
			//clList->setPing((dreamSock_GetCurrentSystemTime() – clList->getPingSent()));
			clList->setPing(dreamSock_GetCurrentSystemTime() - clList->getPingSent());
			break;
	}
}

int dreamServer::checkForTimeout(char *data, struct sockaddr *from)
{
	int currentTime = dreamSock_GetCurrentSystemTime();
	dreamClient *clList = _clientList;
	dreamClient *next;

	for(; clList != NULL;)
	{
		next = clList->_next;

		// Don't timeout when connecting
		if(clList->getConnectionState() == DREAMSOCK_CONNECTING)
		{
			clList = next;
			continue;
		}

		// Check if the client has been silent for 30 seconds
		// If yes, assume crashed and remove the client
		if((currentTime - clList->getLastMessageTime()) > 30000)
		{
	//		LogString("Client timeout, disconnecting (%d – %d = %d)", currentTime, clList->getLastMessageTime(), currentTime – clList->getLastMessageTime());

			// Build a 'fake' message so the application will also
			// receive notification of a client disconnecting
			dreamMessage mes;
			mes.init(data, sizeof(data));
			//-102 = DREAMSOCK_MES_DISCONNECT
			mes.writeByte(-102);
			*(struct sockaddr *) from = *clList->getSocketAddress();
			removeClient(clList);
			return mes.getSize();
		}

		clList = next;
	}

	return 0;
}

int dreamServer::getPacket(char *data, struct sockaddr *from)
{
	// Check if the server is set up
	if(!_socket)
		return 0;

	// Check for timeout
	int timeout = checkForTimeout(data, from);
	if(timeout)
		return timeout;

	// Wait for a while or incoming data
	int maxfd = _socket;

	fd_set allset;

	struct timeval waittime;

	waittime.tv_sec = 10 / 1000;
	waittime.tv_usec = (10 % 1000) * 1000;

	FD_ZERO(&allset);
	FD_SET(_socket, &allset);

	fd_set reading = allset;

	int nready = select(maxfd + 1, &reading, NULL, NULL, &waittime);
	if(!nready)
		return 0;

	// Read data of the socket
	int ret = 0;
	dreamMessage mes;
	mes.init(data, sizeof(data));
	ret = dreamSock_GetPacket(_socket, mes._data, from);

	if(ret <= 0)
		return 0;

	mes.setSize(ret);

	// Parse system messages
	parsePacket(&mes, from);

	return ret;
}

void dreamServer::sendPackets(void)
{
	// Check if the server is set up
	if(!socket)
		return;

	dreamClient *clList = _clientList;

	for(; clList != NULL; clList = clList->_next)
	{
		if(clList->_message.getSize() == 0)
			continue;

		clList->sendPacket();
	}
}