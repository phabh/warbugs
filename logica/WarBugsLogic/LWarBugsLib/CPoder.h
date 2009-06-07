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
#include <time.h>

//#include "CPersonagemJogador.h"
#include "CCenario.h"


class CPoder : public CWarBugObject
{
private:
	//Skills
	static void berserkTornado(CPersonagemJogador *user, int level);
	static void ariete(CPersonagemJogador *user, CPersonagem *target, int level);
	static void strike(CPersonagemJogador *user, int level);

	static void stealItem(CPersonagem *user, CPersonagem *target);
	static void breakItem(CPersonagem *user, CPersonagem *target);
	static void stinkGas(CPersonagem *user);
	static void killingNeedle(CPersonagem *user, CPersonagem *target);
	static void lightSpeed(CPersonagem *user);
	static void eat(CPersonagem *user, CPersonagem *target);
	static void explode(CPersonagem *user);
	static void invisible(CPersonagem *user);
	static void summonAnts();

	//RaceTypes
	static void beetleSkills(CPersonagemJogador *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);

	static void antSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
	static void termiteSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
	static void shaverSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
	static void lizardSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
	static void ladybugSkills(CPersonagem *user, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);

public:
	static void cast(CPersonagem *user, Raca userRace, TipoPoder skillIndex, int skillLevel, CPersonagem *target = NULL);
};

#endif