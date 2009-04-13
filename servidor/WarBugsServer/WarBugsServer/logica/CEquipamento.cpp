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


#ifndef _CEQUIPAMENTO
#define _CEQUIPAMENTO
#include "CArmor.cpp"
#include "CWeapon.cpp"

struct CEquipamento
{
	CArmor *armadura;
	CWeapon *arma;
};
#endif