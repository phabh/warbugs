/*
* Classe CBuff
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os buffs que serão utilizados durante o jogo
*
*/


#ifndef _CBUFF_CPP_
#define _CBUFF_CPP_

#include "CBuff.h"
#include "CPersonagemJogador.h"
#include <iostream>
using namespace std;

CBuff::CBuff()
	{
		_duracao = 0;
		_indiceImagem = -1;
		_indiceEfeito = -1;
		_badBuff = false;
		_tipoBuff = NORMAL;
		_valor1 = 0;
		_valor2 = 0;
		_valor3 = 0;
		_next = NULL;
	}
CBuff::CBuff(TipoBuff tipo, int dur, int img, int efc, int val1, int val2, int val3)
{
	_tipoBuff = tipo;
	_indiceEfeito = efc;
	_indiceImagem = img;
	_duracao = dur;
	switch(tipo)
	{
		case DESESPERO:
			_duracao = -1;
			_valor1 = val1;//Probabilidade de ser afetado pelo desespero
			_valor2 = val2;//Dano que ele receberá se atacar a si mesmo
			_badBuff = true;
			break;
		case VENENO:
			_valor1 = val1;//Dano que será causado por segundo
			_valor2 = val2;//Valor para o teste de resistencia
			_badBuff = true;
			break;
		case DADIVA:
			_valor1 = val1;//Valor de incremento em INS
			_badBuff = false;
			break;
		case BERSERKER:
			_valor1 = val1;//Raio que afetara
			_valor2 = val2;//dano causado por segundo
			_valor3 = val3;//redução em RES e DEF
			_badBuff = false;
			break;
		case STRIKE:
			_valor1 = val1;//Dano por toque
			_valor2 = val2;//Bônus em RES e DEF
			_badBuff = false;
			break;
		case BACKSTAB:
			_valor1 = val1;//Raio de alcance
			_valor2 = val2;//Dano causado
			_badBuff = false;
			break;
		case LENTO:
			_valor1 = val1;//Redução em AGI
			_valor2 = val2;//Dano causado por segundo
			_valor3 = val3;//Valor para o teste de resistencia
			_badBuff = true;
			break;
		case STUN:
			_valor1 = val1;//Valor para teste de resistencia
			_badBuff = true;
			break;
		case ATORDOADO:
			_valor1 = val1;//Redução em AGI
			_valor2 = val2;//Redução em DES
			_valor3 = val3;//Área de efeito
			_badBuff = true;
			break;
		default:
			break;
	}
}
TipoBuff CBuff::getTipo()
{
	return(_tipoBuff);
}
int CBuff::getTipoAsInt()
{
	return((int)_tipoBuff);
}
int CBuff::getDuration()
{
	return(_duracao);
}
void CBuff::setDuration(int newDuration)
{
	_duracao = newDuration;
}
void CBuff::addDuration(int newDuration)
{
	_duracao = _duracao + newDuration;
}
void CBuff::initialize(CObjectCount *counter)
{
	CWarBugObject::initialize(counter);
}
void CBuff::addBuff(CBuff * buff)
{
	CBuff *temp;// = new CBuff();
	temp = this;
	while(temp->_next != NULL)
	{
		temp = temp->_next;
	}
	temp->_next = buff;
	buff->_next = NULL;
	temp = NULL;
	delete temp;
	return;
}
void CBuff::remove(int index)
{
	CBuff *first;// = new CBuff();
	CBuff *temp;// = new CBuff();
	first = this;
	while(index > 0)
	{
		temp = first;
		first = first->_next;
		index = index - 1;
	}
	temp->_next = first->_next;
	temp = NULL;
	first = NULL;
	switch(_tipoBuff)
	{
		case DESESPERO:
			break;
		case VENENO:
			break;
		case DADIVA:
			break;
		case BERSERKER:
			break;
		case STRIKE:
			break;
		case BACKSTAB:
			break;
		case LENTO:
			break;
		case STUN:
			break;
		default:
			break;
	}
	delete first;
	delete temp;
	return;
}
void CBuff::execute(CPersonagemJogador *jogador)
{
	int index = 0;
	CBuff *temp = new CBuff();
	temp = this;
	while(temp->_next != NULL)
	{
		switch(temp->getTipo())
		{
		case DESESPERO:
			jogador->getFOR();
			break;
		case VENENO:
			break;
		case DADIVA:
			break;
		case BERSERKER:
			break;
		case STRIKE:
			break;
		case BACKSTAB:
			break;
		case LENTO:
			break;
		case STUN:
			break;
		case ATORDOADO:
			break;
		default:
			break;
		}
		temp->addDuration(-1);
		if(temp->getDuration() == 0)
		{
			temp->remove(index);
		}
		index = index + 1;
	}
	return;
}

#endif