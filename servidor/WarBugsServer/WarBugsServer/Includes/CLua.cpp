
#include "CLua.h"

CLua::CLua(void)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = MOON_OBLIVION;
	_buffAtual = BUFF_NORMAL;
	_listaCenarios = new CCenarioList();
}
CLua::CLua(Moon lua)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = lua;
	setMoonBuff();
	_listaCenarios = new CCenarioList();
}
CLua::CLua(int lua)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = (Moon)lua;
	setMoonBuff();
	_listaCenarios = new CCenarioList();
}
CLua::CLua(CCenarioList *cenarios)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = MOON_OBLIVION;
	_buffAtual = BUFF_NORMAL;
	_listaCenarios = cenarios;
}
CLua::CLua(Moon lua, CCenarioList *cenarios)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = lua;
	setMoonBuff();
	_listaCenarios = cenarios;
}
CLua::CLua(int lua, CCenarioList *cenarios)
{
	_bonus1 = 0;
	_bonus2 = 0;
	_bonus3 = 0;
	_luaAtual = (Moon)lua;
	setMoonBuff();
	_listaCenarios = cenarios;
}
Moon CLua::getMoon()
{
	return(_luaAtual);
}
int CLua::getMoonAsInt()
{
	return((int)_luaAtual);
}
void CLua::setMoon(Moon newMoon)
{
	_luaAtual = newMoon;
}
void CLua::setMoonBuff()
{
	switch(_luaAtual)
	{
	case MOON_ABGRUNDI:
		_buffAtual = BUFF_MOON_ABGRUNDI;
		_bonus1 = 7;
		_bonus2 = 0;
		_bonus3 = 0;
		break;
	case MOON_MABILOG:
		_buffAtual = BUFF_MOON_MABILOG;
		_bonus1 = 20;
		_bonus2 = 10;
		_bonus3 = 0;
		break;
	case MOON_OBLIVION:
		_buffAtual = BUFF_NORMAL;
		_bonus1 = 0;
		_bonus2 = 0;
		_bonus3 = 0;
		break;
	case MOON_RESPLANDORA:
		_buffAtual = BUFF_MOON_RESPLANDORA;
		_bonus1 = 7;
		_bonus2 = 5;
		_bonus3 = 0;
		break;
	case MOON_SAMARA:
		_buffAtual = BUFF_MOON_SAMARA;
		_bonus1 = 50;
		_bonus2 = -10;
		_bonus3 = 5;
		break;
	case MOON_TYPHOONA:
		_buffAtual = BUFF_MOON_TYPHOONA;
		_bonus1 = 10;
		_bonus2 = 3;
		_bonus3 = 0;
		break;
	}
}
bool CLua::getMoonCompatibility(CPersonagem * personagem)
{
	if(((personagem->getRace() == ARANHA) && (_luaAtual == MOON_TYPHOONA))||((personagem->getRace() == BESOURO) && (_luaAtual == MOON_MABILOG))||((personagem->getRace() == ESCORPIAO) && (_luaAtual == MOON_ABGRUNDI))||((personagem->getRace() == LOUVADEUS) && (_luaAtual == MOON_RESPLANDORA))||((personagem->getRace() == VESPA) && (_luaAtual == MOON_SAMARA)))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
void CLua::apllyMoonBuffs()
{
	CCenario *temp;
	CBuff *tempBuff;
	for(int i = 0; i < _listaCenarios->size(); i = i + 1)
	{
		temp = _listaCenarios->getElementAt(i);
		for(int j = 0; i < max( max(temp->getPlayerList()->size(),temp->getSalesmanList()->size()),max(temp->getMonsterList()->size(), temp->getNPCList()->size())); i = i + 1)
		{
			if(temp->getPlayerList()->size() < i) 
			{
				temp->getPlayerList()->getElementAt(j)->getBuffs()->cleanMoonBuffs();
				if(getMoonCompatibility(temp->getPlayerList()->getElementAt(j)))
				{
					tempBuff = new CBuff(_buffAtual, -1, temp->getPlayerList()->getElementAt(j), _bonus1, _bonus2, _bonus3);
					temp->getPlayerList()->getElementAt(j)->getBuffs()->addBuff(tempBuff, temp->getPlayerList()->getElementAt(j));
				}
			}
		}
	}
}
void CLua::changeOfMoon(Moon newMoon)
{
	setMoon(newMoon);
	setMoonBuff();
	apllyMoonBuffs();
}