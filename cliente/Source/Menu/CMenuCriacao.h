#pragma once

#include "CMenu.h"

class CMenuCriacao : public CMenu
{

private:

	ICameraSceneNode *_menuCamera;
	ISceneNode *_nodoSelecionado;
	int _idPersonagem;
	IParticleSystemSceneNode *_particula[RACASMAX];
	ILightSceneNode *luz;

	CToonShader *_toonShader;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuCriacao();
	bool start(CGameCore *gameCore);
};