/*
* Classe CPersonagem
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os personagens do jogo
*
*/

#ifndef _CPERSONAGEM
#define _CPERSONAGEM
#include "C3DObject.cpp"
#include "CBonus.cpp"
#include "CItem.cpp"
#include "CPoder.cpp"

enum EstadoPersonagem{
	PARADO,
	ANDANDO
};
// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
private:
	EstadoPersonagem _estado;
	//TEmpo de respawn
	//Lista do inventario
	CHabilidadesSecundarias *_habilidadesSecundarias;
	CBonusSecundario *_bonusSecundario;
	//Lista de poderes
public:
	CPersonagem(){}
	void move(){}
	void attack(CPersonagem *alvo){}
	void die(){}
	void useItem(CItem *item){}
	void useSkill(CPoder *skill){}
};
#endif