/*
* Classe CInimigo
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever cada personagem inimigo
*
*/
#include "CPersonagem.cpp"
#ifndef _CINIMIGO
#define _CINIMIGO


class CInimigo : public CPersonagem{
private:
	//Lista de divisores de xp
	//Objeto de ia
public:
	CInimigo(){}
	void takeDecision(){}
};
#endif