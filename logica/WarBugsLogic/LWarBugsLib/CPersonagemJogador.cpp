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
#ifndef _CCENARIO_H_
#include "CCenario.h"
#endif

CPersonagemJogador::CPersonagemJogador()
{
	initC3DObject();
	initCPersonagem();
	setID(-1);
	coordenada = new Ponto();
	dinheiro = 0;
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
//Outros Métodos
//Manipulação de itens
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
	CBolsa *temp = new CBolsa();
	if((item->isDropable())&&(inventario->removeItem(item->getID()) != NULL))
	{
		temp->addItem(item);
		temp->setPosition(this->getPosition());
		getScene()->addBag(temp);
	}
	else
	{
		//ERRO: O ITEM NÃO ESTÁ NO INVENTRÁRIO
	}
	temp = NULL;
	delete temp;
}
void CPersonagemJogador::useItem(CItem *item)
{
	if(haveItem(item))
	{
		if(item->getType() == USO)
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
			//ERRO: EQUIPAMENTOS NÃO PODEM SER USADOS
		}
	}
	else
	{
		//ERRO: NÃO PÓSSUI O ITEM INDICADO
	}
}
void CPersonagemJogador::equip(CItem *item)
{
	//Possui o item?
	if(this->haveItem(item))
	{
		//É arma?
		if(item->getType() == ARMA)
		{
			//Estou equipado?
			if(_equip->arma == NULL)//Se não estou equipado
			{
				_equip->arma = (CWeapon*)item;
				item->setEstado(EQUIPADO);
				habilidadesSecundarias->generate(habilidadesPrimarias, _equip);
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
			else if(inventario->size() < MAXITENS)//Se estou equipado e possuo espaço no inventário
			{
				CItem *temp = new CWeapon();
				temp = _equip->arma;
				inventario->addItem(temp);
				_equip->arma = (CWeapon*)item;
				temp = NULL;
				delete temp;
				habilidadesSecundarias->generate(habilidadesPrimarias, _equip);
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
				//ERRO: INVENTÁRIO CHEIO
			}
		}
		else if(item->getType() == ARMADURA)
		{
			if(_equip->armadura == NULL)
			{
				_equip->armadura = (CArmor*)item;
				item->setEstado(EQUIPADO);
				habilidadesSecundarias->generate(habilidadesPrimarias, _equip);
			}
			else if(inventario->size() < MAXITENS)
			{
				CItem *temp = new CArmor();
				temp = _equip->armadura;
				inventario->addItem(temp);
				_equip->armadura = (CArmor*)item;
				habilidadesSecundarias->generate(habilidadesPrimarias, _equip);
				temp = NULL;
				delete temp;
			}
			else
			{
				//ERRO: INVENTÁRIO CHEIO
			}
		}
		else
		{
			//ERRO: O ITEM NÃO É UMA ARMA/ARMADURA
		}
	}
	else
	{
		//ERRO: O ITEM NÃO ESTÁ NO INVENTRÁRIO
	}
}
void CPersonagemJogador::unequip(CItem *item)
{
	if(_equip->arma->getID() == item->getID())
	{
		if(inventario->size() < MAXITENS)
		{
			_equip->arma = NULL;
			habilidadesSecundarias->generate(habilidadesPrimarias, _equip);
			item->setEstado(NAMOCHILA);
			inventario->addItem(item);
			_ataque = habilidadesPrimarias->getFOR();
			_dano = habilidadesPrimarias->getFOR();
			_range = MAXMELEERANGE;
			_speed = habilidadesPrimarias->getAGI();
			_bareHands = true;
		}
		else
		{
			//ERRO: O INVENTÁRIO ESTÁ CHEIO
		}
	}
	else if(_equip->armadura->getID() == item->getID())
	{
		_equip->arma = NULL;
		item->setEstado(NAMOCHILA);
	}
	else
	{
		//ERRO: O ITEM ESPECIFICADO NÃO ESTÁ EQUIPADO
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
	else return; // ERRO: NÚMERO MÁXIMO DE AMIGOS PERMITIDOS ATINGIDO
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
		//ERRO: O AMIGO NÃO CONSTA NA LISTA
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
		//ERRO: NÃO É LÍDER DO GRUPO
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
		//ERRO: O JOGADOR NÃO PERTENCE AO GRUPO
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
		//ERRO: JÁ FAZ PARTE DE UMA PARTY
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
		//ERRO: JÁ FAZ PARTE DE UMA PARTY
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
	_quest->beginQuest();
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
		if(_bareHands)
		{
			alvo->takeDamage(_dano, this);
		}
		else
		{
			int dano = _dano +((clock()%(_equip->arma->getMaxDamage() - _equip->arma->getMinDamage()))+_equip->arma->getMinDamage());
		}
	}
}
//Level Up
void CPersonagemJogador::updateXP(){/*Acessa banco de dados pra atualizar _xpToNextLv*/}
bool CPersonagemJogador::haveLevelUp()
{
	if(experiencia >= xpToNextLv)
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