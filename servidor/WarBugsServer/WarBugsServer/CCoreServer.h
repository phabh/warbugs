#ifndef _CCORESERVER_H
#define _CCORESERVER_H

#include "commom.h"
#include "CDataBase.h"
#include "CDataManager.h"
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
			memcpy(_message->_data,  mes._data, mes.getSize());
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

				int               _lastTimeSaveAll;
				int               _intervalTimeSaveAll;

				int               _lastTimeSaveMarket;
				int               _intervalTimeSaveMarket;

				int               _intervalTimePing;
				int               _beginTimePing;
				int               _toleranceMaxPing;

				bool              _serverStarted;
				
	public:
						CCoreServer(CDataBase * db);	//Construtor

		void			initialize();					//inicializar� todo o server

		void			initializeNetwork();			//inicializar� a parte de conex�o do servidor

		void			readPackets();

		CPlayerList   * getPlayers();

		static CBufferFrame ^ _buffer;

		void            updateAll();

		void			sendAllMessages();

		void			setIntervalTimeSaveAll(int timeInHour);
		void			setIntervalTimeSaveMarket(int timeInMinutes);
		void			setIntervalTimePing(int timeInSeconds);
		void            setBeginTimePing(int timeInSeconds);
		void			setToleranceMaxPing(int timeInSeconds);
		void			setFPS(int fps);

		int				getIntervalTimeSaveAll();
		int				getLastTimeSaveAll();
		int				getIntervalTimeSaveMarket();
		int				getLastTimeSaveMarket();
		int				getIntervalTimePing();
		int				getBeginTimePing();
		int				getToleranceMaxPing();
		int				getFPS();

		void            backupAll();

		//mensagens para enviar para o cliente
		/*
			funcoes para enviar mensagem para o cliente
			@param toAll -> True envia para todas as pessoas do cen�rio passado
			@param idCenario -> -1 para nenhum cen�rio, 0 acima para o cen�rio que ser� enviado
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
		static void     sendMessage(bool toAll, int idCenario, CBugSocket * destino, int idMensagem, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11, int i12, int i13, int i14, int i15, int i16, int i17);
		static void		sendMessagesFrame(CPlayerList * cList);
};
#endif


