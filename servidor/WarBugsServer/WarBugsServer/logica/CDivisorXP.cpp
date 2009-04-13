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
#include "CPersonagemJogador.cpp"
#ifndef _CDIVXP
#define _CDIVXP

struct CDivisorXP
{
	int dano;
	CPersonagemJogador *causador;
};
#endif