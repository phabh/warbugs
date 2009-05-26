#pragma once

#include "CMenu.h"

class CMenuSelecao : public CMenu
{

private:

	int _idPersonagem;
	ISceneNode *_nodoSelecionado;

	float _camRotation;
	float _camCurrRotation;

	ICameraSceneNode *_menuCamera;

	CToonShader *_toonShader;

	int _nSlotChars;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuSelecao();
	bool start(CGameCore *gameCore);
};