/*
* Classe CPoder
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os poderes de um personagem
*
*/
#ifndef _CPODER_CPP_
#define _CPODER_CPP_

#include "CPoder.h"
//Skills
void CPoder::berserkTornado(CPersonagemJogador *user, CPersonagem *target, int level)
{
	CBuff *temp;
	switch(level)
	{
	case 0:
		temp = new CBuff(BERSERKER, 5*FPS, 10, user->getFOR()+1, -10);
		break;
	case 1:
		break;
	default:
		break;
	}
}


//RaceTypes
void CPoder::beetleSkills(CPersonagem *user, CPersonagem *target, TipoPoder skillIndex, int level)
{
	switch(skillIndex)
	{
	case SK_BERSERK_TORNADO:

		break;
	default:
		break;
	}
}

void CPoder::cast(CPersonagem *user, CPersonagem *target, Raca userRace, TipoPoder skillIndex, int level)
{
	switch(userRace)
	{
	case BESOURO:
		beetleSkills(user, target, skillIndex, level);
		break;
	default:
		break;
	}
}

#endif