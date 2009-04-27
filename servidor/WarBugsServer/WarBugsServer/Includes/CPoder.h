#pragma once
/*
* Classe CPoder
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os poderes de um personagem
*
*/
#ifndef _CPODER_H_
#define _CPODER_H_

#include "CWarBugObject.h"
//#include "CBuff.h"
#include <string>
using namespace std;

class CBuff;

class CPoder : public CWarBugObject
{
private:
	string _nome;
	string _descricao;
	int _custoTC;
	int _custoPP;
	int _nivel;
	int _dano;
	CBuff * _statusCausado;
public:
	CPoder();
	void cast();
};

#endif