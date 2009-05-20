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
}
CBuff::CBuff(TipoBuff tipo, int dur, /*int img, int efc,*/ int val1, int val2, int val3)
{
	_tipoBuff = tipo;
	//_indiceEfeito = efc;
	//_indiceImagem = img;
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
void CBuff::addBuff(CBuffList * lista, CPersonagem *alvo)
{
	CBonus *bonus;
	
	if(lista->haveBuff(this))
	{
		CBuff *temp = lista->getBuff(this);
		temp->remove(alvo);
		lista->removeBuff(this);
		temp = NULL;
		delete temp;
	}

	lista->addBuff(this);
	switch(getTipo())
	{
		case DADIVA:
			bonus = new CBonusPrimario();
			bonus->createBonus(0, 0, 0, _valor1, 0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BERSERKER:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,0,0,0,_valor3);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			bonus = new CBonusSecundario();
			bonus->createBonus(0,0,0,0,_valor3);
			bonus->setOrigem(this->getTipo());
			alvo->getBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case STRIKE:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,0,0,0,_valor2);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			bonus = new CBonusSecundario();
			bonus->createBonus(0,0,0,0,_valor2);
			bonus->setOrigem(this->getTipo());
			alvo->getBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case LENTO:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,0,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case STUN:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,((-1)*(alvo->getAGI())),0,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case ATORDOADO:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,_valor2,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		default:
			break;
	}
	return;
}
void CBuff::remove(CPersonagem *alvo)
{
	switch(this->getTipo())
	{
		case DADIVA:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BERSERKER:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			alvo->getBonus()->removeElement(this->getTipo());
			break;
		case STRIKE:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			alvo->getBonus()->removeElement(this->getTipo());
			break;
		case LENTO:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case STUN:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case ATORDOADO:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		default:
			break;
	}
	return;
}
void CBuff::execute(CPersonagem *jogador, CBuffList *lista)
{
	switch(getTipo())
	{
	case DESESPERO:
		break;
	case VENENO:
		if(jogador->getRES() < _valor2)
		{
			jogador->getStats()->addPV(((-1)*_valor1));
		}
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
		if(jogador->getFOR() < _valor3)
		{
			jogador->getStats()->addPV(((-1)*_valor2));
		}
		break;
	case STUN:
		break;
	case ATORDOADO:
		break;
	default:
		break;
	}
	addDuration(-1);
	if(getDuration() == 0)
	{
		this->remove(jogador);
		lista->removeBuff(this->getID());
	}
	return;
}

#endif