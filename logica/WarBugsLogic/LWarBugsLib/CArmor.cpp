/*
* Classe CArmor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armaduras do jogo
*
*/
#ifndef _CARMOR_CPP_
#define _CARMOR_CPP_

#include "CArmor.h"

CArmor::CArmor()
{
	setID(-1);
	setDurability(0);
	_raca = ALLRACE;
	_defesa = 0;
	_nivelMagico = 0;
}
CArmor::CArmor(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Raca raca, int def, int dur, int nM)
{
	setID(-1);
	setNome(nome);
	setEstado(estado);
	setPrice(preco);
	setDropable(isdropable);
	_raca = raca;
	_defesa = def;
	setDurability(dur);
	_nivelMagico = nM;
}
void CArmor::useScroll(CScroll *&scroll)
{
	if(scroll != NULL)
	{
		_defesa = _defesa + scroll->getDef();
		setDurability(getDurability() + scroll->getDurability());
		if(scroll->getDef())
		{
			_nivelMagico = _nivelMagico + 1;
		}
		//scroll->setOwner(null);
		delete scroll;
		scroll = NULL;
	}
}
Raca CArmor::getRace()
{
	return(_raca);
}
int CArmor::getDef()
{
	return(_defesa);
}
int CArmor::getMagicLevel()
{
	return(_nivelMagico);
}
int CArmor::getValue()
{
	return -1;
}
Atrib CArmor::getAtribute()
{
	return (NENHUM);
}
void CArmor::setAll(Raca raca, int def, int dur, int nM)
{
	_raca = raca;
	_defesa = def;
	setDurability(dur);
	_nivelMagico = nM;
}
#endif