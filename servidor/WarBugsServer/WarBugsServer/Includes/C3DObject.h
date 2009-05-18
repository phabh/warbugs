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
	int animacao;//ID da anima��o corrente
	//qqr otra coisa necess�ria pela irrlicht
public:
	C3DObject();
	C3DObject(Ponto *posicao, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);
	C3DObject(float x, float z, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);
	//Getters e Setters
	Ponto *getPosition();
	int getModel();
	int get2DTexture();
	int get3DTexture();

	void setModel(int valor);
	void set2DTexture(int valor);
	void set3DTexture(int valor);
	void setPosition(float x, float z);
	void setPosition(Ponto *newPonto);
	//M�todos matem�ticos
	float modulo(float valor);
	//M�todos 3D
	float getDistanceToPoint(Ponto *ponto);
	//M�todos CObject
};
#endif