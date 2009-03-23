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
#ifndef _CINIMIGO
#define _CINIMIGO
#include "CPersonagem.cpp"

class CInimigo : public CPersonagem{
private:
	//Lista de divisores de xp
	//Objeto de ia
public:
	CInimigo(){}
	void takeDecision(){}
};
#endif