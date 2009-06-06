/*
* Classe CPersonagem
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os personagens do jogo
*
*/
#ifndef _CPERSONAGEM_CPP_
#define _CPERSONAGEM_CPP_

#include "CPersonagem.h"

#include "CBuff.h"

#ifndef _CPODER_H_
#include "CPoder.h"
#endif

void CPersonagem::initCPersonagem()
{
	initC3DObject();
	setID(-1);
	nivel = 1;
	experiencia = 0;
	xpToNextLv = 0;
	dinheiro = 0;
	habilidadesPrimarias = new CHabilidades();
	bonusPrimario = new CBonusPrimario();
	inventario = new CBolsa();
	habilidadesSecundarias = new CHabilidadesSecundarias();
	bonusSecundario = new CBonusSecundario();
	//poderes = new CPoder();
	status = new CBuffList();
	divisorxp = new CDivisorXP(this);
}
//Getters
int CPersonagem::getLevel()
{
	return(nivel);
}
int CPersonagem::getXP()
{
	return(experiencia);
}
int CPersonagem::getMaxXP()
{
	return(xpToNextLv);
}
char *CPersonagem::getName()
{
	return(nome);
}
Raca CPersonagem::getRace()
{
	return(raca);
}
TypeClassChars CPersonagem::getType()
{
	return(tipo);
}
int CPersonagem::getRespawnTime()
{
	return(respawn);
}
float CPersonagem::getDirection()
{
	return(direcao);
}
float CPersonagem::getMoveSpeed()
{
	return(FPS+(float)(getAGI()/10.0f));
}
int CPersonagem::getFOR()
{
	return(habilidadesPrimarias->getFOR() + bonusPrimario->getTotalBonusOf(FOR));
}
int CPersonagem::getDES()
{
	return(habilidadesPrimarias->getDES() + bonusPrimario->getTotalBonusOf(DES));
}
int CPersonagem::getAGI()
{
	return(habilidadesPrimarias->getAGI() + bonusPrimario->getTotalBonusOf(AGI));
}
int CPersonagem::getRES()
{
	return(habilidadesPrimarias->getRES() + bonusPrimario->getTotalBonusOf(RES));
}
int CPersonagem::getINS()
{
	return(habilidadesPrimarias->getINS() + bonusPrimario->getTotalBonusOf(INS));
}
EstadoPersonagem CPersonagem::getState()
{
	return(estado);
}
int CPersonagem::getMoney()
{
	return(dinheiro);
}
CBolsa *CPersonagem::getBolsa()
{
	return(inventario);
}
CHabilidadesSecundarias *CPersonagem::getStats()
{
	return(habilidadesSecundarias);
}
CBonus *CPersonagem::getBonus()
{
	return(bonusSecundario);
}
CBuffList *CPersonagem::getBuffs()
{
	return(status);
}
CHabilidades *CPersonagem::getBaseStats()
{
	return(habilidadesPrimarias);
}
CBonusPrimario *CPersonagem::getBaseBonus()
{
	return(bonusPrimario);
}
CPersonagem *CPersonagem::getTarget()
{
	return(alvo);
}
CCenario *CPersonagem::getScene()
{
	return(cenario);
}
//Setters
void CPersonagem::setLevel(int level)
{
	nivel = level;
}
void CPersonagem::setXP(int xp)
{
	experiencia = xp;
}
void CPersonagem::setMaxXP(int xp)
{
	xpToNextLv = xp;
}
void CPersonagem::setName(char *name)
{
	if(sizeof(nome) >= strlen(name))
		strcpy_s(nome, name);
}
void CPersonagem::setRace(Raca newraca)
{
	raca = newraca;
}
void CPersonagem::setType(TypeClassChars novotipo)
{
	tipo = novotipo;
}
void CPersonagem::setRespawnTime(int newTime)
{
	respawn = newTime;
}
void CPersonagem::setDirection(float direction)
{
	if(direction < 0)
	{
		direction = direction + 360;
	}
	direcao = direction;
}
void CPersonagem::setState(EstadoPersonagem newState)
{
	estado = newState;
}
void CPersonagem::setMoney(int value)
{
	dinheiro = value;
}
void CPersonagem::setBolsa(CBolsa *bolsa)
{
	inventario = bolsa;
}
void CPersonagem::setStats(CHabilidadesSecundarias *stats)
{
	habilidadesSecundarias = stats;
}
void CPersonagem::setBaseStats(CHabilidades *stats)
{
	habilidadesPrimarias = stats;
}
void CPersonagem::setBuffs(CBuffList *buff)
{
	status = buff;
}
void CPersonagem::setBonus(CBonus *bonus)
{
	bonusSecundario = (CBonusSecundario*)bonus;
}
void CPersonagem::setTarget(CPersonagem *Alvo)
{
	alvo = Alvo;
}
void CPersonagem::setScene(CCenario *newScene)
{
	cenario = newScene;
}
void CPersonagem::setBaseBonus(CBonus *bonus)
{
	bonusPrimario = (CBonusPrimario*)bonus;
}

void CPersonagem::addMoney(int value)
{
	dinheiro = dinheiro + value;
}
void CPersonagem::addXP(int value)
{
	experiencia = experiencia + value;
}
//Outros métodos
void CPersonagem::move()
{
	float PI = 3.14159265358979323846f;
    Ponto *teste = new Ponto();
	if(getPosition()->x < destino->x)
	{
	    teste->x = getPosition()->x + getMoveSpeed();
    }
    else
	{
        teste->x = getPosition()->x - getMoveSpeed();
	}
    if(getPosition()->z < destino->z)
    {
	   	teste->z = getPosition()->z + getMoveSpeed();
    }
    else
    {
        teste->z = getPosition()->z - getMoveSpeed();
    }
    setDirection(atan2(destino->z - getPosition()->z, destino->x - getPosition()->x) * 180 / PI);
    setPosition(teste->x, teste->z);
}
//void CPersonagem::die(){}
void CPersonagem::useSkill(TipoPoder skill, int skillLevel)
{
	CPoder::cast(this, this->getRace(), skill, skillLevel, this->getTarget());
}
#endif