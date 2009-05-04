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
	_raca = ALLRACE;
	_defesa = 0;
	_durabilidade = 0;
	_nivelMagico = 0;
}
CArmor::CArmor(TypeItens nome, EstadoItem estado, int preco, bool isdropable, Raca raca, int def, int dur, int nM)
{
	setNome(nome);
	setEstado(estado);
	setPreco(preco);
	setDropable(isdropable);
	_raca = raca;
	_defesa = def;
	_durabilidade = dur;
	_nivelMagico = nM;
}
void CArmor::useScroll(CScroll *&scroll)
{
	if(scroll != NULL)
	{
		_defesa = _defesa + scroll->getDef();
		_durabilidade = _durabilidade + scroll->getDurability();
		if(scroll->getDef())
		{
			_nivelMagico = _nivelMagico + 1;
		}
		//scroll->setOwner(null);
		delete scroll;
		scroll = NULL;
	}
}
int CArmor::getDef()
{
	return(_defesa);
}
int CArmor::getDurability()
{
	return(_durabilidade);
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
#endif