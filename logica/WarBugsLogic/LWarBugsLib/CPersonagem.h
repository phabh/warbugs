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

#include <math.h>
#include "CHabilidadesSecundarias.h"
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
#ifndef _BUFFLIST_
#include "CBuffList.h"
#ifndef _BUFFLIST_
class CBuffList;
#endif
#endif


// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
protected:
	Raca raca;
	float direcao;
	Ponto *destino;
	EstadoPersonagem estado;
	int respawn;
	int dinheiro;
	CBolsa *inventario;
	CHabilidadesSecundarias *habilidadesSecundarias;
	CBonusSecundario *bonusSecundario;
	//CPoder *poderes;
	CBuffList *status;
	CHabilidades *habilidadesPrimarias;
	CBonusPrimario *bonusPrimario;
	CPersonagem *alvo;
public:

	CPersonagem();
	//Getters e Setters
	Raca getRace();
	int getRespawnTime();
	float getDirection();
	float getMoveSpeed();
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
	CBuffList *getBuffs();
	CHabilidades *getBaseStats();
	CBonusPrimario *getBaseBonus();
	CPersonagem *getTarget();
	
	void setRace(Raca raca);
	void setRespawnTime(int newTime);
	void setDirection(float direction);
	void setState(EstadoPersonagem newState);
	void setMoney(int value);
	void setBolsa(CBolsa *bolsa);
	void setBaseStats(CHabilidades *stats);
	void setStats(CHabilidadesSecundarias *stats);
	void setBuffs(CBuffList *buff);
	void setBaseBonus(CBonus *bonus);
	void setBonus(CBonus *bonus);
	void setTarget(CPersonagem *alvo);
	void addMoney(int value);
	//Outros métodos
	void move();
	virtual void attack()=0;
	virtual void takeDamage(int damage)=0;
	void die();
	virtual void useItem(CItem *item)=0;
	//void useSkill(CPoder *skill);
};
#endif