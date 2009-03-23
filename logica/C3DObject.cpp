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

#ifndef _C3DOBJECT

//Define a criação da classe
#define _C3DOBJECT
#include "CObject.cpp"

struct Ponto{
	int x;
	int y;
	int z;
};
// -------------------------------------------------------------------------------------------------------------------
class C3DObject abstract : public CObject{
protected:
	Ponto coordenada;
	int modelo;
	int textura3D;//Textura do modelo
	int textura2D;//Imagem pra colocar no inventario por exemplo.
	//qqr otra coisa necessária pela irrlicht

	//Métodos 3D

	//Métodos CObject
	virtual void initialize(CObjectCount *counter){
		CObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};
#endif