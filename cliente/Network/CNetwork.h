#pragma once

#include "Setup.h"
#include "CBugSocket.h"

class CNetwork
{

private:

	CBugSocketClient *gameNetClient;
	
	CBugMessage msgToSend, msgToReceive;	
	
	char dataSend[PACKAGESIZE],
		 dataReceive[PACKAGESIZE];

public:

	CNetwork();
	void conectar(const std::string& host, int port);
	void enviarPacote(char *s);
	CBugMessage *receberPacote();
};