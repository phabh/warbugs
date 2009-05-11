#pragma once
/*
* Classe CPersonagem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os personagens do jogo
*
*/
#ifndef _CPERSONAGEM_H_

//#include "CHabilidadesSecundarias.h"
	//#include "CWarBugObject.h"
	//#include "CEquipamento.h"
	//#include "CHabilidades.h"
#include "CBolsa.h"
	//#include "CItem.h"
#include "CBonusPrimario.h"
	//#include "CHabilidades.h"
	//#include "CBonus.h"
#include "CBonusSecundario.h"
	//#include "CHabilidadesSecundarias.h"
	//#include "CBonus.h"
#ifndef _CBUFF_H_
#include "CBuff.h"
#ifndef _CBUFF_H_
class CBuff;
#endif
#endif

// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
protected:
	EstadoPersonagem estado;
	//Tempo de respawn
	int dinheiro;
	CBolsa *inventario;
	CHabilidadesSecundarias *habilidadesSecundarias;
	CBonusSecundario *bonusSecundario;
	//CPoder *poderes;
	CBuff *status;
	CHabilidades *habilidadesPrimarias;
	CBonusPrimario *bonusPrimario;
public:

	CPersonagem();
	//Getters e Setters
	int getFOR();
	int getDES();
	int getAGI();
	int getRES();
	int getINS();
	EstadoPersonagem getState();
	int getMoney();
	CBolsa *getBolsa();
	CHabilidadesSecundarias *getStats();
	CBonus *getBonus();
	CBuff *getBuffs();
	CHabilidades *getBaseStats();
	CBonusPrimario *getBaseBonus();
	
	void setState(EstadoPersonagem newState);
	void setMoney(int value);
	void setBolsa(CBolsa *bolsa);
	void setBaseStats(CHabilidades *stats);
	void setStats(CHabilidadesSecundarias *stats);
	void setBuffs(CBuff *buff);
	void setBaseBonus(CBonus *bonus);
	void setBonus(CBonus *bonus);
	
	void addMoney(int value);
	//Outros m�todos
	void move();
	virtual void attack()=0;
	virtual void takeDamage(int damage)=0;
	void die();
	virtual void useItem(CItem *item)=0;
	//void useSkill(CPoder *skill);

};
#endif