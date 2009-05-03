#pragma once
/*
* Classe CPoder
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
	static void berserkTornado(CPersonagemJogador *user, int level);
	static void ariete(CPersonagemJogador *user, CPersonagem *target, int level);
	static void strike(CPersonagemJogador *user, int level);
	//RaceTypes
	static void beetleSkills(CPersonagemJogador *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);

public:
	static void cast(CPersonagem *user, Raca userRace, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
};

#endif