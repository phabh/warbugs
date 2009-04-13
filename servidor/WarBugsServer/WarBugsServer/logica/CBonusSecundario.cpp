/*
* Classe CBonusPrimario
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os bonus primários de um personagem
*
*/
#include "CHabilidades.cpp"
#include "CHabilidadesSecundarias.cpp"
#include "CBuff.cpp"
#include "CBonus.cpp"
#ifndef _CBONUSSECUNDARIO
#define _CBONUSSECUNDARIO
class CBonusSecundario : public CBonus
{
	CHabilidadesSecundarias *valor;
};
#endif