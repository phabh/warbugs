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
#include "CLogicObject.cpp"

#ifndef _CBUFF
#define _CBUFF

class CBuff abstract : public CLogicObject{
private:
	int _duracao;
	int _indiceImagem;
	int _indiceEfeito;
public:
	CBuff(){
		_duracao = 0;
		_indiceImagem = -1;
		_indiceEfeito = -1;
	}
	void initialize(CObjectCount *counter){
		CObject::initialize(counter);
	}
	void apply();
	void remove();
	void execute();
};
// -------------------------------------------------------------------------------------------------------------------

#endif