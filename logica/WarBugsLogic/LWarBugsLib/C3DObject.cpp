/*
* Classe C3DObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/
#ifndef _C3DOBJECT_CPP_
//Define a cria��o da classe
#define _C3DOBJECT_CPP_

#include "C3DObject.h"

C3DObject::C3DObject(){}
	Ponto C3DObject::getPosition()
	{
		return(coordenada);
	}
	void C3DObject::setPosition(int x, int y)
	{
		coordenada.x = x;
		coordenada.y = y;
	}
	void C3DObject::setPosition(Ponto newPonto)
	{
		coordenada.x = newPonto.x;
		coordenada.y = newPonto.y;
	}
	//M�todos matem�ticos
	int C3DObject::modulo(int valor)
	{
		if (valor < 0)
		{
			valor = valor*(-1);
		}
		return (valor);
	}
	//M�todos 3D
	int C3DObject::getDistanceToPoint(Ponto ponto)
	{
		return(modulo(coordenada.x - ponto.x) + modulo(coordenada.y - ponto.y));
	}

	//M�todos CObject
#endif