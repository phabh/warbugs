#ifndef __DREAMSOCK_H
#define __DREAMSOCK_H

//#include "dreamSockLog.h"

#ifdef WIN32
	#pragma comment (lib,"ws2_32.lib")
	#pragma message ("Auto linking WinSock2 library")
	#include <winsock2.h>
#else
	#include <string.h>
	#include <netinet/in.h>
#endif

#include <stdio.h>
#include <stddef.h>
#include <time.h>


// Define SOCKET data type for Unix (defined in WinSock for Win32)
// And socklen_t for Win32
#ifdef WIN32
	typedef int socklen_t;
#else
	typedef int SOCKET;

	#ifndef TRUE
		#define TRUE 1
	#endif
	#ifndef FALSE
		#define FALSE 0
	#endif
#endif

// Host types
#define DREAMSERVER –1
#define DREAMCLIENT	0

// Connection protocols
#define DREAMSOCK_TCP 0
#define DREAMSOCK_UDP 1

// Connection states
#define DREAMSOCK_CONNECTING	0
#define DREAMSOCK_CONNECTED		1
#define DREAMSOCK_DISCONNECTING 2
#define DREAMSOCK_DISCONNECTED	4

// Error codes
#define DREAMSOCK_SERVER_ERROR 1
#define DREAMSOCK_CLIENT_ERROR 2

#ifdef WIN32
	#define DREAMSOCK_INVALID_SOCKET INVALID_SOCKET
#else
	#define DREAMSOCK_INVALID_SOCKET –1
#endif

// System messages
// Note (for all messages — system and user):
// positive = sequenced message
// negative = unsequenced message

#define DREAMSOCK_MES_CONNECT –101
#define DREAMSOCK_MES_DISCONNECT –102
#define DREAMSOCK_MES_ADDCLIENT –103
#define DREAMSOCK_MES_REMOVECLIENT –104
#define DREAMSOCK_MES_PING –105


// Introduce classes
class dreamMessage;
class dreamClient;
class dreamServer;
class dreamSock;


class dreamMessage
{
	private:
		bool _overFlow;
		int  _maxSize;
		int  _size;
		int  _readCount;

		char *getNewPoint(int length);

	public:
		char  * _data;
		char    _outgoingData[1400];

		void    init(char *d, int length);

		void    clear(void);
		void    write(void *d, int length);
		void    addSequences(dreamClient *client);

		void    writeByte(char c);
		void    writeShort(short c);
		void    writeLong(long c);
		void    writeFloat(float c);
		void    writeString(char *s);
		void    beginReading(void);
		void    beginReading(int s);
		char  * read(int s);
		char    readByte(void);
		short   readShort(void);
		long    readLong(void);
		float   readFloat(void);
		char  * readString(void);

		bool    getOverFlow(void) {return _overFlow;}

		int     getSize(void) {return _size;}
		void    setSize(int s) {_size = s;}

};

class dreamClient
{
	private:
		int              _connectionState; // Connecting, connected, disconnecting, disconnected

		unsigned short   _outgoingSequence; // Outgoing packet sequence
		unsigned short   _incomingSequence; // Incoming packet sequence
		unsigned short   _incomingAcknowledged; // Last packet acknowledged by other end
		unsigned short   _droppedPackets; // Dropped packets

		int			     _serverPort; // Port
		char		     _serverIP[32]; // IP address
		int			     _index; // Client index (starts from 1, running number)

		char			 _name[32]; // Client name

		SOCKET			 _socket; // Socket
		struct sockaddr  _myaddress; // Socket address

		int				 _pingSent; // When did we send ping?
		int				 _ping; // Network latency
		int				 _lastMessageTime;

		bool			 _init;


		void dumpBuffer(void);
		void parsePacket(dreamMessage *mes);



	public:

		dreamMessage _message;
		dreamClient *_next;

		dreamClient();
		~dreamClient();

		int				  initialize(char *localIP, char *remoteIP, int port);
		void			  uninitialize(void);
		void			  reset(void);
		void			  sendConnect(char *name);
		void			  sendDisconnect(void);
		void			  sendPing(void);

		void			  setConnectionState(int con) {_connectionState = con;}
		int				  getConnectionState(void) {return _connectionState;}

		int				  getPacket(char *data, struct sockaddr *from);
		void			  sendPacket(void);
		void			  sendPacket(dreamMessage *message);

		unsigned short    getOutgoingSequence(void) {return _outgoingSequence;}
		void			  setOutgoingSequence(unsigned short seq){_outgoingSequence = seq;}
		void			  increaseOutgoingSequence(void) {_outgoingSequence++;}
		unsigned short    getIncomingSequence(void) {return _incomingSequence;}
		void			  setIncomingSequence(unsigned short seq) {_incomingSequence = seq;}
		unsigned short	  getIncomingAcknowledged(void) {return _incomingAcknowledged;}
		void			  setIncomingAcknowledged(unsigned short seq) {_incomingAcknowledged = seq;}
		unsigned short    getDroppedPackets(void) {return _droppedPackets;}
		void			  setDroppedPackets(unsigned short drop) {_droppedPackets = drop;}

		bool			  getInit(void) {return _init;}

		int				  getIndex(void) {return _index;}
		void			  setIndex(int ind) {_index = ind;}

		char		    * getName(void) {return _name;}
		void			  setName(char *n) {strcpy(_name, n);}

		SOCKET			  getSocket(void) {return _socket;}
		void		 	  setSocket(SOCKET sock) {_socket = sock;}

		struct sockaddr * getSocketAddress(void)					 {return &_myaddress;}
		void			  setSocketAddress(struct sockaddr *address) {memcpy(&_myaddress, address, sizeof(struct sockaddr));}

		int				  getPingSent(void) {return _pingSent;}
		void			  setPing(int p)	{_ping = p;}

		int				  getLastMessageTime(void) {return _lastMessageTime;}
		void			  setLastMessageTime(int t) {_lastMessageTime = t;}

};

class dreamServer
{
	private:
		dreamClient * _clientList;

		int			  _port; // Port

		SOCKET		  _socket; // Socket

		int			  _runningIndex; // Running index numbers for new clients

		bool		  _init;
		
		void		  sendAddClient(dreamClient *newClient);
		void		  sendRemoveClient(dreamClient *client);
		void		  addClient(struct sockaddr *address, char *name);
		void		  removeClient(dreamClient *client);
		void		  parsePacket(dreamMessage *mes, struct sockaddr	*address);
		int			  checkForTimeout(char *data, struct sockaddr *from);

	public:
		dreamServer();
		~dreamServer();

		int			  initialize(char *localIP, int serverPort);
		void		  uninitialize(void);

		void		  sendPing(void);

		int			  getPacket(char *data, struct sockaddr *from);
		void		  sendPackets(void);

		bool		  getInit(void) {return _init;}

		dreamClient * getClientList(void) {return _clientList;}

		int			  getPort(void) {return _port;}
};



/***************************************
dreamSock global functions
***************************************/

//Atributos
static bool   _dreamSock_init;

// Function prototypes

int    dreamSock_Initialize(void);
int	   dreamSock_InitializeWinSock(void);
void   dreamSock_Shutdown(void);

SOCKET dreamSock_Socket(int protocol);
int    dreamSock_SetNonBlocking(SOCKET sock, u_long setMode);
int    dreamSock_SetBroadcasting(SOCKET sock, int mode);
int    dreamSock_StringToSockaddr(char *addressString, struct sockaddr *sadr);
SOCKET dreamSock_OpenUDPSocket(char netInterface[32], int port);
void   dreamSock_CloseSocket(SOCKET sock);

int    dreamSock_GetPacket(SOCKET sock, char *data, struct sockaddr *from);
void   dreamSock_SendPacket(SOCKET sock, int length, char *data, struct sockaddr addr);
void   dreamSock_Broadcast(SOCKET sock, int length, char *data, int port);

#ifndef WIN32
	int dreamSock_Linux_GetCurrentSystemTime(void);
#else
	int dreamSock_Win_GetCurrentSystemTime(void);
#endif
	int dreamSock_GetCurrentSystemTime(void);
#endif







