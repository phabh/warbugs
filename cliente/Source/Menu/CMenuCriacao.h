#pragma once

#include "CMenu.h"

class CMenuCriacao : public CMenu
{

private:

	ICameraSceneNode *_menuCamera;

	IParticleSystemSceneNode *_particula[RACASMAX];
	ILightSceneNode *_luz;
	CToonShader *_toonShader;

	int _idChar;
	int _tipoPersonagem;
	ISceneNode *_nodeChar;
	float _camRotation;
	float _camCurrRotation;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();
	void receivePackages();

public:

	CMenuCriacao();
	bool start(CGameCore *gameCore);
};