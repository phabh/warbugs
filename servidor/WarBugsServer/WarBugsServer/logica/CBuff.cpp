/*
* Classe CBuff
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os buffs que serão utilizados durante o jogo
*
*/
#include "CObject.cpp"
#ifndef _CBUFF
#define _CBUFF


class CBuff : public CObject
{
private:
	int _duracao;
	int _indiceImagem;
	int _indiceEfeito;
	bool _badBuff;
public:
	CBuff()
	{
		_duracao = 0;
		_indiceImagem = -1;
		_indiceEfeito = -1;
	}
	void initialize(CObjectCount *counter)
	{
		CObject::initialize(counter);
	}
	void apply();
	void remove();
	void execute();
};
// -------------------------------------------------------------------------------------------------------------------

#endif