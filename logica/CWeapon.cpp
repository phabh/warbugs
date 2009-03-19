/*
* Classe CWeapon
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armas do jogo
*
*/

#include "CItem.cpp"
#include "CScroll.cpp"

#ifndef _CWEAPON
#define _CWEAPON

class CWeapon : public CItem{
private:
	Raca _raca;
	int _modificador;
	int _danoMin;
	int _danoMax;
	int _velocidade;
	int _alcance;
	int _durabilidade;
	int _nivelMagico;

public:
	CWeapon(){
		_raca = TODAS;
		_modificador = 0;
		_danoMin = 0;
		_danoMax = 0;
		_velocidade = 0;
		_alcance = 0;
		_durabilidade = 0;
		_nivelMagico = 0;
	}
	//Métodos da CObject
	void initialize(CObjectCount *counter, Raca raca, int mod, int danM, int danX, int spd, int rng, int dur, int nM){
		CItem::initialize(counter);
		_raca = raca;
		_modificador = mod;
		_danoMin = danM;
		_danoMax = danX;
		_velocidade = spd;
		_alcance = rng;
		_durabilidade = dur;
		_nivelMagico = nM;
	}
	TipoClasse getClass(){
		return(CWEAPON);
	}
	int getID(){
		return(CObject::getID());
	}	
	void useScroll(CScroll *&scroll){
		if(scroll != NULL){
			_modificador = _modificador + scroll->getMod();
			_danoMin = _danoMin + scroll->getMinDamage();
			_danoMax = _danoMax + scroll->getMaxDamage();
			_velocidade = _velocidade + scroll->getSpeed();
			_alcance = _alcance + scroll->getRange();
			_durabilidade = _durabilidade + scroll->getDurability();
			if((scroll->getMod())||
				(scroll->getMinDamage())||
				(scroll->getMaxDamage())||
				(scroll->getSpeed())||
				(scroll->getRange())){
			_nivelMagico = _nivelMagico + 1;
			}
			//scroll->setOwner(null);
			delete scroll;
			scroll = NULL;
		}
	}
	int getMod(){return(_modificador);}
	int getMinDamage(){return(_danoMin);}
	int getMaxDamage(){return(_danoMax);}
	int getSpeed(){return(_velocidade);}
	int getRange(){return(_alcance);}
	int getDurability(){return(_durabilidade);}
	int getMagicLevel(){return(_nivelMagico);}
	//void equip(CPersonagem *alvo)
	//void unequip()
};
#endif