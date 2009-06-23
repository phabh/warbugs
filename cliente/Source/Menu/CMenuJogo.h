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

	void addNewBtn( IGUIButton *&ptrBtn, rect<s32> posicao, IGUIElement *parent, s32 id=-1, const wchar_t *texto=0, const wchar_t *dica=0, bool isTexturedBtn=false, bool isPushBtn=false, int idImageUp=-1, int idImagePressed=-1);
	void addNewText( IGUIStaticText *&ptrTexto, const wchar_t *texto, rect<s32> posicao, bool hasBorder=false, bool isWrap=false, bool fillBg=false, IGUIElement *parent=0, s32 id=-1, EGUI_ALIGNMENT horizontal = EGUIA_LOWERRIGHT , EGUI_ALIGNMENT vertical = EGUIA_CENTER);
	void addNewWindow( IGUIWindow *&ptrWindow, rect<s32> posicao, bool modal=false, const wchar_t *titulo=0, IGUIElement *parent=0, int id=-1);
	
};