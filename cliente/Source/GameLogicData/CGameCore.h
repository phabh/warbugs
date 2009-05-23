#pragma once

#include "Setup.h"
#include "PathSetup.h"

#include "CDoubleList.h"

#include "NetworkSetup.h"
#include "CBugSocket.h"

#include "CArquivoConfig.cpp"
#include "CArquivoMatrizes.cpp"

#include "CGerEventos.h"
#include "CGameData.h"
#include "CGameLogic.h"

#include "CToonShader.cpp"

class CGameCore
{

private:

	IrrlichtDevice  *_dispositivoGrafico; 
	ISoundEngine    *_dispositivoAudio;

	IVideoDriver    *_gerenciadorVideo; 
	ISceneManager   *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;
	CGerEventos      _gerenciadorEventos;

	CBugSocketClient *_netClient;

	CBugMessage _msgToSend,    // Pacote a enviar
		        _msgToReceive; // Pacote a receber

	char _dataSend[PACKAGESIZE],
		 _dataReceive[PACKAGESIZE];

	CGameData *_Data;
	CGameLogic *_Logic;

public:

	CGameCore(int &startInit);

	void drop();

	void loadGameData();

	IrrlichtDevice* getGraphicDevice();
	ISoundEngine*   getSoundDevice();

	// Métodos Network
	void conectar(const std::string& host, int port);
	void enviarPacote(char *s);
	CBugMessage *receberPacote();
};