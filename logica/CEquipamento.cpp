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
#include "CWeapon.cpp"
#include "CArmor.cpp"

#ifndef _CEQUIPAMENTO
#define _CEQUIPAMENTO

struct CEquipamento{
	CArmor *armadura;
	CWeapon *arma;
};
#endif