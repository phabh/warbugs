#pragma once
/*
* Classe CInimigo
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem inimigo
*
*/
#ifndef _CINIMIGO_H_

#ifndef _CCENARIO_H_
#include "CCenario.h"
#ifndef _CCENARIO_H_
class CCenario;
#endif
#endif

#include "CDivisorXP.h"

//#include "CPersonagem.h"
#include <time.h>

#define _CINIMIGO_H_
class CInimigo : public CPersonagem{
private:
	//Lista de divisores de xp
	//Objeto de ia
public:
	CInimigo();

	void takeDecision();

	bool tryAttack();
	void attack();
	void takeDamage(int damage, CPersonagem *atkr);
	void die();
	void useItem(CItem *item);

	void update();
};
#endif