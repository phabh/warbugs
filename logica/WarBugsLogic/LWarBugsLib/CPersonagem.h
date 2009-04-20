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
#define _CPERSONAGEM_H_

#include "Enumerators.h"
#include "C3DObject.h"

#ifndef _CITEM_H_
class CItem;
#endif

#ifndef _CHABILIDADESSECUNDARIAS_H_
class CHabilidadesSecundarias;
#endif

#ifndef _CBONUSSECUNDARIO_H_
class BonusSecundario;
#endif

#include "CBonus.h"

#ifndef _CPODER_H_
class CPoder;
#endif


//#include "CItem.h"
//#include "CHabilidadesSecundarias.h"
//#include "CBonusSecundario.h"
//#include "CPoder.h"
#include <irrlicht.h>
//using namespace std;

// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
protected:
	EstadoPersonagem estado;
	//Tempo de respawn
	irr::core::array<CItem*> *inventario;
	CHabilidadesSecundarias *habilidadesSecundarias;
	CBonus *bonusSecundario;
	irr::core::array<CPoder*> *poderes;
public:
	CPersonagem();
	//Getters e Setters
	CHabilidadesSecundarias *getStats();
	CBonus *getBonus();
	//Outros métodos
	void move();
	virtual void attack()=0;
	virtual void takeDamage(int damage)=0;
	void die();
	virtual void useItem(CItem *item)=0;
	void useSkill(CPoder *skill);

};
#endif