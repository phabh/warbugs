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
C3DObject::C3DObject(float x, float z, int modeloID, int textura3DID, int animacaoID, int textura2DID)
{
	coordenada->x = x;
	coordenada->z = z;
	modelo = modeloID;
	textura2D = textura2DID;
	textura3D = textura3DID;
	animacao = animacaoID;
}
Ponto *C3DObject::getPosition()
{
	return(coordenada);
}
int C3DObject::getModel()
{
	return(modelo);
}
int C3DObject::get2DTexture()
{
	return(textura2D);
}
int C3DObject::get3DTexture()
{
	return(textura3D);
}


void C3DObject::setModel(int valor)
{
	modelo = valor;
}
void C3DObject::set2DTexture(int valor)
{
	textura2D = valor;
}
void C3DObject::set3DTexture(int valor)
{
	textura3D = valor;
}
void C3DObject::setPosition(float x, float z)
{
	coordenada->x = x;
	coordenada->z = z;
}
void C3DObject::setPosition(Ponto *newPonto)
{
	coordenada->x = newPonto->x;
	coordenada->z = newPonto->z;
}
//Métodos matemáticos
float C3DObject::modulo(float valor)
{
	if (valor < 0)
	{
		valor = valor*(-1);
	}
	return (valor);
}
//Métodos 3D
float C3DObject::getDistanceToPoint(Ponto *ponto)
{
	return(modulo(coordenada->x - ponto->x) + modulo(coordenada->z - ponto->z));
}
//Métodos CObject
#endif