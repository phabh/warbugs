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
#include "CPersonagem.cpp"
#ifndef _CVENDEDOR
#define _CVENDEDOR


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