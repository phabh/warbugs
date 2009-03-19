/*
* Classe CAtributo
*
* Versão: 0.01
*
* Autor: Eder Figueiredo
*
* Objetivo: Descrever todos os atributos de um personagem
*
*/

#include "CLogicObject.cpp"

#ifndef _CATRIBUTO
#define _CATRIBUTO

class CAtributo : public CLogicObject{
};
// -------------------------------------------------------------------------------------------------------------------
class CHabilidades : public CAtributo{
public:
	int forca;
	int agilidade;
	int destreza;
	int isntinto;
	int resistencia;
};
// -------------------------------------------------------------------------------------------------------------------
class CHabilidadesSecundarias : CAtributo {
private:
	int _pv;//Pontos de vida
	int _pm;//Pontos de magia
	int _atqC;//Ataque Corpo-a-Corpo
	int _atqD;//Ataque a disância
	int _danoC;//Dano Corpo-a-Corpo
	int _danoD;//Dano a distância
	int _def;//Defesa
	int _atRt;//Taxa de frequência de ataque
	int _tc;//Tempo de carga

public:
	CHabilidadesSecundarias(){
		_pv = 0;
		_pm = 0;
		_atqC = 0;
		_atqD = 0;
		_danoC = 0;
		_danoD = 0;
		_def = 0;
		_atRt = 0;
		_tc = 0;
	}
	int generate(CHabilidades *primarias){
		_pv = primarias->resistencia * 5;
		_pm = primarias->isntinto * 5;
		_def = primarias->resistencia + (primarias->agilidade/2);
	}
	int getPV(){return(_pv);}
	int getPM(){return(_pm);}
	int getMeleeAttack(){return(_atqC);}
	int getRangedAttack(){return(_atqD);}
	int getMeleeDamage(){return(_danoC);}
	int getRangedDamage(){return(_danoD);}
	int getDefense(){return(_def);}
	int getAttackRate(){return(_atRt);}
	int getChargeTime(){return(_tc);}
};
// -------------------------------------------------------------------------------------------------------------------
class CLealdade : CAtributo {
public:
	int aranha;
	int besouro;
	int escorpiao;
	int louva;//Louva-a-Deus
	int vespa;

	CLealdade(){
		aranha =
		besouro =
		escorpiao =
		louva = 
		vespa = 0;
	}
	void addLoyalty(CLealdade *bonus){
		aranha = aranha + bonus->aranha;
		besouro = besouro + bonus->besouro;
		escorpiao = escorpiao + bonus->escorpiao;
		louva = louva + bonus->louva;
		vespa = vespa + bonus->vespa;
	}
};

#endif