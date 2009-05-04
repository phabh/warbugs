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
//Define a criação da classe
#define _C3DOBJECT_H_

#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CWarBugObject.h"


// -------------------------------------------------------------------------------------------------------------------
class C3DObject abstract : public CWarBugObject
{
protected:
	Ponto *coordenada;
	int modelo;
	int textura3D;//Textura do modelo
	int textura2D;//Imagem pra colocar no inventario por exemplo.
	int animacao;//ID da animação corrente
	//qqr otra coisa necessária pela irrlicht
public:
	C3DObject();
	C3DObject(Ponto *posicao, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);
	C3DObject(int x, int y, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);
	//Getters e Setters
	Ponto *getPosition();
	void setPosition(int x, int y);
	void setPosition(Ponto *newPonto);
	//Métodos matemáticos
	int modulo(int valor);
	//Métodos 3D
	int getDistanceToPoint(Ponto *ponto);
	//Métodos CObject
};
#endif