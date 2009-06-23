#pragma once

#include "CMenu.h"
#include "CHudRoleta.cpp"


class CMenuJogo : public CMenu
{

private:

	int _idInimigo;

	ICameraSceneNode *_menuCamera;
	
	bool _combate, _newPosition;

	TypeCfg _gameConfig;

	IGUIListBox *chatPlayers,
				*gameMessages;

	IGUIEditBox *chatInput; 

	IGUIWindow *invWindow,
			   *shopWindow,
			   *tradeWindow,
			   *statWindow,
			   *cfgWindow,
			   *mapWindow,
			   *alertWindow,
			   *bagWindow;

	IGUIButton *slotInv[11], *invBtn[3], // Inventário
			   *slotInvBag[11], *slotBag[9], *bagBtn[3], // Bolsa do cenário
			   *slotInvShop[11], *slotShop[9], *shopBtn[7], // Shop
			   *slotInvTrade[11], *slotTrade[2], *tradeBtn[5], // Trade
			   *hudBtn[11];

	IGUIStaticText *cashInv,
				   *cashInvBag,
				   *cashInvShop, *cashToSell, *cashToBuy,
				   *cashTradeSend, *cashTradeRecv,
				   *cfgCaption[2];
		
	IGUIImage *meOnMap, *imgMoon, *bgMoon, *statusBg, *statusFace;

	IGUIScrollBar *cfgVolume;

	IGUICheckBox *cfgContorno;

	CHudProgressBar *barPV,
					*barPP,
					*barXP,
					*barMP;
		

	CHudRoleta *_roleta;

	float rotV, 
		rotH;

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