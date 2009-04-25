/*
* Classe C3DObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/
#ifndef _C3DOBJECT_CPP_
//Define a criação da classe
#define _C3DOBJECT_CPP_

#include "C3DObject.h"

C3DObject::C3DObject()
{
	coordenada = NULL;
	modelo = -1;
	textura2D = -1;
	textura3D = -1;
	animacao = -1;
}
C3DObject::C3DObject(Ponto *posicao, int modeloID, int textura3DID, int animacaoID, int textura2DID)
{
	coordenada = posicao;
	modelo = modeloID;
	textura2D = textura2DID;
	textura3D = textura3DID;
	animacao = animacaoID;
}
C3DObject::C3DObject(int x, int y, int modeloID, int textura3DID, int animacaoID, int textura2DID)
{
	coordenada->x = x;
	coordenada->y = y;
	modelo = modeloID;
	textura2D = textura2DID;
	textura3D = textura3DID;
	animacao = animacaoID;
}
Ponto *C3DObject::getPosition()
{
	return(coordenada);
}
void C3DObject::setPosition(int x, int y)
{
	coordenada->x = x;
	coordenada->y = y;
}
void C3DObject::setPosition(Ponto *newPonto)
{
	coordenada->x = newPonto->x;
	coordenada->y = newPonto->y;
}
//Métodos matemáticos
int C3DObject::modulo(int valor)
{
	if (valor < 0)
	{
		valor = valor*(-1);
	}
	return (valor);
}
//Métodos 3D
int C3DObject::getDistanceToPoint(Ponto *ponto)
{
	return(modulo(coordenada->x - ponto->x) + modulo(coordenada->y - ponto->y));
}
//Métodos CObject
#endif