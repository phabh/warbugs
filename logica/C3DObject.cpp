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

#ifndef _C3DOBJECT

//Define a cria��o da classe
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
	//qqr otra coisa necess�ria pela irrlicht

	//M�todos 3D

	//M�todos CObject
	virtual void initialize(CObjectCount *counter){
		CObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};
#endif