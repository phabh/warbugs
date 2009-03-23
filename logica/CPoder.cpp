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

#ifndef _CPODER
#define _CPODER
#include "CLogicObject.cpp"
#include "CBuff.cpp"
#include <string>
using namespace std;

class CPoder : public CLogicObject{
private:
	string _nome;
	string _descricao;
	int _custoTC;
	int _custoPP;
	int _nivel;
	int _dano;
	CBuff * _statusCausado;
public:
	CPoder(){
		_nome = "";
		_descricao = "";
		_custoTC = 0;
		_custoPP = 0;
		_nivel = 0;
		_dano = 0;
		_statusCausado = NULL;
	}
	void cast(){}
};

#endif