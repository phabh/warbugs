/*
* Classe C3DObject
*
* Vers�o: 0.3
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/
#include "CObject.cpp"

#ifndef _C3DOBJECT

//Define a cria��o da classe
#define _C3DOBJECT

class C3DObject abstract : public CObject{
protected:
	//vector3df coordenada;
	//modelo
	//textura
	//qqr otra coisa necess�ria pela irrlicht

	//M�todos 3D

	//M�todos CObject
	virtual void initialize(CObjectCount &counter){
		CObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};
#endif