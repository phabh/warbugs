/*
* Classe C3DObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes 3D
*
*/
#include "CObject.cpp"
#include <math.h>
#ifndef _C3DOBJECT

//Define a criação da classe
#define _C3DOBJECT


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
public:
	//Getters e Setters
	Ponto getPosition()
	{
		return(coordenada);
	}
	void setPosition(int x, int y, int z)
	{
		coordenada.x = x;
		coordenada.y = y;
		coordenada.z = z;
	}
	void setPosition(Ponto newPonto)
	{
		coordenada.x = newPonto.x;
		coordenada.y = newPonto.y;
		coordenada.z = newPonto.z;
	}
	//Métodos 3D
	double getDistanceToPoint(Ponto ponto)
	{
		return(sqrt(pow(((double)(coordenada.x - ponto.x)),2)+pow(((double)(coordenada.y - ponto.y)),2)+pow(((double)(coordenada.z - ponto.z)),2)));
	}

	//Métodos CObject
	virtual void initialize(CObjectCount *counter){
		CObject::initialize(counter);
	}
	virtual TipoClasse getClass(){
		return(C3DOBJECT);
	}
};
#endif