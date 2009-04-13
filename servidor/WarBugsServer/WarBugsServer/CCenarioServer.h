#ifndef CCENARIOSERVER_H
#define CCENARIOSERVER_H

#include "commom.h"

/**
	Classe para gerenciamento do cenário do jogo e 
	das conexões para cada cenário
*/


class CCenarioServer : CObject
{

	private:
		int			  _idCenario;
		char		* _nomeCenario;

		dreamServer * _networkServer;
		CDataPlayer * _playerList;
		int           _numClients;
	
		int           _map[][];
	
		int           _realTime;
		int           _serverTime;
		int           _frameTime;

	public:
		CCenarioServer();

		void			initializeNetwork();
		void			readPackets();
		void			sendPackets();

		void			removePlayers();

		CDataPlayer *	searchPlayer(sockaddr * player);


		//tratamento das mensagens
		void            messageToPlayer(CDataPlayer * player, dreamMessage * message);
		void			messageToAll(CDataPlayer * player, dreamMessage * message);
		void			enterCenario(CDataPlayer * player, dreamMessage * message);
		void            exitCenario(CDataPlayer * player, dreamMessage * message);
		void			selectTarget(CDataPlayer * player, dreamMessage * message);
		void			deselectTarget(CDataPlayer * player, dreamMessage * message);
		void			doAtack(CDataPlayer * player, dreamMessage * message);
		void			doPower(CDataPlayer * player, dreamMessage * message);
		void			equipItem(CDataPlayer * player, dreamMessage * message);
		void            useItem(CDataPlayer * player, dreamMessage * message);
		void            tradeRequest(CDataPlayer * player, dreamMessage * message);
		void            doTradeItem(CDataPlayer * player, dreamMessage * message);
		void            pickItem(CDataPlayer * player, dreamMessage * message);
		void            exitCenario(CDataPlayer * player, dreamMessage * message);
		
		CDataPlayer	*	getPlayerList();

};

//Construtor da Classe
CCenarioServer::CCenarioServer()
{};

//Inicialização da espera por clients
void CCenarioServer::initializeNetwork()
{
	if(dreamSock_Initialize() != 0)
		return;


	int ret = -1;
	if(_networkServer)
		ret = _networkServer->initialize("",PORT);

	if(ret == DREAMSOCK_SERVER_ERROR)
		return;

}

//Recebimento dos pacotes enviados pelos clientes
void CCenarioServer::readPackets()
{
	//1400 é um valor aleatorio, vai ser definido ainda
	char data[1400];

	int ret;         //tamanho da mensagem
	int typeMessage; //tipo de mensagem

	//endereço do cliente que enviou o pacote
	struct sockaddr endPlayer;


	//apontador para a lista de clientes do cenário
	CDataPlayer * tempPlayer;

	dreamMessage mes;
	mes.init(data, sizeof(data));

	try
	{
		while(ret = _networkServer->getPacket(mes._data,&endPlayer))
		{
			mes.setSize(ret);
			mes.beginReading();

			typeMessage = mes.readByte();

			tempPlayer = searchPlayer(&endPlayer);

			switch(typeMessage)
			{

				case ENTER_CENARIO:		enterCenario(tempPlayer,&mes);		break; //envie uma requisição apra entrar neste cenário
				case MESSAGE_TO_PLAYER:	messageToPlayer(tempPlayer,&mes);	break; //personagem envie uma mensagem para um outro jogador privado
				case MESSAGE_TOALL:		messageToAll(tempPlayer,&mes);		break; //personagem envie uma mensagem sem destinatario
				case SELECT_TARGET:		selectTarget(tempPlayer,&mes);		break; //selecionei um personagem(alvo)
				case DESELECT_TARGET:	deselectTarget(tempPlayer,&mes);	break; //tirei a selecao do personagem(alvo)
				case DO_ATACK:			doAtack(tempPlayer,&mes);			break; //ataquei
				case DO_POWER:			doPower(tempPlayer,&mes);			break; //usei poder
				case EQUIP_ITEM:		equipItem(tempPlayer,&mes);			break; //equipei Item
				case USE_ITEM:			useItem(tempPlayer,&mes);			break; //usei Item
				case TRADE_REQUEST:		tradeRequest(tempPlayer,&mes);		break; //quero trocar item
				case DO_TRADE_ITEM:		doTradeItem(tempPlayer,&mes);		break; //confirmei a troca
				case PICK_ITEM:			pickItem(tempPlayer,&mes);			break; //peguei um item que estava no cenário
				case EXIT_CENARIO:		exitCenario(tempPlayer,&mes);		break; //sai do cenário

			}//fim switch

		}//fim while
	}
	catch()
	{}


}


/*
	metodo para achar o player desejado pelo seu endereço de rede
	@param  player - estrutura de endereço de socket de quem enviou
	@return - os dados do player
*/
CDataPlayer *	CCenarioServer::searchPlayer(sockaddr * player)
{
	
	CDataPlayer * tempList;

	tempList = _playerList;


	for(; tempList != NULL; tempList = tempList->next)
	{
		if(memcmp(tempList->_netPlayer->getSocketAddress(), player, sizeof(* player)) == 0)
			break;//achei	
	}

	return tempList;
}


/*
	metodo para tratar o personagem que entra no cenário vindo do login ou de outro cenário
	@param  player - estrutura de endereço de socket de quem enviou
	@param  message - a mensagem que foi enviada
*/
void CCenarioServer::enterCenario(CDataPlayer * player, dreamMessage * message)
{
	


}



#endif