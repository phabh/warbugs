#ifndef CCENARIOSERVER_H
#define CCENARIOSERVER_H

#include "commom.h"

/**
	Classe para gerenciamento do cenário do jogo e 
	das conexões para cada cenário
*/

class CCenarioServer : public CWarBugObject
{

	private:
		int			  _idCenario;
		char		* _nomeCenario;

		dreamServer * _networkServer;
		CPersonagemJogador	* _playerList;
		int           _numClients;
	
		int           _map[50][50];
	
		int           _realTime;
		int           _serverTime;
		int           _frameTime;

	public:
		CCenarioServer * _next;
		CCenarioServer();

		void			sendPackets();

		void			removePlayers();
		int				getId();
		void			addPlayer(CPersonagemJogador * player);

		CPersonagemJogador	*	getPlayerList();

};

//Construtor da Classe
CCenarioServer::CCenarioServer()
{}

#endif