#pragma once

#include "dreamSock.h"
#include "dreamClient.h"
#include "dreamMessage.h"

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