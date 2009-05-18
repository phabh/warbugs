#include "CNetwork.h"

CNetwork::CNetwork()
{
}

void CNetwork::conectar(const std::string& host, int port)
{
	gameNetClient = new CBugSocketClient(host, port);

	msgToSend.init(dataSend, PACKAGESIZE);
	msgToReceive.init(dataReceive, PACKAGESIZE);
}

void CNetwork::enviarPacote(char *s)
{
	msgToSend.writeString(s);
	gameNetClient->SendLine(msgToSend);
}

CBugMessage *CNetwork::receberPacote()
{
	return gameNetClient->ReceiveLine();
}