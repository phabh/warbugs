#pragma once

#include "CMenu.h"

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

class CMenuSelecao : public CMenu
{

private:

	int _idPersonagem;
	ISceneNode *_nodoSelecionado;

	float _camRotation;
	float _camCurrRotation;

	ICameraSceneNode *_menuCamera;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuSelecao();
	bool start(CGameCore *gameCore);
};