#pragma once
/*
* Classe CPoder
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os poderes de um personagem
*
*/



#ifndef _CPODER_H_
#define _CPODER_H_

#include "Enumerators.h"
#include "CWarBugObject.h"
#include "CBuff.h"

#include "CPersonagem.h"


class CPoder : public CWarBugObject
{
private:
	//Skills
	static void berserkTornado(CPersonagemJogador *user, CPersonagem *target, int level);
	//RaceTypes
	static void beetleSkills(CPersonagem *user, CPersonagem *target, TipoPoder skillIndex, int level);

public:
	static void cast(CPersonagem *user, CPersonagem *target, Raca userRace, TipoPoder skillIndex, int level);
};

#endif