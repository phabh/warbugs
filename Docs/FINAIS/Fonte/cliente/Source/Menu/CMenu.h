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

	void addNewBtn( IGUIButton *&ptrBtn, rect<s32> posicao, IGUIElement *parent, s32 id=-1, const wchar_t *texto=0, const wchar_t *dica=0, bool isTexturedBtn=false, bool isPushBtn=false, int idImageUp=-1, int idImagePressed=-1);
	void addNewText( IGUIStaticText *&ptrTexto, const wchar_t *texto, rect<s32> posicao, bool hasBorder=false, bool isWrap=false, bool fillBg=false, IGUIElement *parent=0, s32 id=-1, EGUI_ALIGNMENT horizontal = EGUIA_LOWERRIGHT , EGUI_ALIGNMENT vertical = EGUIA_CENTER);
	void addNewWindow( IGUIWindow *&ptrWindow, rect<s32> posicao, bool modal=false, const wchar_t *titulo=0, IGUIElement *parent=0, int id=-1);

};
