/*
* Classe CArmor
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever as armaduras do jogo
*
*/
#include "CItem.cpp"
#include "CScroll.cpp"
#ifndef _CARMOR
#define _CARMOR


class CArmor : public CItem{
private:
	Raca _raca;
	int _defesa;
	int _durabilidade;
	int _nivelMagico;

public:
	CArmor(){
		_raca = TODAS;
		_defesa = 0;
		_durabilidade = 0;
		_nivelMagico = 0;
	}
	//Métodos da CObject
	void initialize(CObjectCount *counter, Raca raca, int def, int dur, int nM){
		CItem::initialize(counter);
		_raca = raca;
		_defesa = def;
		_durabilidade = dur;
		_nivelMagico = nM;
	}
	TipoClasse getClass(){
		return(CARMOR);
	}
	int getID(){
		return(CObject::getID());
	}	
	void useScroll(CScroll *&scroll){
		if(scroll != NULL){
			_defesa = _defesa + scroll->getDef();
			_durabilidade = _durabilidade + scroll->getDurability();
			if(scroll->getDef()){
			_nivelMagico = _nivelMagico + 1;
			}
			//scroll->setOwner(null);
			delete scroll;
			scroll = NULL;
		}
	}
	int getDef(){return(_defesa);}
	int getDurability(){return(_durabilidade);}
	int getMagicLevel(){return(_nivelMagico);}
};
#endif