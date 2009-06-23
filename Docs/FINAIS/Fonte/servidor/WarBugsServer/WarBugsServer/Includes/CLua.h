#pragma once

#include "Enumerators.h"

#include "CCenarioList.h"

ref class CLua
{
private:
	Moon _luaAtual;
	TipoBuff _buffAtual;
	CCenarioList *_listaCenarios;
	int _bonus1;
	int _bonus2;
	int _bonus3;

public:
	CLua(void);
	CLua(Moon lua);
	CLua(int lua);
	CLua(CCenarioList *cenarios);
	CLua(Moon lua, CCenarioList *cenarios);
	CLua(int lua, CCenarioList *cenarios);

	Moon getMoon();
	int getMoonAsInt();
	void setMoon(Moon newMoon);
	void setMoonBuff();

	bool getMoonCompatibility(CPersonagem * personagem);

	void apllyMoonBuffs();
	void changeOfMoon(Moon newMoon);
};