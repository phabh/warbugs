#pragma once

#include "GameSetup.h"
#include "CGameCore.h"

class CMenu
{

protected:

	CGameCore *_gameCore;

	IrrlichtDevice  *_dispGrafico; 
	ISoundEngine    *_dispAudio;
	IVideoDriver    *_gerVideo; 
	ISceneManager   *_gerCena; 
	IGUIEnvironment *_gerHud;
	CGerEventos     *_gerEventos;

	TypeCfg _gameConfig;

	bool _menuFlag[NUMFLAGSMENU];
	

	//IGUISkin *_skin;
	//IGUIFont *_font[NUMHUDFONTS];

	//ISceneNode *_nodoSelecionado;

	//ICameraSceneNode *_camera;

	TypeMenuID _myID, _nextID;

	//ISound* _musica;
	//ISound* _hudFX[NUMFXHUD];

	

	//char *_arquivoCena;
	
	//bool _temPacote;

	//CGameData *_gameData;

	//CToonShader *_toonShader;

	virtual void updateHuds() = 0;
	virtual void readCommands() = 0;
	virtual void updateGraphics() = 0;
	virtual void graphicsDrawAddOn() = 0;

public:

	CMenu(){}
	bool start(CGameCore *gameCore);
	TypeMenuID run();
};
