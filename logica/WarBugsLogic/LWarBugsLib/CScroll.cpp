/*
* Classe CScroll
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os pergaminhos, que aumentam os atributos das armas
*
*/
#ifndef _CSCROLL_CPP_
#define _CSCROLL_CPP_

#include "CScroll.h"

CScroll::CScroll()
{
	_bModificador = 0;
	_bDanoMin = 0;
	_bDanoMax = 0;
	_bVelocidade = 0;
	_bAlcance = 0;
	_bDefesa = 0;
	_bDurabilidade = 0;
}
//Métodos da CObject
CScroll::CScroll(TypeItens nome, EstadoItem estado, int preco, bool isdropable, int mod, int danM, int danX, int spd, int rng, int def, int dur)
{
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_bModificador = mod;
	_bDanoMin = danM;
	_bDanoMax = danX;
	_bVelocidade = spd;
	_bAlcance = rng;
	_bDefesa = def;
	_bDurabilidade = dur;
}
int CScroll::getMod()
{
	return(_bModificador);
}
int CScroll::getMinDamage()
{
	return(_bDanoMin);
}
int CScroll::getMaxDamage()
{
	return(_bDanoMax);
}
int CScroll::getSpeed()
{
	return(_bVelocidade);
}
int CScroll::getRange()
{
	return(_bAlcance);
}
int CScroll::getDef()
{
	return(_bDefesa);
}
int CScroll::getDurability()
{
	return(_bDurabilidade);
}

Atrib CScroll::getAtribute()
{
	return (NENHUM);
}
int CScroll::getValue()
{
	return -1;
}
#endif