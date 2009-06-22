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
#ifndef _CCENARIO_H_
class CCenario;
#endif

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

#ifndef _CDIVXP_H_
class CDivisorXP;
#endif

#ifndef _CPODER_H_
class CPoder;
#endif
// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
protected:
	int nivel;
	int experiencia;
	int xpToNextLv;
	char nome[10];
	Raca raca;
	TypeClassChars tipo;
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
	CCenario *cenario;
	CDivisorXP *divisorxp;
public:

	void initCPersonagem();
	//Getters e Setters
	int getLevel();
	int getXP();
	int getMaxXP();
	char *getName();
	Raca getRace();
	TypeClassChars getType();
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
	
	void setLevel(int level);
	void setXP(int xp);
	void setMaxXP(int xp);
	void setName(char *name);
	CPersonagem *getTarget();
	CCenario *getScene();
	void setRace(Raca raca);
	void setType(TypeClassChars novotipo);
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
	void setScene(CCenario *newScene);

	void addMoney(int value);
	void addXP(int value);
	//Outros métodos
	bool move();
	virtual int getDEF()=0;
	virtual bool tryAttack()=0;
	virtual void attack()=0;
	virtual void takeDamage(int damage, CPersonagem *atkr)=0;
	virtual void die()=0;
	virtual void useItem(CItem *item)=0;
	void useSkill(TipoPoder skill, int skillLevel);
};
#endif