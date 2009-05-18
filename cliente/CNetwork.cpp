#include "CNetwork.h"

CNetwork::CNetwork()
{
}

void CNetwork::conectar(const string& host, int port)
{
	gameNetClient = new CBugSocketClient(host, port);

	msgToSend.init(dataSend, PACKAGESIZE);
	msgToReceive.init(dataReceive, PACKAGESIZE);
}

void CNetwork::enviarPacote(char *string)
{
	msgToSend.writeString(string);
	gameNetClient->SendLine(msgToSend);
}

CBugMessage *CNetwork::receberPacote()
{
	return gameNetClient->ReceiveLine();
}