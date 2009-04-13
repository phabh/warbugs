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
#include "C3DObject.cpp"
#include "CBonus.cpp"
#include "CItem.cpp"
#include "CPoder.cpp"
#include "CBonusSecundario.cpp"
#include <list>
#include <irrlicht.h>
using namespace std;
#ifndef _CPERSONAGEM
#define _CPERSONAGEM


enum EstadoPersonagem{
	PARADO,
	ANDANDO
};
// ------------------------------------------------------------------------------------------------------------
class CPersonagem : public C3DObject{
protected:
	EstadoPersonagem estado;
	//Tempo de respawn
	irr::core::array<CItem*> *inventario;
	CHabilidadesSecundarias *habilidadesSecundarias;
	CBonusSecundario *bonusSecundario;
	irr::core::array<CPoder*> *poderes;
public:
	CPersonagem(){
		inventario = new irr::core::array<CItem*>();
		habilidadesSecundarias = new CHabilidadesSecundarias();
		bonusSecundario = new CBonusSecundario();
		poderes = new irr::core::array<CPoder*>();
	}
	//Getters e Setters
	CHabilidadesSecundarias getStats()
	{
		return(habilidadesSecundarias);
	}
	//Outros métodos
	void move(){}
	virtual void attack(int attackType)=0;
	virtual void takeDamage(int damage)=0;
	void die(){}
	virtual void useItem(CItem *item)=0;
	void useSkill(CPoder *skill){}

};
#endif