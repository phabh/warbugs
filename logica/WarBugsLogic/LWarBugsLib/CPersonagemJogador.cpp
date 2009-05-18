/*
* Classe CPersonagemJogador
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem controlado por um jogador
*
*/
#ifndef _CPERSONAGEMJOGADOR_CPP_
#define _CPERSONAGEMJOGADOR_CPP_

#include "CPersonagemJogador.h"

CPersonagemJogador::CPersonagemJogador()
{
	setState(PARADO);
	setMoney(0);
	setBolsa(new CBolsa());
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuff());
	_nivel = 1;
	_experiencia = 0;
	_xpToNextLv = 0;
	_pontoDistribuir = 0;
	_lealdade = new CLealdade();
	//_party = new irr::core::array<CPersonagemJogador*>();
	//_friends = new irr::core::array<CPersonagemJogador*>();
	_jogadorID = 0;
	_alvo = NULL;
	_bareHands = true;
	_ataque = 0;
	_dano = 0;
	_range = 0;
	_speed = 0;
	bool _tradeOn = false;
	bool _tradeConfirmation = false;
	int _idTrader = -1;
	int _idItemTrade = -1;
	int _idMoneyTrade = -1;
}
//Getters e setters
char *CPersonagemJogador::getName()
{
	return(_nome);
}
int CPersonagemJogador::getLevel()
{
	return(_nivel);
}
int CPersonagemJogador::getXP()
{
	return(_experiencia);
}
int CPersonagemJogador::getMaxXP()
{
	return(_xpToNextLv);
}
int CPersonagemJogador::getAttack()
{
	if(_range <= MAXMELEERANGE)
		return(_ataque + getBonus()->getTotalBonusOf(ATTACKMELEE));
	else
		return(_ataque + getBonus()->getTotalBonusOf(ATTACKRANGED));
}
int CPersonagemJogador::getDamage()
{
	if(_range <= MAXMELEERANGE)
		return(_dano + getBonus()->getTotalBonusOf(DAMAGEMELEE));
	else
		return(_dano + getBonus()->getTotalBonusOf(DAMAGERANGED));
}
bool CPersonagemJogador::isTradeOn()
{
	return(_tradeOn);
}
bool CPersonagemJogador::isTradeConfirmated()
{
	return(_tradeConfirmation);
}
int CPersonagemJogador::getIDTrader()
{
	return(_idTrader);
}
int CPersonagemJogador::getIDItemTrade()
{
	return(_idItemTrade);
}
int CPersonagemJogador::getIDMoneyTrade()
{
	return(_idMoneyTrade);
}
//Setters
void CPersonagemJogador::setName(char *name)
{
	if(sizeof(_nome) >= strlen(name))
		strcpy_s(_nome, name);
}
void CPersonagemJogador::setRace(Raca raca)
{
	_raca = raca;
}

void CPersonagemJogador::setLevel(int level)
{
	_nivel = level;
}
void CPersonagemJogador::setXP(int xp)
{
	_experiencia = xp;
}
void CPersonagemJogador::setXPToNextLv(int xp)
{
	_xpToNextLv = xp;
}
void CPersonagemJogador::setPointsToDistribute(int points)
{
	_pontoDistribuir = points;
}
void CPersonagemJogador::setEquip(CEquipamento *equip)
{
	_equip = equip;
}
/*void CPersonagemJogador::setStatus(CBuff *status)
{
	_status = status;
}*/
void CPersonagemJogador::setLoyalty(CLealdade *lealdade)
{
	_lealdade = lealdade;
}

/*void CPersonagemJogador::setParty(irr::core::array<CPersonagemJogador*> *lista)
{
	_party = lista;
}
void CPersonagemJogador::setFriends(irr::core::array<CPersonagemJogador*> *lista)
{
	_friends = lista;
}*/
void CPersonagemJogador::setPlayer(int playerID)
{
	_jogadorID = playerID;
}
void CPersonagemJogador::setTarget(CPersonagem *alvo)
{
	_alvo = alvo;
}
void CPersonagemJogador::setBareHands(bool isBareHands)
{
	_bareHands = isBareHands;
}
void CPersonagemJogador::setAttack(int ataque)
{
	_ataque = ataque;
}
void CPersonagemJogador::setDamage(int dano)
{
	_dano = dano;
}
void CPersonagemJogador::setRange(int range)
{
	_range = range;
}
void CPersonagemJogador::setSpeed(int speed)
{
	_speed = speed;
}
void CPersonagemJogador::setTradeOn(bool value)
{
	_tradeOn = value;
}
void CPersonagemJogador::setTradeConfirmated(bool value)
{
	_tradeConfirmation = value;
}
void CPersonagemJogador::setIDTrader(int value)
{
	_idTrader = value;
}
void CPersonagemJogador::setIDItemTrade(int value)
{
	_idItemTrade = value;
}
void CPersonagemJogador::setIDMoneyTrade(int value)
{
	_idMoneyTrade = value;
}
//Outros M�todos
//Manipula��o de itens
int CPersonagemJogador::haveItem(CItem * item)
{
	return(inventario->haveItem(item->getID()));
}
void CPersonagemJogador::addItem(CItem *item)
{
	if(inventario->size() < MAXITENS)
	{
		inventario->addItem(item);
	}
}
void CPersonagemJogador::dropItem(CItem *item)
{
	if((item->isDropable())&&(inventario->removeItem(item->getID()) != NULL))
	{
		item->setEstado(NOCHAO);
		item->setPosition(this->getPosition());
	}
	else
	{
		//ERRO: O ITEM N�O EST� NO INVENTR�RIO
	}
}
void CPersonagemJogador::useItem(CItem *item)
{
	if(haveItem(item))
	{
		if(item->getTipo() == USO)
		{
			switch(item->getAtribute())
			{
			case NENHUM:
				break;
			case PV:
				habilidadesSecundarias->addPV(item->getValue());
				break;
			case PM:
				habilidadesSecundarias->addPM(item->getValue());
				break;
			default:
				break;
			}
		}
		else
		{
			//ERRO: EQUIPAMENTOS N�O PODEM SER USADOS
		}
	}
}
void CPersonagemJogador::equip(CItem *item)
{
	if(this->haveItem(item))
	{
		if(item->getTipo() == ARMA)
		{
			if(_equip->arma == NULL)
			{
				_equip->arma = (CWeapon*)item;
				item->setEstado(EQUIPADO);
				if(_equip->arma->getRange() <= MAXMELEERANGE)
				{
					_ataque = habilidadesSecundarias->getMeleeAttack();
					_dano = habilidadesSecundarias->getMeleeDamage();
				}
				else
				{
					_ataque = habilidadesSecundarias->getRangedAttack();
					_dano = habilidadesSecundarias->getRangedDamage();
				}
				_range = _equip->arma->getRange();
				_speed = _equip->arma->getSpeed();
				_bareHands = false;
			}
			else if(inventario->size() < MAXITENS)
			{
				CItem *temp = new CWeapon();
				temp = _equip->arma;
				_equip->arma = (CWeapon*)item;
				inventario->addItem(temp);
				temp = NULL;
				delete temp;
				if(_equip->arma->getRange() <= MAXMELEERANGE)
				{
					_ataque = habilidadesSecundarias->getMeleeAttack();
					_dano = habilidadesSecundarias->getMeleeDamage();
				}
				else
				{
					_ataque = habilidadesSecundarias->getRangedAttack();
					_dano = habilidadesSecundarias->getRangedDamage();
				}
				_range = _equip->arma->getRange();
				_speed = _equip->arma->getSpeed();
				_bareHands = false;
			}
			else
			{
				//ERRO: INVENT�RIO CHEIO
			}
		}
		else if(item->getTipo() == ARMADURA)
		{
			if(_equip->armadura == NULL)
			{
				_equip->armadura = (CArmor*)item;
				item->setEstado(EQUIPADO);
			}
			else if(inventario->size() < MAXITENS)
			{
				CItem *temp = new CArmor();
				temp = _equip->armadura;
				_equip->armadura = (CArmor*)item;
				inventario->addItem(temp);
				temp = NULL;
				delete temp;
			}
			else
			{
				//ERRO: INVENT�RIO CHEIO
			}
		}
		else
		{
			//ERRO: O ITEM N�O � UMA ARMA/ARMADURA
		}
	}
	else
	{
		//ERRO: O ITEM N�O EST� NO INVENTR�RIO
	}
}
void CPersonagemJogador::unequip(CItem *item)
{
	if(_equip->arma == item)
	{
		_equip->arma = NULL;
		item->setEstado(NAMOCHILA);
		_ataque = habilidadesPrimarias->getFOR();
		_dano = habilidadesPrimarias->getFOR();
		_range = MAXMELEERANGE;
		_speed = habilidadesPrimarias->getAGI();
		_bareHands = true;
	}
	else if(_equip->armadura == item)
	{
		_equip->arma = NULL;
		item->setEstado(NAMOCHILA);
	}
	else
	{
		//ERRO: O ITEM ESPECIFICADO N�O EST� EQUIPADO
	}
}
//Friends Manipulation
/*int CPersonagemJogador::isFriend(CPersonagemJogador *jogador)
{
	return(_friends->binary_search_const(jogador));
}
void CPersonagemJogador::addFriend(CPersonagemJogador *newFriend)
{
	if(_friends->size() < MAXFRIENDS)
	{
		_friends->push_back(newFriend);
		_friends->sort();
	}
	else return; // ERRO: N�MERO M�XIMO DE AMIGOS PERMITIDOS ATINGIDO
}
void CPersonagemJogador::removeFriend(CPersonagemJogador *jogador)
{
	irr::s32 i = this->isFriend(jogador);
	if(i >=	 0)
	{
		_friends->erase(i);
	}
	else
	{
		//ERRO: O AMIGO N�O CONSTA NA LISTA
	}
	return;
}
//Party Manipulation
bool CPersonagemJogador::isPartyLeader()
{
	return((!_party->empty())&&(_party->getLast() == this));
}
int CPersonagemJogador::isPartyMember(CPersonagemJogador* jogador)
{
	return(_party->binary_search_const(jogador));
}
void CPersonagemJogador::addPartyMember (CPersonagemJogador *jogador)
{
	if((this->isPartyLeader()) && (!this->isPartyMember(jogador)))
	{
		_party->push_front(jogador);
		_party->sort();
	}
	else
	{
		//ERRO: N�O � L�DER DO GRUPO
	}
}
void CPersonagemJogador::removePartyMember(CPersonagemJogador *jogador)
{
	if((_party->empty()) && ((this->isPartyMember(jogador))>=0))
	{
		_party->erase(this->isPartyMember(jogador));
	}
	else
	{
		//ERRO: O JOGADOR N�O PERTENCE AO GRUPO
	}
	return;
}
void CPersonagemJogador::givePartyAlliesID(irr::core::array<CPersonagemJogador*> *lista)
{
	lista = _party;
}
void CPersonagemJogador::updateAlliesID()
{
}
void CPersonagemJogador::createParty()
{
	if(_party->empty())
	{
		_party->push_back(this);
	}
	else
	{
		//ERRO: J� FAZ PARTE DE UMA PARTY
	}
}
void CPersonagemJogador::joinParty(CPersonagemJogador *lider)
{
	if(_party->empty())
	{
		lider->addPartyMember(this);
		lider->givePartyAlliesID(_party);
	}
	else
	{
		//ERRO: J� FAZ PARTE DE UMA PARTY
	}
}
void CPersonagemJogador::leaveParty(CPersonagemJogador *lider)
{
	if(!(_party->empty()))
	{
		lider->removePartyMember(this);
		_party->clear();
	}
}*/
//Quest
void CPersonagemJogador::acceptQuest(CQuest *quest){}
//Speaking
void CPersonagemJogador::speakToPlayer(CPersonagemJogador *alvo){}
void CPersonagemJogador::speakToNPC(CPersonagem *alvo){}
//Batalha
void CPersonagemJogador::takeDamage(int damage)
{
	habilidadesSecundarias->addPV(habilidadesSecundarias->getPV() - damage);
}
void CPersonagemJogador::attack()
{
	int testValue = 0;
	if((this->getDistanceToPoint(_alvo->getPosition()) <= _range))
	{
		if(_bareHands)
		{
			testValue = _ataque + ((rand()%_equip->arma->getMaxDamage())+_equip->arma->getMinDamage())/2;
		}
		else
		{
			testValue = _ataque;
		}

		if(testValue > _alvo->getStats()->getDefense())
		{
			if(_bareHands)
			{
				testValue = _dano + ((rand()%_equip->arma->getMaxDamage())+_equip->arma->getMinDamage());
			}
			else
			{
				testValue = _dano;
			}
			_alvo->takeDamage(testValue);
		}
	}
}
//Level Up
void CPersonagemJogador::updateXP(){/*Acessa banco de dados pra atualizar _xpToNextLv _xpToPrevLv*/}
bool CPersonagemJogador::haveLevelUp()
{
	if(_experiencia >= _xpToNextLv)
	{
		_pontoDistribuir = _pontoDistribuir + 5;
		_nivel = _nivel + 1;
		updateXP();
		return(true);
	}
	else return(false);
}
bool CPersonagemJogador::haveLevelDown()
{
	if(_experiencia < 0)
	{
		_nivel = _nivel - 1;
		 _pontoDistribuir = _pontoDistribuir - 5;
		updateXP();
		return(true);
	}
	else return(false);
}
void CPersonagemJogador::distibutePoints(int points, int atribute)
{
	if(points <= _pontoDistribuir)
	{
		switch(atribute)
		{
		case 0:
			habilidadesPrimarias->addFOR(points);
			_pontoDistribuir = _pontoDistribuir - points;
			break;
		case 1:
			habilidadesPrimarias->addDES(points);
			_pontoDistribuir = _pontoDistribuir - points;
			break;
		case 2:
			habilidadesPrimarias->addAGI(points);
			_pontoDistribuir = _pontoDistribuir - points;
			break;
		case 3:
			habilidadesPrimarias->addRES(points);
			_pontoDistribuir = _pontoDistribuir - points;
			break;
		case 4:
			habilidadesPrimarias->addINS(points);
			_pontoDistribuir = _pontoDistribuir - points;
			break;
		default:
			break;
		}
	}
	return;
}

void CPersonagemJogador::update()
{
}
#endif