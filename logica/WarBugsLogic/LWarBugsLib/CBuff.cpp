/*
* Classe CBuff
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever os buffs que serão utilizados durante o jogo
*
*/

#ifndef _CCENARIO_H_
#include "CCenario.h"
#endif

#ifndef _CBUFF_CPP_
#define _CBUFF_CPP_

#include "CBuff.h"

CBuff::CBuff()
{
	setID(-1);
	_duracao = 0;
	_indiceImagem = -1;
	_indiceEfeito = -1;
	_badBuff = false;
	_tipoBuff = BUFF_NORMAL;
	_causador = NULL;
	_valor1 = 0;
	_valor2 = 0;
	_valor3 = 0;
}
CBuff::CBuff(TipoBuff tipo, int dur, /*int img, int efc,*/ CPersonagem *origem, int val1, int val2, int val3)
{
	setID(-1);
	_tipoBuff = tipo;
	//_indiceEfeito = efc;
	//_indiceImagem = img;
	_duracao = dur;
	_causador = origem;
	switch(tipo)
	{
		case BUFF_DESESPERO:
			_duracao = -1;
			_valor1 = val1;//Probabilidade de ser afetado pelo desespero
			_valor2 = val2;//Dano que ele receberá se atacar a si mesmo
			_badBuff = true;
			break;
		case BUFF_VENENO:
			_valor1 = val1;//Dano que será causado por segundo
			_valor2 = val2;//Valor para o teste de resistencia
			_badBuff = true;
			break;
		case BUFF_DADIVA:
			_valor1 = val1;//Valor de incremento em INS
			_badBuff = false;
			break;
		case BUFF_BERSERKER:
			_valor1 = val1;//Raio que afetara
			_valor2 = val2;//dano causado por segundo
			_valor3 = val3;//redução em RES e DEF
			_badBuff = false;
			break;
		case BUFF_STRIKE:
			_valor1 = val1;//Dano por toque
			_valor2 = val2;//Bônus em RES e DEF
			_badBuff = false;
			break;
		case BUFF_BACKSTAB:
			_valor1 = val1;//Raio de alcance
			_valor2 = val2;//Dano causado
			_badBuff = false;
			break;
		case BUFF_LENTO:
			_valor1 = val1;//Redução em AGI
			_valor2 = val2;//Dano causado por segundo
			_valor3 = val3;//Valor para o teste de resistencia
			_badBuff = true;
			break;
		case BUFF_STUN:
			_valor1 = val1;//Valor para teste de resistencia
			_badBuff = true;
			break;
		case BUFF_ATORDOADO:
			_valor1 = val1;//Redução em AGI
			_valor2 = val2;//Redução em DES
			_valor3 = val3;//Área de efeito
			_badBuff = true;
			break;
		case BUFF_MOON_ABGRUNDI:
			_valor1 = val1;//Aumento em INS
			//TIRAR O DESESPERO
			_badBuff = false;
			break;
		case BUFF_MOON_MABILOG:
			_valor1 = val1;//Aumento de Dano
			_valor2 = val2;//Aumento de DEF
			_badBuff = false;
			break;
		case BUFF_MOON_RESPLANDORA:
			_valor1 = val1;//Aumento em AGI
			_valor2 = val2;//Aumento em INS
			_badBuff = false;
			break;
		case BUFF_MOON_SAMARA:
			_valor1 = val1;//Aumento no Ataque
			_valor2 = val2;//Redução no Dano
			_valor3 = val3;//Aumento em AGI
			_badBuff = false;
			break;
		case BUFF_MOON_TYPHOONA:
			_valor1 = val1;//Aumento em DES
			_valor2 = val2;//Aumento em INS
			_badBuff = false;
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
		case BUFF_DADIVA:
			bonus = new CBonusPrimario();
			bonus->createBonus(0, 0, 0, _valor1, 0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_BERSERKER:
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
		case BUFF_STRIKE:
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
		case BUFF_LENTO:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,0,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_STUN:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,((-1)*(alvo->getAGI())),0,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_ATORDOADO:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,_valor2,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_MOON_ABGRUNDI:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,0,0,_valor1,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			//TIRAR O DESESPERO
			break;
		case BUFF_MOON_MABILOG:
			bonus = new CBonusSecundario();
			bonus->createBonus(0,0,_valor1, _valor1, _valor2);
			bonus->setOrigem(this->getTipo());
			alvo->getBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_MOON_RESPLANDORA:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,0,_valor2,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_MOON_SAMARA:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor3, 0,0,0);
			bonus->setOrigem(this->getTipo());
			alvo->getBaseBonus()->add(bonus);
			bonus = NULL;
			bonus = new CBonusSecundario();
			bonus->createBonus(_valor1, _valor1, _valor2, _valor2, 0);
			alvo->getBonus()->add(bonus);
			bonus = NULL;
			delete bonus;
			break;
		case BUFF_MOON_TYPHOONA:
			bonus = new CBonusPrimario();
			bonus->createBonus(0,_valor1,0,_valor2,0);
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
		case BUFF_DADIVA:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_BERSERKER:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			alvo->getBonus()->removeElement(this->getTipo());
			break;
		case BUFF_STRIKE:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			alvo->getBonus()->removeElement(this->getTipo());
			break;
		case BUFF_LENTO:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_STUN:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_ATORDOADO:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_MOON_ABGRUNDI:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_MOON_MABILOG:
			alvo->getBonus()->removeElement(this->getTipo());
			break;
		case BUFF_MOON_RESPLANDORA:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			break;
		case BUFF_MOON_SAMARA:
			alvo->getBaseBonus()->removeElement(this->getTipo());
			alvo->getBonus()->removeElement(this->getTipo());
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
	case BUFF_DESESPERO:
		break;
	case BUFF_VENENO:
		if(jogador->getRES() < _valor2)
		{
			jogador->takeDamage((-1)*_valor1, _causador);//addPV(((-1)*_valor1));
		}
		break;
	case BUFF_DADIVA:
		break;
	case BUFF_BERSERKER:
		for(int i = 0; i < jogador->getScene()->playerCount(); i = i+1)
		{
			if((jogador->getDistanceToPoint(jogador->getScene()->getPlayerAt(i)->getPosition()) <= _valor1)&&(jogador->getSceneID() != jogador->getScene()->getPlayerAt(i)->getSceneID()))
				((jogador->getScene()->getPlayerAt(i)))->takeDamage((-1)*_valor1, jogador);//getStats()->addPV((-1)*_valor2);
		}
		for(int i = 0; i < jogador->getScene()->monsterCount(); i = i + 1)
		{
			if(jogador->getDistanceToPoint(jogador->getScene()->getMonsterAt(i)->getPosition()) <= _valor1)
			{
				((jogador->getScene()->getMonsterAt(i)))->takeDamage((-1)*_valor1, jogador);//->getStats()->addPV((-1)*_valor2);
			}
		}
		break;
	case BUFF_STRIKE:
		jogador->move();
		for(int i = 0; i < jogador->getScene()->playerCount(); i = i+1)
		{
			if(jogador->getDistanceToPoint(jogador->getScene()->getPlayerAt(i)->getPosition()) <= MAXMELEERANGE)
				((jogador->getScene()->getPlayerAt(i)))->takeDamage((-1)*_valor1, jogador);//getStats()->addPV((-1)*_valor2);
		}
		for(int i = 0; i < jogador->getScene()->monsterCount(); i = i + 1)
		{
			if(jogador->getDistanceToPoint(jogador->getScene()->getMonsterAt(i)->getPosition()) <= MAXMELEERANGE)
			{
				((jogador->getScene()->getMonsterAt(i)))->takeDamage((-1)*_valor1, jogador);//->getStats()->addPV((-1)*_valor2);
			}
		}
		break;
	case BUFF_BACKSTAB:
		break;
	case BUFF_LENTO:
		if(jogador->getFOR() < _valor3)
		{
			jogador->takeDamage((-1)*_valor2, _causador);//->getStats()->addPV(((-1)*_valor2));
		}
		break;
	case BUFF_STUN:
		break;
	case BUFF_ATORDOADO:
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