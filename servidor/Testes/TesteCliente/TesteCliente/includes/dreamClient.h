#pragma once

#include "dreamSock.h"

#include "dreamMessage.h"


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