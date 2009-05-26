#pragma once

#include "GameSetup.h"
#include "PathSetup.h"

#include "CDoubleList.h"

#include "NetworkSetup.h"
#include "CBugSocket.h"

#include "CArquivoConfig.cpp"
#include "CArquivoMatrizes.cpp"

#include "CGerEventos.h"
#include "CGameData.h"
#include "CGameLogic.h"

#include "CToonShader.h"

struct SPersonagemSelecao
{
	int _id;
	char *_nome;
	int _nivel;

	int _agilidade;
	int _destreza;
	int _forca;
	int _instinto;
	int _resistencia;

	int _taxaAtaque;
	int _tempoCarga;
	int _defesa;
	int _ataqueCorporal;
	int _danoCorporal;
	int _raioAtaque;
	int _raioDano;

	int _idModelo;
	int _idTextura;
	int _idHud;
};

class CGameCore
{

private:

	IrrlichtDevice  *_dispositivoGrafico; 
	ISoundEngine    *_dispositivoAudio;

	IVideoDriver    *_gerenciadorVideo; 
	ISceneManager   *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;
	CGerEventos     _gerenciadorEventos;

	ICameraSceneNode *_gameCamera;

	typedef CDoubleList<IParticleSystemSceneNode> CListaParticulas;
	CListaParticulas  *_listaParticulas;

	//IParticleSystemSceneNode *_particleSystem[5000];

	IGUISkin *_gameSkin;
	IGUIFont *_gameFont[NUMHUDFONTS];

	ISound* _gameMusic;
	ISound* _hudFX[NUMSFXHUD];

	CBugSocketClient *_gameSocket;

	CBugMessage _packageToSend,    // Pacote a enviar
		_packageReceived; // Pacote a receber

	char _dataToSend[PACKAGESIZE],
		_dataReceived[PACKAGESIZE];

	CArquivoConfig *_fileCfg;
	TypeCfg _gameConfig;

	CGameData *_Data;
	CGameLogic *_Logic;

	char _myLogin[15],
		_myPassword[15];



	bool _connected; // Identifica se o cliente está conectado ao servidor

	int _particleCount;

public:

	int _nSlotChars;
	int _meuLoginID;

	SPersonagemSelecao _vectPersonagem[MAXSLOTPERSONAGEM];
	IAnimatedMeshSceneNode *_personagem[MAXSLOTPERSONAGEM];

	CGameCore(int &startInit);

	void drop();

	void loadGameData();

	IrrlichtDevice * getGraphicDevice();
	ISoundEngine * getSoundDevice();
	CGerEventos * getEventManager();

	void getAllManagers(IrrlichtDevice*&dispGrafico, ISoundEngine*&dispAudio, CGerEventos*&gerEventos, ISceneManager*&gerCena, IVideoDriver*&gerVideo, IGUIEnvironment*&gerHud, TypeCfg &gameCfg); 

	void playMusic( char* soundFile, bool looped = true, bool startPaused = false, bool track = false, E_STREAM_MODE modo = ESM_AUTO_DETECT, bool efeitos = false);

	IParticleSystemSceneNode* addPaticleNode(TypeParticle tipo, int tempoVida, vector3df posicao, vector3df escala);
	
	void loadMenuScene(c8 *sceneFile);
	int getNSlotChars();

	void loadGameScene(c8 *sceneFile);

	ICameraSceneNode *createCamera( vector3df posicao, vector3df target = vector3df(0,0,100) , vector3df rotacao = vector3df(0,0,0), ISceneNode *parent = 0, f32 angulo = 179.0f/*bool isOrtogonal = true*/, bool bind = true);

	bool conectar(char *login, char *password);

	bool isConnected();

	void enviarPacote(int packageID);
	void enviarPacote(int packageID, int i1);
	void enviarPacote(int packageID, int i1, int i2);
	void enviarPacote(int packageID, int i1, int i2, int i3);
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4);
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6);
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9);
	void enviarPacote(int packageID, int i1, char *s1);
	void enviarPacote(int packageID, int i1, float f1, float f2);
	void enviarPacote(int packageID, int i1, int i2, int i3, float f1, float f2);
	void enviarPacote(int packageID, char *s1, char *s2);

	void receberPacote();
};