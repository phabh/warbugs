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

//#include "CPersonagem.h"
#include <time.h>

#define _CINIMIGO_H_
class CInimigo : public CPersonagem{
private:
	CCenario *_cenario;
	//Lista de divisores de xp
	//Objeto de ia
public:
	CInimigo();

	CCenario *getScene();

	void setScene(CCenario *newScene);

	void takeDecision();

	void attack();
	void takeDamage(int damage);
	void die();
	void useItem(CItem *item);

	void update();
};
#endif