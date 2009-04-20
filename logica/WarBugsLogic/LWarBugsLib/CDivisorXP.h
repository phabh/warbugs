#pragma once
/*
* Classe CDivisorXP
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever a lista de personagens que causaram dano a um inimigo para a divisao de xp
*
*/
#ifndef _CDIVXP_H_
#define _CDIVXP_H_

#include "CPersonagemJogador.h"

struct CDivisorXP
{
	int dano;
	CPersonagemJogador *causador;
};
#endif