/*
* Classe C3DObject
*
* Versão: 0.3
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
* Alterações: 
* 28/02/2009 - Criação da classe
*
*/
#ifndef _COBJECT
#include "CObject.cpp"
#endif

//Define a criação da classe
#define _C3DOBJECT

class C3DObject abstract : public CObject{
protected:
	//vector3df coordenada;
	//modelo
	//textura
	//qqr otra coisa necessária pela irrlicht

	//Métodos 3D

	//Métodos CObject
	virtual void inicializar(){
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};