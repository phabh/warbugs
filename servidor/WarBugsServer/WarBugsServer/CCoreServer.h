#ifndef _CCORESERVER_H
#define _CCORESERVER_H

#include "commom.h"
#include <CCenario.h>
#include <dreamServer.h>
#include "CDataBase.h"
#include <CPersonagemJogador.h>
#include <CJogador.h>
#include "CDataManager.h"

class CCoreServer
{
				CCenario		* _cenarioList;
				dreamServer     * _networkServer;
				CDataBase       * _db;
				CDataManager    * _dataManager;
				
				CPersonagemJogador * _limbo;
				CJogador        * _playersList;

				int               _fps;
//				CTimer            _time;

				bool              _serverStarted;
				
	public:
						CCoreServer(CDataBase * db, int fps);	//Construtor

		void			initialize();					//inicializará todo o server

		void			initializeNetwork();			//inicializará a parte de conexão do servidor

		void			readPackets();

		void            addPlayer(CJogador * jogador);
		void			removePlayer(int idJogador);
		void			removePlayers();

		//mensagens para enviar para o cliente
		void			sendMessage(bool toAll, sockaddr * destino, dreamMessage * mes);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, float f1, float f2);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, CPersonagem * p1);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, float f1, float f2);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, char * mensagem);
		void			sendMessage(bool toAll, sockaddr * destino, int idMensagem, int v1[30], int v2[30]);
};
#endif


