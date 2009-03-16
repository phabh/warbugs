/*
* Classe C3DObject
*
* Versão: 0.3
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/
#include "CObject.cpp"

#ifndef _C3DOBJECT

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
	virtual void initialize(CObjectCount &counter){
		CObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};
#endif