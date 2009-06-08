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
//#include "CGameScene.h"

#include "CPersonagem.h"

#include "CToonShader.h"

#include "CVideoTexture.h"

#include "CHudSkin.h"





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

	typedef CDoubleList<CPersonagem> ListaPersonagem;
	typedef CDoubleList<SBolsa> ListaBolsa;

	IrrlichtDevice  *_dispositivoGrafico; 
	ISoundEngine    *_dispositivoAudio;

	IVideoDriver    *_gerenciadorVideo; 
	ISceneManager   *_gerenciadorCena; 
	IGUIEnvironment *_gerenciadorHud;
	CGerEventos     _gerenciadorEventos;



	typedef CDoubleList<IParticleSystemSceneNode> CListaParticulas;
	CListaParticulas  *_listaParticulas;

	CHudImageSkin* _gameSkin;

	IGUIFont *_gameFont[NUMHUDFONTS];

	ISound* _gameMusic;
	ISound* _hudFX[NUMSFXHUD];

	CBugSocketClient *_gameSocket;

	CBugMessage _packageToSend,    // Pacote a enviar
		_packageReceived; // Pacote a receber

	char _dataToSend[PACKAGESIZE],
		_dataReceived[PACKAGESIZE];

	//! Objeto para carregar as matrizes de colisão do cenário
	CArquivoMatrizes *_fileMtx;

	//! Objeto para carregar as configurações do jogo
	CArquivoConfig *_fileCfg;
	
	TypeCfg _gameConfig;

	char _myLogin[15],
		_myPassword[15];

	bool _connected; // Identifica se o cliente está conectado ao servidor

	int _particleCount;

	ILightSceneNode *_luz;

	CToonShader *_toonShader; // Classe de ToonShader

	CVideoTexture *_cutScene[CS_COUNT];

	//! Matriz de colisões do cenário atual
	SMatrix _cenario; 

	//! Lista de personagens do cenário
	ListaPersonagem  *_listaPersonagens;

	
	
	//! Lista de bolsas do cenário
	ListaBolsa *_listaBolsas;


	//! Identificação da lua corrente
	int _sceneMoon;

	//! Lista de portais para troca de cenário
	SQuadrante _portal[MAXPORTAIS];

	ITerrainSceneNode *_sceneTerrain;
	ITriangleSelector* _sceneTris;

public:

	

	ICameraSceneNode *_gameCamera;

	ISceneNode *_emptyCam; // nodo vazio para camera

	float camRotVert, camRotHor; // rotações do empty da camera

	int sWidth, sHeight;

	CHudProgressBar* _barraLoad;

	CGameData *_gameData;
	//CGameScene *_gameScene;

	int _numMyChars;
	int _myUserID;
	int _myCharID;
	int _myCharSceneID;
	int _myMapSceneID;

	//! Ponteiro para o meu personagem
	CPersonagem *_myPlayerChar;
	
	SPersonagemSelecao _myStructChar[MAXSLOTPERSONAGEM];
	IAnimatedMeshSceneNode *_myChar[MAXSLOTPERSONAGEM];

	IAnimatedMesh* getMAnimMesh(int idMesh);
	ITexture* getMTexture(int idTexture);

	CGameCore(int &startInit);
	void drop();
	void loadGameData();
	void loadGameData(int stage);
	IrrlichtDevice * getGraphicDevice();
	ISoundEngine * getSoundDevice();
	CGerEventos * getEventManager();
	void initToonShader();
	void loadSkin(int idSkin);
	void getAllManagers(IrrlichtDevice*&dispGrafico, ISoundEngine*&dispAudio, CGerEventos*&gerEventos, ISceneManager*&gerCena, IVideoDriver*&gerVideo, IGUIEnvironment*&gerHud, TypeCfg &gameCfg); 
	void playMusic( char* soundFile, bool looped = true, bool startPaused = false, bool track = false, E_STREAM_MODE modo = ESM_AUTO_DETECT, bool efeitos = false);
	bool playCutScene( int idCutScene, int volume);
	IParticleSystemSceneNode* addPaticleNode(TypeParticle tipo, int tempoVida, vector3df posicao, vector3df escala);
	void loadMenuScene(c8 *sceneFile);
	int getNumCharSlots();

	void loadGameScene(c8 *sceneFile);
/*
	void setMyMapSceneID(int idMapa);
	void setMyCharSceneID(int idChar);
	void setSceneQuadPortalID(int idQuadPortal1, int idQuadPortal2, int idQuadPortal3, int idQuadPortal4);
*/

	//! Calcula a rotação resultante entre três eixos (X,Y,Z).
	vector3df rotacaoResultante(f32 rotX, f32 rotY, f32 rotZ);

	ICameraSceneNode *createCamera( vector3df posicao, vector3df target = vector3df(0,0,100) , vector3df rotacao = vector3df(0,0,0), ISceneNode *parent = 0, f32 angulo = 179.0f/*bool isOrtogonal = true*/, bool bind = true);
	void createLight(ISceneNode *parent, vector3df posicao, f32 raio);

	void addContour(ISceneNode* oNode, f32 fThickness = 3, SColor cColor = SColor(255,0,0,0));
	void contourAll(ISceneNode* node);


	//! Carrega a matriz de colisão do cenário atual
	SMatrix loadSceneMatrix(int idScene);

	//! Inclui uma bolsa no cenário
	void addBolsa(int idBolsa, float posX, float posZ);

	//! Remove uma bolsa do cenário
	void removeBolsa(int idBolsa);

	//! Inclui um personagem no cenário
	void addPersonagem(CPersonagem *personagem);

	//! Remove um personagem do cenário
	void removePersonagem(int idPersonagem);

	//! Atualiza a posição de um personagem
	void updCharPosition(int idPersonagem, float posX, float posZ);

	//! Atualiza o estado de animação de um personagem
	void updCharState(int idPersonagem, int estado);

	//! Atualiza o alvo de um personagem
	void updCharTarget(int idPersonagem, float posX, float posZ);

	//! Atualiza os itens equipados por um personagem
	void updCharEquipment(int idPersonagem, int idArmadura, int idArma);

	//! Atualiza a direção e a velocidade de um personagem
	void updCharDirectionVelocity(int idPersonagem, int direction, int velocity);

	//! Atualiza os buffs de um personagem
	void updCharBuff(int idPersonagem, short buffs);

	//! Atualiza os ids dos quadrantes dos portais no cenário
	void updMapPortals(int idQuadPortal1, int idQuadPortal2, int idQuadPortal3, int idQuadPortal4);

	//! Atualiza a lua corrente do cenário
	void updMoon(int idLua);

	//! Retorna a coordenada3D do centro de um quadrante
	vector3df getQuadCenter(int linha, int coluna);

	//! Retorna a coordenada3D do centro de um quadrante
	vector3df getQuadCenter(int idQuad);

	//! Retorna a coordenada3D do centro de um quadrante
	vector3df getQuadCenter(vector3df posicao);

	//! Retorna por parâmetros a linha e a coluna de uma posicao
	void getQuadLinhaColuna(vector3df posicao, int &linha, int &coluna);

	//! Retorna por parâmetros a linha e a coluna de um determinado quadrante
	void getQuadLinhaColuna(int idQuad, int &linha, int &coluna);

	//! Retorna o id do quadrante referente a uma posição
	int getQuadID(vector3df posicao);

	//! Retorna o id do quadrante referente a linha e coluna
	int getQuadID(int linha, int coluna);

	//! Atualiza a posição 3D de um elemento do cenário
	vector3df upd3DPosition(float posX, float posZ);



	bool conectar(char *login, char *password);
	bool isConnected();
	void enviarPacote(int packageID);
	void enviarPacote(int packageID, int i1);
	void enviarPacote(int packageID, int i1, int i2);
	void enviarPacote(int packageID, int i1, int i2, int i3);
	void enviarPacote(int packageID, int i1, int i2, char *s1 );
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4);
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6);
	void enviarPacote(int packageID, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9);
	void enviarPacote(int packageID, int i1, char *s1);
	void enviarPacote(int packageID, int i1, float f1, float f2);
	void enviarPacote(int packageID, int i1, int i2, int i3, float f1, float f2);
	void enviarPacote(int packageID, char *s1, char *s2);
	int receberPacote();
};