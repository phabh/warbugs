#pragma once
/*
* Classe CHabilidadesSecundarias
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades que se derivam das primárias de um personagem
*
*/
#ifndef _CHABILIDADESSECUNDARIAS_H_
#define _CHABILIDADESSECUNDARIAS_H_

#include "CWarBugObject.h"
#include "CEquipamento.h"
#include "CHabilidades.h"

class CHabilidadesSecundarias : public CWarBugObject 
{
private:
	int _pv;//Pontos de vida
	int _pm;//Pontos de magia
	int _maxpv;//Pontos de vida maximos
	int _maxpm;//Pontos de magia maximos
	int _atqC;//Ataque Corpo-a-Corpo
	int _atqD;//Ataque a disância
	int _danoC;//Dano Corpo-a-Corpo
	int _danoD;//Dano a distância
	int _def;//Defesa
	int _atRt;//Taxa de frequência de ataque
	int _tc;//Tempo de carga

public:
	CHabilidadesSecundarias();
	CHabilidadesSecundarias(int PV, int PM, int ATC, int ATD, int DMC, int DMD, int DEF, int ATR, int TC);
	CHabilidadesSecundarias(CHabilidadesSecundarias *base);
	void generate(CHabilidades *primarias, CEquipamento *equip);
	int getPV();
	int getPM();
	int getMaxPV();
	int getMaxPM();
	int getMeleeAttack();
	int getRangedAttack();
	int getMeleeDamage();
	int getRangedDamage();
	int getDefense();
	int getAttackRate();
	int getChargeTime();
	void setPV(int valor);
	void setPM(int valor);
	void setMaxPV(int valor);
	void setMaxPM(int valor);
	void setMeleeAttack(int valor);
	void setRangedAttack(int valor);
	void setMeleeDamage(int valor);
	void setRangedDamage(int valor);
	void setDefense(int valor);
	void setAttackRate(int valor);
	void setChargeTime(int valor);
	bool addPV(int valor);
	bool addPM(int valor);
	void addMaxPV(int valor);
	void addMaxPM(int valor);
	void addMeleeAttack(int valor);
	void addRangedAttack(int valor);
	void addMeleeDamage(int valor);
	void addRangedDamage(int valor);
	void addDefense(int valor);
	void addAttackRate(int valor);
	void addChargeTime(int valor);
};
#endif