#ifdef WIN32
// Windows-specific headers
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <windows.h>
#include <winsock2.h>
#else
// Unix-specific headers
#include <memory.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
// Common headers
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "dreamSock.h"
//#include "dreamSockLog.h"


/*************************************************************************************

	Funções de Configuração da dreamSock

*************************************************************************************/

int dreamSock_Initialize(void)
{
	if(_dreamSock_init == true)
		return 0;

	_dreamSock_init = true;

//	StartLog();

	#ifdef WIN32
		return dreamSock_InitializeWinSock();
	#else
		return 0;
	#endif
}

int dreamSock_InitializeWinSock(void)
{
	WORD versionRequested;
	WSADATA wsaData;
	DWORD bufferSize = 0;
	LPWSAPROTOCOL_INFO SelectedProtocol;
	int NumProtocols;
	
	// Start WinSock2. If it fails, we do not need to call WSACleanup()
	versionRequested = MAKEWORD(2, 0);
	int error = WSAStartup(versionRequested, &wsaData);
	if(error)
	{
		//LogString("FATAL ERROR: WSAStartup failed (error = %d)", error);
		return 1;
	}
	else
	{
		//LogString("WSAStartup OK");

		// Confirm that the WinSock2 DLL supports the exact version we want. If not, call WSACleanup().
		if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion)!= 0)
		{
			//LogString("FATAL ERROR: WinSock2 DLL does not support the correct version (%d.%d)",	LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
			WSACleanup();
			return 1;
		}
	}

	// Call WSAEnumProtocols to figure out how big of a buffer we need
	NumProtocols = WSAEnumProtocols(NULL, NULL, &bufferSize);
	if((NumProtocols != SOCKET_ERROR) && (WSAGetLastError() != WSAENOBUFS))
	{
		WSACleanup();
		return 1;
	}

	// Allocate a buffer and call WSAEnumProtocols to get an array of
	// WSAPROTOCOL_INFO structs
	SelectedProtocol = (LPWSAPROTOCOL_INFO) malloc(bufferSize);
	if(SelectedProtocol == NULL)
	{
		WSACleanup();
		return 1;
	}

	// Allocate memory for protocol list and define the protocols to look for
	int *protos = (int *) calloc(2, sizeof(int));
	protos[0] = IPPROTO_TCP;
	protos[1] = IPPROTO_UDP;
	NumProtocols = WSAEnumProtocols(protos, SelectedProtocol, &bufferSize);
	free(protos);
	protos = NULL;
	free(SelectedProtocol);
	SelectedProtocol = NULL;

	if(NumProtocols == SOCKET_ERROR)
	{
		//LogString("FATAL ERROR: Didn't find any required protocols");
		WSACleanup();
		return 1;
	}

	return 0;
}

void dreamSock_Shutdown(void)
{
	if(_dreamSock_init == false)
		return;

	//LogString("Shutting down dreamSock");
	_dreamSock_init = false;
//	StopLog();

	#ifdef WIN32
		WSACleanup();
	#endif
}

/***************************************************************************************

	Funções de Socket da dreamSock

****************************************************************************************/

SOCKET dreamSock_Socket(int protocol)
{
	int type;
	int proto;
	SOCKET sock;

	// Check which protocol to use
	if(protocol == DREAMSOCK_TCP)
	{
		type = SOCK_STREAM;
		proto = IPPROTO_TCP;
	}
	else
	{
		type = SOCK_DGRAM;
		proto = IPPROTO_UDP;
	}

	// Create the socket
	if((sock = socket(AF_INET, type, proto)) ==  INVALID_SOCKET)
	{
		//LogString("dreamSock_Socket - socket() failed");
		#ifdef WIN32
			errno = WSAGetLastError();
			//LogString("Error: socket() code %d : %s", errno, strerror(errno));
		#else
			LogString("Error: socket() : %s", strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}
		

	return sock;
}

int dreamSock_SetNonBlocking(SOCKET sock, u_long setMode)
{
	u_long set = setMode;

	// Set the socket option
	#ifdef WIN32
		return ioctlsocket(sock, FIONBIO, &set);
	#else
		return ioctl(sock, FIONBIO, &set);
	#endif
}

int dreamSock_SetBroadcasting(SOCKET sock, int mode)
{
	// make it broadcast capable
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &mode,sizeof(int)) < 0)
	{
		//LogString("DreamSock_SetBroadcasting failed");

		#ifdef WIN32
			int err = WSAGetLastError();
			//LogString("Error code %d: setsockopt() : %s", err, strerror(err));
		#else
			LogString("Error code %d: setsockopt() : %s", errno,
			strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	return 0;
}

int dreamSock_StringToSockaddr(char *addressString, struct sockaddr *sadr)
{
	char copy[128];
	memset(sadr, 0, sizeof(struct sockaddr));
	struct sockaddr_in *addressPtr = (struct sockaddr_in *) sadr;
	addressPtr->sin_family = AF_INET;
	addressPtr->sin_port = htons(0);
	strcpy(copy, addressString);

	// If the address string begins with a number, assume an IP address
	if(copy[0] >= '0' && copy[0] <= '9')
	{
		*(int *) &addressPtr->sin_addr = inet_addr(copy);
		return 0;
	}
	else 
		return 1;
}

SOCKET dreamSock_OpenUDPSocket(char *netInterface, int port)
{
	SOCKET sock;
	struct sockaddr_in address;
	sock = dreamSock_Socket(DREAMSOCK_UDP);

	if(sock == DREAMSOCK_INVALID_SOCKET)
		return sock;

	dreamSock_SetNonBlocking(sock, 1);
	dreamSock_SetBroadcasting(sock, 1);

	// If no address string provided, use any interface available
	if(!netInterface || !netInterface[0] || !strcmp(netInterface,"localhost"))
	{
		//LogString("No net interface given, using any interface available");
		address.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		//LogString("Using net interface = '%s'", netInterface);
		dreamSock_StringToSockaddr(netInterface, (struct sockaddr *)&address);
	}

	// If no port number provided, use any port number available
	if(port == 0)
	{
		//LogString("No port defined, picking one for you");
		address.sin_port = 0;
	}
	else
	{
		address.sin_port = htons((short) port);
	}

	address.sin_family = AF_INET;

	// Bind the address to the socket
	if(bind(sock, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		#ifdef WIN32
			errno = WSAGetLastError();
			//LogString("Error code %d: bind() : %s", errno, strerror(errno));
		#else
			LogString("Error code %d: bind() : %s", errno, strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	// Get the port number (if we did not define one, we get the assigned port number here)
	socklen_t len = sizeof(address);
	getsockname(sock, (struct sockaddr *) &address, &len);
	//LogString("Opening UDP port = %d", ntohs(address.sin_port));

	return sock;
}

void dreamSock_CloseSocket(SOCKET sock)
{
	#ifdef WIN32
		closesocket(sock);
	#else
		close(sock);
	#endif
}

int dreamSock_GetPacket(SOCKET sock, char *data, struct sockaddr *from)
{
	int ret;
	struct sockaddr tempFrom;
	socklen_t fromlen;
	fromlen = sizeof(tempFrom);
	ret = recvfrom(sock, data, 1400, 0, (struct sockaddr *) &tempFrom,&fromlen);

	// Copy the address to the from pointer
	if(from != NULL)
		*(struct sockaddr *) from = tempFrom;

	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return ret;

			if(errno == WSAEMSGSIZE)
			{
				// ERROR: Oversize packet
				return ret;
			}

			//LogString("Error code %d: recvfrom() : %s", errno, strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK || errno == ECONNREFUSED)
				return ret;

			LogString("Error code %d: recvfrom() : %s", errno, strerror(errno));
		#endif

		return ret;
	}

	return ret;
}

void dreamSock_SendPacket(SOCKET sock, int length, char *data, struct sockaddr addr)
{
	int ret;
	ret = sendto(sock, data, length, 0, &addr, sizeof(addr));
	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return;

			//LogString("Error code %d: sendto() : %s", errno,strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK)
				return;

			LogString("Error code %d: sendto() : %s", errno,
			strerror(errno));
		#endif
	}

}

void dreamSock_Broadcast(SOCKET sock, int length, char *data, int port)
{
	struct sockaddr_in servaddr;
	socklen_t len;

	// Use broadcast address
	u_long inetAddr = inet_addr("255.255.255.255");

	// Fill address information structure
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inetAddr;
	len = sizeof(servaddr);

	// Broadcast!
	int ret = sendto(sock, data, length, 0, (struct sockaddr *) &servaddr, len);
	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return;

			//LogString("Error code %d: sendto() : %s", errno, strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK)
				return;

			LogString("Error code %d: sendto() : %s", errno,
			strerror(errno));
		#endif
	}

}

int dreamSock_Win_GetCurrentSystemTime(void)
{
	int curtime;
	static int base;
	static bool initialized = false;

	
	if(!initialized)
	{
		base = System::DateTime::Now.Millisecond;
		//base = timeGetTime() & 0xffff0000;
		initialized = true;
	}
	
	//curtime  = timeGetTime();
	//curtime =  (curtime) - (base);
	curtime = System::DateTime::Now.Millisecond - base;
	return curtime;
}

int dreamSock_GetCurrentSystemTime(void)
{
	#ifndef WIN32
		return dreamSock_Linux_GetCurrentSystemTime();
	#else
		return dreamSock_Win_GetCurrentSystemTime();
	#endif
}

/***************************************************************************

	Funções da Classe dreamMessage

****************************************************************************/

void dreamMessage::init(char *d, int length)
{
	_data = d;
	_maxSize = length;
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

void dreamMessage::clear(void)
{
	_size = 0;
	_readCount = 0;
	_overFlow = false;
}

char *dreamMessage::getNewPoint(int length)
{
	char *tempData;

	// Check for overflow
	if(_size + length > _maxSize)
	{
		clear();
		_overFlow = true;
	}

	tempData = _data + _size;
	_size += length;

	return tempData;
}

void dreamMessage::addSequences(dreamClient *client)
{
	writeShort(client->getOutgoingSequence());
	writeShort(client->getIncomingSequence());
}

void dreamMessage::write(void *d, int length)
{
	memcpy(getNewPoint(length), d, length);
}

void dreamMessage::writeByte(char c)
{
	char *buf;
	buf = getNewPoint(1);
	memcpy(buf, &c, 1);
}

void dreamMessage::writeShort(short c)
{
	char *buf;
	buf = getNewPoint(2);
	memcpy(buf, &c, 2);
}

void dreamMessage::writeLong(long c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void dreamMessage::writeFloat(float c)
{
	char *buf;
	buf = getNewPoint(4);
	memcpy(buf, &c, 4);
}

void dreamMessage::writeString(char *s)
{
	if(!s)
	{
		return;
	}
	else
		write(s, strlen(s) + 1);
}

void dreamMessage::beginReading(void)
{
	_readCount = 0;
}

void dreamMessage::beginReading(int s)
{
	_size = s;
	_readCount = 0;
}

char *dreamMessage::read(int s)
{
	static char c[2048];

	if(_readCount+s > _size)
		return NULL;
	else
		memcpy(&c, &_data[_readCount], s);

	_readCount += s;
	return c;
}

char dreamMessage::readByte(void)
{
	char c;

	if(_readCount+1 > _size)
		c = -1;
	else
		memcpy(&c, &_data[_readCount], 1);

	_readCount++;
	return c;
}

short dreamMessage::readShort(void)
{
	short c = -1;

	if(_readCount+2 <= _size)
		memcpy(&c, &_data[_readCount], 2);

	_readCount += 2;
	return c;
}

long dreamMessage::readLong(void)
{
	long c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

float dreamMessage::readFloat(void)
{
	float c = -1;

	if(_readCount+4 <= _size)
		memcpy(&c, &_data[_readCount], 4);

	_readCount += 4;
	return c;
}

char *dreamMessage::readString(void)
{
	static char string[2048];
	int l, c;

	l=0;
	do
	{
		c = readByte();

		if (c == -1 || c == 0)
			break;

		string[l] = c;
		l++;
	} while(l < (sizeof(string)-1));

	string[l] = 0;
	return string;
}

/*************************************************************************************************

	Fim funções da Classe dreamMessage

**************************************************************************************************/

/*************************************************************************************************

	Funções da Classe dreamClient

**************************************************************************************************/

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

/******************************************************************************************

	Fim das funções da classe dreamClient

*******************************************************************************************/

/******************************************************************************************

	Funções da classe dreamServer

*******************************************************************************************/

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