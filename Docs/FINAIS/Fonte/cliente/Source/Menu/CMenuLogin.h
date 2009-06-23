#pragma once

#include "CMenu.h"

class CMenuLogin : public CMenu
{

private:

	IGUIEditBox *Login,
				*Password;

	char _login[15],
		  _senha[15];

	int _loadingStage;

	void graphicsDrawAddOn();
	void updateHuds();
	void readCommands();
	void updateGraphics();
	void receivePackages();

public:

	CMenuLogin();
	bool start(CGameCore *gameCore);
};
