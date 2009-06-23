#pragma once

#include "CMenu.h"

class CMenuSelecao : public CMenu
{

private:

	int _idChar;
	ISceneNode *_nodeChar;

	float _camRotation;
	float _camCurrRotation;

	ICameraSceneNode *_menuCamera;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();
	void receivePackages();

public:

	CMenuSelecao();
	bool start(CGameCore *gameCore);
};