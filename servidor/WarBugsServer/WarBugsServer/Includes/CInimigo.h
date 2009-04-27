#pragma once
/*
* Classe CInimigo
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem inimigo
*
*/
#ifndef _CINIMIGO_H_
#define _CINIMIGO_H_

#include "CPersonagem.h"

class CInimigo : public CPersonagem{
private:
	//Lista de divisores de xp
	//Objeto de ia
public:
	CInimigo();
	void takeDecision();
};
#endif