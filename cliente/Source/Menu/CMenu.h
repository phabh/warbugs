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
	
	TypeMenuID _myID, _nextID;

	virtual void updateHuds() = 0;
	virtual void readCommands() = 0;
	virtual void updateGraphics() = 0;
	virtual void graphicsDrawAddOn() = 0;
	virtual void receivePackages() = 0;
	

public:

	int maxH,
		maxW,
		minH,
		minW,
		midH,
		midW;

	CMenu(){}
	
	bool start(CGameCore *gameCore);
	TypeMenuID run();
};
