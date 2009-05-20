#pragma once

#include "Setup.h"
#include "Caminhos.h"
#include "CBugSocket.h"
#include "CDoubleList.h"

class CGameData
{

private:

	float _totalLoading; // Total de elementos a carregar na mem�ria
	float _dataLoaded; // Total de elementos carregados

	IrrlichtDevice *_dispositivo; 
	IVideoDriver *_gerenciadorVideo; 
	ISceneManager *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;

	float porcentagem;

	ITexture *dataTxScenes[NUMCENARIOS],
		*dataTxProps[NUMPROPS],
		*dataTxHuds[NUMMENUHUDS],
		*dataTxChars[NUM3DPERS],
		*dataTxItens[NUM3DITENS],
		*dataTx2DItens[NUM2DOBJS];    


	IAnimatedMesh *dataGeometryChars[NUM3DPERS],
		*dataGeometryItens[NUM3DITENS],		          
		*dataGeometryProps[NUMPROPS];

	// Atributos Network
	CBugSocketClient *gameNetClient;
	CBugMessage msgToSend, msgToReceive;	

	char dataSend[PACKAGESIZE],
		 dataReceive[PACKAGESIZE];

public:

	CGameData();

	// M�todos de dados
	void start(IrrlichtDevice *grafico);
	void loadGameData(int stage);

	// M�todos Network
	void conectar(const std::string& host, int port);
	void enviarPacote(char *s);
	CBugMessage *receberPacote();
};