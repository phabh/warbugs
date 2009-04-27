#pragma once
/*
* Classe CVendedor
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem vendedor
*
*/
#ifndef _CVENDEDOR_H_
#define _CVENDEDOR_H_

#include "CPersonagem.h"

class CVendedor : public CPersonagem{
private:
	int _dinheiro;
public:
	CVendedor();
	void speak();
	void buy();
	void sell();
};
#endif