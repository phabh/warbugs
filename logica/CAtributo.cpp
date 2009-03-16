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

class CHabilidades : public CAtributo{
public:
	int forca;
	int agilidade;
	int destreza;
	int isntinto;
	int resistencia;
};

class CHabilidadesSecundarias : CAtributo {
public:
	int pv;//Pontos de vida
	int pm;//Pontos de magia
	int atqC;//Ataque Corpo-a-Corpo
	int atqD;//Ataque a disância
	int danoC;//Dano Corpo-a-Corpo
	int danoD;//Dano a distância
	int def;//Defesa
	int atRt;//Taxa de frequência de ataque
	int tc;//Tempo de carga

	CHabilidadesSecundarias(){
		pv = 0;
		pm = 0;
		atqC = 0;
		atqD = 0;
		danoC = 0;
		danoD = 0;
		def = 0;
		atRt = 0;
		tc = 0;
	}
	int generate(CHabilidades primarias){
		pv = primarias.resistencia * 5;
		pm = primarias.isntinto * 5;
		def = primarias.resistencia + (primarias.agilidade/2);
	}
};

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
	void addLoyalty(CLealdade bonus){
		aranha = aranha + bonus.aranha;
		besouro = besouro + bonus.besouro;
		escorpiao = escorpiao + bonus.escorpiao;
		louva = louva + bonus.louva;
		vespa = vespa + bonus.vespa;
	}
};

#endif