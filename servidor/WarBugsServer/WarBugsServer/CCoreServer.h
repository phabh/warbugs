#ifndef _CCORESERVER_H
#define _CCORESERVER_H

#include "commom.h"
#include "CDataBase.h"
#include "CDataManager.h"
//#include <CDoubleList.h>
#include <CCenario.h>
#include <CBugSocket.h>
#include <CPersonagemJogador.h>
#include <CBuff.h>
#include <CJogador.h>
#include <CPlayerList.h>

ref class CFrame
{
	public:
		bool			_toAll;
		char        *   _data;
		CBugSocket  *	_socket;
		CBugMessage *	_message;
		int             _idCenario;

		CFrame()
		{
			_toAll	= false;
			_socket = NULL;
			_data   = new char[1400];
			_message = new CBugMessage();
			_message->init(_data,1400);
			_idCenario = -1;
		}

		CFrame(bool toAll, CBugSocket * socket, CBugMessage  & mes, int idCenario)
		{
			_toAll	= toAll;
			_socket = socket;
			_data   = new char[1400];
			_message = new CBugMessage();
			_message->init(_data,1400);
			strcpy(_message->_data,  mes._data);
			_message->setSize(mes.getSize());
			_message->beginReading();
			for(int i = 0; i < mes.getSize(); i++)
			{
				_message->readByte();
			}
			_idCenario = idCenario;
		}
};

typedef System::Collections::ArrayList CBufferFrame;



ref class CCoreServer
{
				CCenarioList	* _cenarioList;
				CBugSocketServer* _networkServer;
				CDataBase       * _db;
				CDataManager    * _dataManager;
				CPlayerList     * _playersList;

				int               _fps;
//				CTimer            _time;

				bool              _serverStarted;
				
	public:
						CCoreServer(CDataBase * db, int fps);	//Construtor

		void			initialize();					//inicializará todo o server

		void			initializeNetwork();			//inicializará a parte de conexão do servidor

		void			readPackets();

		CPlayerList   * getPlayers();

		static CBufferFrame ^ _buffer;

	//	void            addPlayer(CJogador * jogador);
	//	void			removePlayer(int idJogador);
	//	void			removePlayers();

		//mensagens para enviar para o cliente
		/*
			funcoes para enviar mensagem para o cliente
			@param toAll -> True envia para todas as pessoas do cenário passado
			@param idCenario -> -1 para nenhum cenário, 0 acima para o cenário que será enviado
			@param destino -> caso seja para um jogador apenas
			@param mes -> messagem a ser enviada
		*/
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, CBugMessage & mes);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, float f1, float f2);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino,  int idMensagem, TypeClassChars tipoPersonagem, CPersonagem  * p1);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, CPeopleList * p1);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, float f1, float f2);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, char * mensagem);
		static void		sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int v1[30], int v2[30]);
		static void		sendMessagesFrame(CPlayerList * cList);
};
#endif


