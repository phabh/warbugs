#pragma once
/*
* Classe C3DObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/


#ifndef _C3DOBJECT_H_
//Define a cria��o da classe
#define _C3DOBJECT_H_

#include "CWarBugObject.h"

struct Ponto{
	int x;
	int y;
};
// -------------------------------------------------------------------------------------------------------------------
class C3DObject abstract : public CWarBugObject
{
protected:
	Ponto coordenada;
	int modelo;
	int textura3D;//Textura do modelo
	int textura2D;//Imagem pra colocar no inventario por exemplo.
	//qqr otra coisa necess�ria pela irrlicht
public:
	C3DObject();
	//Getters e Setters
	Ponto getPosition();
	void setPosition(int x, int y);
	void setPosition(Ponto newPonto);
	//M�todos matem�ticos
	int modulo(int valor);
	//M�todos 3D
	int getDistanceToPoint(Ponto ponto);
	//M�todos CObject
};
#endif