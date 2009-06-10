#pragma once

#include "CMenu.h"
#include "CHudChat.cpp"
#include "CHudMiniMapa.cpp"
#include "CHudRoleta.cpp"
#include "CHudStatus.cpp"

class CMenuJogo : public CMenu
{

private:

	//int _idPersonagem, 
	//	_idInimigo;

	//ITriangleSelector* _selector;

	int _idInimigo;

	ICameraSceneNode *_menuCamera;
	
	bool _combate;

	TypeCfg _gameConfig;

	IGUIListBox *_chatText;
	IGUIEditBox *_chatInput; 

	IGUIWindow *_invWindow,
		*_chatWindow,	
		*_statWindow,
		*_cfgWindow,
		*_mapWindow,
		*_equipWindow,
		*_alertWindow;

	CHudRoleta *_roleta;

	//ITerrainSceneNode *_terreno;
	//IAnimatedMesh *_malha[10];
	//ITexture *_textura[10];
	//IAnimatedMeshSceneNode *_modelo[10];

	//float _direcao, 
	//	_velocidade;

	float rotV, 
		rotH;

	//ISceneNode *_empty;
	//ILightSceneNode *_luz;


	// Variáveis para tratar o click do mouse no terreno
	SMaterial _material;
	vector3df _coordenadaCapt;
	triangle3df _trianguloCapt;
	position2di _posClick;
	line3df _raio;

	ISceneNode *_nodoSelecionado;
	vector3df _targetPosition;

	stringw temp;

	//CToonShader *_toonShader;

	void updateHuds();
	void readCommands();
	void updateGraphics();
	void graphicsDrawAddOn();
	void receivePackages();

public:

	CMenuJogo();
	bool start(CGameCore *gameCore);

	void updateScene();

	
};