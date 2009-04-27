#pragma once
/*
* Classe CEquipamento
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os equipamentos de um personagem
*
*/
#ifndef _CEQUIPAMENTO_H_
#define _CEQUIPAMENTO_H_

#include "CArmor.h"
#include "CWeapon.h"

struct CEquipamento
{
	CArmor *armadura;
	CWeapon *arma;
};
#endif