/*
* Classe CPersonagemJogador
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem controlado por um jogador
*
*/
#include "CPersonagem.cpp"
#include "CEquipamento.cpp"
#include "CBuff.cpp"
#include "CAtributo.cpp"
#include "CQuest.cpp"
#include <list>
#include <iostream>
#include <time.h>
#include <irrlicht.h>
using namespace std;
#ifndef _CPERSONAGEMJOGADOR
#define _CPERSONAGEMJOGADOR


//Constantes
#define MAXFRIENDS 10
#define MAXPARTYSIZE 4
#define MAXSTATS 5
//end Constantes

class CPersonagemJogador : public CPersonagem
{
	CHabilidades *_habilidadesPrimarias;
	CBonusPrimario *_bonusPrimario;
	int _nivel;
	int _experiencia;
	int _dinheiro;
	CEquipamento *_equip;
	irr::core::array<CBuff*> *_status;
	CLealdade *_lealdade;
	irr::core::array<CPersonagemJogador*> *_party;
	irr::core::array<CPersonagemJogador*> *_friends;
	int _jogadorID;
public:
	CPersonagemJogador()
	{
		_habilidadesPrimarias = new CHabilidades();
		_bonusPrimario = new CBonusPrimario();
		_nivel = 1;
		_experiencia = 0;
		_dinheiro = 0;
		_equip = new CEquipamento();
		_status = new irr::core::array<CBuff*>();
		_lealdade = new CLealdade();
		_party = new irr::core::array<CPersonagemJogador*>();
		_friends = new irr::core::array<CPersonagemJogador*>();
		_jogadorID = 0;
	}
	//Getters e setters
	void setParty(irr::core::array<CPersonagemJogador*> *lista)
	{
		_party = lista;
	}
	//Outros Métodos
	void equip(CItem *item)
	{
		if(item->getClass() == CWEAPON)
		{
			_equip->arma = (CWeapon*)item;
			item->setEstado(EQUIPADO);
		}
		else if(item->getClass() == CARMOR)
		{
			_equip->armadura = (CArmor*)item;
			item->setEstado(EQUIPADO);
		}
		else
		{
			//ERRO: O ITEM NÃO É UMA ARMA/ARMADURA
		}
	}
	void unequip(CItem *item)
	{
		if(_equip->arma == item)
		{
			_equip->arma = NULL;
			item->setEstado(NAMOCHILA);
		}
		else if(_equip->armadura == item)
		{
			_equip->arma = NULL;
			item->setEstado(NAMOCHILA);
		}
		else
		{
			//ERRO: O ITEM ESPECIFICADO NÃO ESTÁ EQUIPADO
		}
	}
	void addFriend(CPersonagemJogador *newFriend)
	{
		if(_friends->size() < MAXFRIENDS)
		{
			_friends->push_back(newFriend);
			_friends->sort();
		}
		else return; // ERRO: NÚMERO MÁXIMO DE AMIGOS PERMITIDOS ATINGIDO
	}
	void removeFriend(CPersonagemJogador *jogador)
	{
		irr::u32 i =_friends->binary_search_const(jogador);
		if(i > 0)
		{
			_friends->erase(i);
		}
		else
		{
			//ERRO: O AMIGO NÃO CONSTA NA LISTA
		}
		return;
	}
	bool isPartyLeader()
	{
		return((_party->empty())&&(_party->getLast() == this));
	}
	int isPartyMember()
	{
		return(_party->binary_search_const(this));
	}
	void addPartyMember (CPersonagemJogador *jogador)
	{
		if((this->isPartyLeader()) && (!jogador->isPartyMember()))
		{
			_party->push_front(jogador);
		}
		else
		{
			//ERRO: NÃO É LÍDER DO GRUPO
		}
	}
	void removePartyMember(CPersonagemJogador *jogador)
	{
		if((_party->empty()) && ((jogador->isPartyMember())>=0))
		{
			_party->erase(jogador->isPartyMember());
		}
		else
		{
			//ERRO: O JOGADOR NÃO PERTENCE AO GRUPO
		}
		return;
	}
	void givePartyAlliesID(irr::core::array<CPersonagemJogador*> *lista)
	{
		lista = _party;
	}
	void updateAlliesID()
	{
	}
	void createParty()
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
	void joinParty(CPersonagemJogador *lider)
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
	void leaveParty(CPersonagemJogador *lider)
	{
		if(!(_party->empty()))
		{
			lider->removePartyMember(this);
			_party->clear();
		}
	}
	void acceptQuest(CQuest *quest){}
	void speakToPlayer(CPersonagemJogador *alvo){}
	void speakToNPC(CPersonagem *alvo){}
	//Implementando métodos pureVirtual
	void attack(CPersonagem *alvo, int attackType)
	{
		int testValue = 0;
		if(attackType%2 == 0)
		{
			//MELEE
			testValue = habilidadesSecundarias->getMeleeAttack() + ((rand()%_equip->arma->getMaxDamage())+_equip->arma->getMinDamage())/2;
			if(testValue > alvo->getStats().getDefense())
			{
				testValue = habilidadesSecundarias->getMeleeDamage() + ((rand()%_equip->arma->getMaxDamage())+_equip->arma->getMinDamage());
			}
		}
	}
};
#endif