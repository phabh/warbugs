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
		_raca = TODAS;
		_defesa = 0;
		_durabilidade = 0;
		_nivelMagico = 0;
	}
	//Métodos da CObject
	void CArmor::initialize(CObjectCount *counter, Raca raca, int def, int dur, int nM)
	{
		CItem::initialize(counter);
		_raca = raca;
		_defesa = def;
		_durabilidade = dur;
		_nivelMagico = nM;
	}
	TipoClasse CArmor::getClass()
	{
		return(CARMOR);
	}
	int CArmor::getID()
	{
		return(CWarBugObject::getID());
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