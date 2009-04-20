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
#ifndef _CPODER_CPP_
#define _CPODER_CPP_

#include "CPoder.h"

#include <string>
using namespace std;

CPoder::CPoder()
	{
		_nome = "";
		_descricao = "";
		_custoTC = 0;
		_custoPP = 0;
		_nivel = 0;
		_dano = 0;
		_statusCausado = NULL;
	}
void CPoder::cast(){}

#endif