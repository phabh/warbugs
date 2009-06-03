#pragma once

#include "CMenu.h"

class CMenuAbertura : public CMenu
{
	
private:

	CVideoTexture *_video;
	
	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();

public:

	CMenuAbertura();
	bool start(CGameCore *gameCore);
};

