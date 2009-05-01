/*************************************************************************************************

	Funções da Classe dreamClient

**************************************************************************************************/
#include "dreamClient.h"
#include "dreamSock.h"
#include "dreamMessage.h"

dreamClient::dreamClient()
{
	_connectionState		= DREAMSOCK_DISCONNECTED;
	_outgoingSequence		= 1;
	_incomingSequence		= 0;
	_incomingAcknowledged	= 0;
	_droppedPackets			= 0;
	_init					= false;
	_serverPort				= 0;
	_pingSent				= 0;
	_ping					= 0;
	_lastMessageTime		= 0;
	_next					= NULL;
}

dreamClient::~dreamClient()
{
	dreamSock_CloseSocket(_socket);
}

int dreamClient::initialize(char *localIP, char *remoteIP, int port)
{
	// Initialize dreamSock if it is not already initialized
	dreamSock_Initialize();

	// Save server's address information for later use
	_serverPort = port;
	strcpy(_serverIP, remoteIP);
	//LogString("Server's information: IP address: %s, port: %d", _serverIP, _serverPort);

	// Create client socket
	_socket = dreamSock_OpenUDPSocket(localIP, 0);

	// Check that the address is not empty
	u_long inetAddr = inet_addr(_serverIP);

	if(inetAddr == INADDR_NONE)
	{
		return DREAMSOCK_CLIENT_ERROR;
	}

	if(_socket == DREAMSOCK_INVALID_SOCKET)
	{
		return DREAMSOCK_CLIENT_ERROR;
	}

	_init = true;

	return 0;
}

void dreamClient::uninitialize(void)
{
	dreamSock_CloseSocket(_socket);
	reset();
	_init = false;
}

void dreamClient::reset(void)
{
	_connectionState		= DREAMSOCK_DISCONNECTED;
	_outgoingSequence		= 1;
	_incomingSequence		= 0;
	_incomingAcknowledged	= 0;
	_droppedPackets			= 0;
	_pingSent				= 0;
	_ping					= 0;
	_lastMessageTime		= 0;
	_next					= NULL;
}

void dreamClient::dumpBuffer(void)
{
	char data[1400];
	int ret;

	while((ret = dreamSock_GetPacket(_socket, data, NULL)) > 0)
	{
	}
}

void dreamClient::sendConnect(char *name)
{
	// Dump buffer so there won't be any old packets to process
	dumpBuffer();
	_connectionState = DREAMSOCK_CONNECTING;

	_message.init(_message._outgoingData, sizeof(_message._outgoingData));
	//-101 = DREAMSOCK_MES_CONNECT
	_message.writeByte(-101);
	_message.writeString(name);

	sendPacket(&_message);
}

void dreamClient::sendDisconnect(void)
{
	_message.init(_message._outgoingData, sizeof(_message._outgoingData));
	//-102 = DREAMSOCK_MES_DISCONNECT
	_message.writeByte(-102);

	sendPacket(&_message);

	reset();

	_connectionState = DREAMSOCK_DISCONNECTING;
}

void dreamClient::sendPing(void)
{
	_pingSent = dreamSock_GetCurrentSystemTime();
	_message.init(_message._outgoingData, sizeof(_message._outgoingData));
	//-105 = DREAMSOCK_MES_PING
	_message.writeByte(-105);
	sendPacket(&_message);
}

void dreamClient::parsePacket(dreamMessage *mes)
{
	mes->beginReading();
	int type = mes->readByte();

	// Check if the type is a positive number = is the packet sequenced
	if(type > 0)
	{
		unsigned short sequence = mes->readShort();
		unsigned short sequenceAck = mes->readShort();

		if(sequence <= _incomingSequence)
		{
//			LogString("Client: (sequence: %d <= incoming seq: %d)",	sequence, _incomingSequence);
//			LogString("Client: Sequence mismatch");
		}

		_droppedPackets = (sequence - _incomingSequence) + 1;
		_incomingSequence = sequence;
		_incomingAcknowledged = sequenceAck;
	}

	// Parse through the system messages
	switch(type)
	{
		//-101 = DREAMSOCK_MES_CONNECT
		case -101:
			_connectionState = DREAMSOCK_CONNECTED;
//			LogString("LIBRARY: Client: got connect confirmation");
			break;

		//-102 = DREAMSOCK_MES_DISCONNECT
		case -102:
			_connectionState = DREAMSOCK_DISCONNECTED;
			//LogString("LIBRARY: Client: got disconnect confirmation");
			break;

		//-103 = DREAMSOCK_MES_ADDCLIENT
		case -103:
			//LogString("LIBRARY: Client: adding a client");
			break;

		//-104 = DREAMSOCK_MES_REMOVECLIENT
		case -104:
			//LogString("LIBRARY: Client: removing a client");
			break;

		//-105 = DREAMSOCK_MES_PING
		case -105:
			sendPing();
			break;
	}
}

int dreamClient::getPacket(char *data, struct sockaddr *from)
{
	// Check if the client is set up or if it is disconnecting
	if(!_socket)
		return 0;

	int ret;
	dreamMessage mes;

	mes.init(data, sizeof(data));
	ret = dreamSock_GetPacket(_socket, mes._data, from);

	if(ret <= 0)
		return 0;

	mes.setSize(ret);

	// Parse system messages
	parsePacket(&mes);

	return ret;
}

void dreamClient::sendPacket(void)
{
	// Check that everything is set up
	if(!_socket || _connectionState == DREAMSOCK_DISCONNECTED)
	{
//		LogString("SendPacket error: Could not send because the client is disconnected");
		return;
	}

	// If the message overflowed, do not send it
	if(_message.getOverFlow())
	{
		//LogString("SendPacket error: Could not send because the buffer overflowed");
		return;
	}

	// Check if serverPort is set. If it is, we are a client sending to
	// the server. Otherwise we are a server sending to a client.
	if(_serverPort)
	{
		struct sockaddr_in sendToAddress;
		memset((char *) &sendToAddress, 0, sizeof(sendToAddress));
		u_long inetAddr = inet_addr(_serverIP);

		sendToAddress.sin_port = htons((u_short) _serverPort);
		sendToAddress.sin_family = AF_INET;
		sendToAddress.sin_addr.s_addr = inetAddr;
		dreamSock_SendPacket(_socket, _message.getSize(), _message._data, *(struct sockaddr *) &sendToAddress);
	}
	else
	{
		dreamSock_SendPacket(_socket, _message.getSize(), _message._data, _myaddress);
	}

	// Check if the packet is sequenced
	_message.beginReading();

	int type = _message.readByte();

	if(type > 0)
	{
		_outgoingSequence++;
	}
}


void dreamClient::sendPacket(dreamMessage *theMes)
{
	// Check that everything is set up
	if(!_socket || _connectionState == DREAMSOCK_DISCONNECTED)
	{
		//LogString("SendPacket error: Could not send because the client is disconnected");
		return;
	}

	// If the message overflowed, do not send it
	if(theMes->getOverFlow())
	{
		//LogString("SendPacket error: Could not send because the buffer overflowed");
		return;
	}

	// Check if serverPort is set. If it is, we are a client sending to
	// the server. Otherwise we are a server sending to a client.
	if(_serverPort)
	{
		struct sockaddr_in sendToAddress;
		memset((char *) &sendToAddress, 0, sizeof(sendToAddress));
		u_long inetAddr = inet_addr(_serverIP);

		sendToAddress.sin_port = htons((u_short) _serverPort);
		sendToAddress.sin_family = AF_INET;
		sendToAddress.sin_addr.s_addr = inetAddr;

		dreamSock_SendPacket(_socket, theMes->getSize(), theMes->_data, *(struct sockaddr *) &sendToAddress);
	}
	else
	{
		dreamSock_SendPacket(_socket, theMes->getSize(), theMes->_data, _myaddress);
	}

	// Check if the packet is sequenced
	theMes->beginReading();
	int type = theMes->readByte();

	if(type > 0)
	{
		_outgoingSequence++;
	}
}