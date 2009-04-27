#pragma once
/*
* Classe CHabilidades
*
* Autor: Eder Figueiredo
*
* Objetivo: Descreve as habilidades primárias de um personagem
*
*/
#ifndef _CHABILIDADES_H_
#define _CHABILIDADES_H_

#include "CWarBugObject.h"

class CHabilidades : public CWarBugObject
{
private:
	int _forca;
	int _agilidade;
	int _destreza;
	int _instinto;
	int _resistencia;
public:
	CHabilidades();
	CHabilidades(int FOR, int AGI, int DES, int INS, int RES);
	CHabilidades(CHabilidades *base);
	int getFOR();
	int getAGI();
	int getDES();
	int getINS();
	int getRES();
	void setFOR(int valor);
	void setAGI(int valor);
	void setDES(int valor);
	void setINS(int valor);
	void setRES(int valor);
	void addFOR(int valor);
	void addAGI(int valor);
	void addDES(int valor);
	void addINS(int valor);
	void addRES(int valor);
};
#endif