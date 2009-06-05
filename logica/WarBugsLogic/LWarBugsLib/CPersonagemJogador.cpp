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
	setID(-1);
	coordenada = new Ponto();
	dinheiro = 0;
	baseMoveSpeed = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	status = new CBuffList();
	setState(E_PARADO);
	setMoney(0);
	setBolsa(new CBolsa());
	setStats(new CHabilidadesSecundarias());
	setBonus(new CBonusSecundario());
	setBaseStats(new CHabilidades());
	setBaseBonus(new CBonusPrimario());
	setBuffs(new CBuffList());
	_xpToNextLv = 0;
	_pontoDistribuir = 0;
	_lealdade = new CLealdade();
	_quest = new CQuest(this);
	//_party = new irr::core::array<CPersonagemJogador*>();
	//_friends = new irr::core::array<CPersonagemJogador*>();
	_jogadorID = 0;
	alvo = NULL;
	_bareHands = true;
	_ataque = 0;
	_dano = 0;
	_range = 0;
	_speed = 0;
	_tradeOn = false;
	_tradeConfirmation = false;
	_idTrader = -1;
	_idItemTrade = -1;
	_idMoneyTrade = -1;
	_skillPontoDistribuir = 0;
	_skillLevel[0] = 0;
	_skillLevel[1] = 0;
	_skillLevel[2] = 0;
}
//Getters e setters
int CPersonagemJogador::getSkillLevel(int skillIndex)
{
	if((skillIndex > 0)&&(skillIndex < 3))
	{
		return(_skillLevel[skillIndex]);
	}
	else
	{
		return(-1);
	}
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
CLealdade *CPersonagemJogador::getLoyalty()
{
	return(_lealdade);
}
CEquipamento *CPersonagemJogador::getEquip()
{
	return(_equip);
}
int CPersonagemJogador::getPointsLeft()
{
	return(_pontoDistribuir);
}
int CPersonagemJogador::getSkillPointsLeft()
{
	return(_skillPontoDistribuir);
}
CBugSocket *CPersonagemJogador::getSocket()
{
	return(_socketJogador);
}
//Setters
void CPersonagemJogador::setXPToNextLv(int xp)
{
	_xpToNextLv = xp;
}
void CPersonagemJogador::setPointsToDistribute(int points)
{
	_pontoDistribuir = points;
}
void CPersonagemJogador::setSkillPointsToDistribute(int value)
{
	_skillPontoDistribuir = value;
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
void CPersonagemJogador::setSocket(CBugSocket * socket)
{
	_socketJogador = socket;
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
				inventario->addItem(temp);
				_equip->arma = (CWeapon*)item;
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
				inventario->addItem(temp);
				_equip->armadura = (CArmor*)item;
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
void CPersonagemJogador::acceptQuest(CQuest *quest)
{
	_quest = new CQuest(this);
	_quest->setPlayer(quest->getPlayer());
	_quest->setNPC(quest->getNPC());
	_quest->setRequestedItem(quest->getRequestedItem());
	_quest->setRequestedEnemy(quest->getRequestedEnemy());
	_quest->setRequestedNumberOfItens(quest->getRequestedNumberOfItens());
	_quest->setRequestedNumberOfEnemies(quest->getRequestedNumberOfEnemies());
	_quest->setReward(quest->getReward());
	_quest->setXPReward(quest->getXPReward());
	_quest->setItemReward(quest->getItemReward());
	_quest->setLoyaltyReward(quest->getLoyaltyReward());
}
//Speaking
void CPersonagemJogador::speakToPlayer(CPersonagemJogador *alvo){}
void CPersonagemJogador::speakToNPC(CPersonagem *alvo){}
//Batalha
void CPersonagemJogador::takeDamage(int damage, CPersonagem *atkr)
{
	habilidadesSecundarias->addPV((-1)*damage);
	divisorxp->addAttacker(atkr, damage);
}
bool CPersonagemJogador::tryAttack()
{
	int testValue = 0;
	if((this->getDistanceToPoint(alvo->getPosition()) <= _range))
	{
		testValue = _ataque;

		if(testValue > alvo->getStats()->getDefense())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
	else
	{
		return(false);
	}
}
void CPersonagemJogador::attack()
{
	if(tryAttack())
	{
		alvo->takeDamage(_dano, this);
	}
}
//Level Up
void CPersonagemJogador::updateXP(){/*Acessa banco de dados pra atualizar _xpToNextLv*/}
bool CPersonagemJogador::haveLevelUp()
{
	if(experiencia >= _xpToNextLv)
	{
		_pontoDistribuir = _pontoDistribuir + 5;
		nivel = nivel + 1;
		if(nivel%2 == 0)
		{
			_skillPontoDistribuir = _skillPontoDistribuir + 1;
		}
		updateXP();
		return(true);
	}
	else return(false);
}
bool CPersonagemJogador::haveLevelDown()
{
	if(experiencia < 0)
	{
		if(nivel%2 == 0)
		{
			_skillPontoDistribuir = _skillPontoDistribuir - 1;
		}
		nivel = nivel - 1;
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
void CPersonagemJogador::distibuteSkillPoints(int points, int skillIndex)
{
	if((points <= _skillPontoDistribuir)&&((skillIndex > 0)&&(skillIndex < MAXSKILLNUMBER)))
	{
		 _skillLevel[skillIndex] = _skillLevel[skillIndex] + points;
	}
}
void CPersonagemJogador::die()
{
	divisorxp->giveXP();
}
void CPersonagemJogador::update()
{
	status->executeBuffs(this, this->status);
}
#endif