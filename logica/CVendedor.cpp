/*
* Classe CVendedor
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem vendedor
*
*/

#ifndef _CVENDEDOR
#define _CVENDEDOR
#include "CPersonagem.cpp"

class CVendedor : public CPersonagem{
private:
	int _dinheiro;
public:
	CVendedor(){}
	void speak(){}
	void buy(){}
	void sell(){}
};
#endif