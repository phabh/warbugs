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
	Ponto *coordenada;//Posição do modelo no espaço
	int modelo;//ID do modelo 3D
	int textura3D;//Textura do modelo
	int textura2D;//Imagem pra colocar no inventario por exemplo.
	int animacao;//ID da animação corrente
	//qqr otra coisa necessária pela irrlicht
public:
	/*void initC3DObject(): 
	 inicializa as variáveis C3DObject com seus valores default
	 */
	void initC3DObject();

	/*void initC3DObject():
	 inicializa as variáveis C3DObject com os valores passados
	 
	 @param: valores a serem assumidos pelas variáveis C3DObject
	 */
	void initC3DObject(Ponto *posicao, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);

	/*void initC3DObject():
	 inicializa as variáveis C3DObject com os valores passados
	 
	 @param: valores a serem assumidos pelas variáveis C3DObject
	 */
	void initC3DObject(float x, float z, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);


	/*Ponto *getPosition():
	 retorna a posição do modelos 3D no espaço
	 
	 @return: posição X e Z do modelo no espaço. Retorna no formato da estrutura Ponto
	 */
	Ponto *getPosition();

	/*int getModel():
	 retorna o ID do modelo 3D
	 
	 @return: ID do modelo 3D
	 */
	int getModel();

	/*int get2DTexture():
	 retorna a textura 2D.
	 
	 @return: textura 2D
	 */
	int get2DTexture();

	/*int get3DTexture():
	 retorna a textura 3D de um modelo.
	 
	 @return: textura 3D de um modelo
	 */
	int get3DTexture();

	void setModel(int valor);
	void set2DTexture(int valor);
	void set3DTexture(int valor);
	void setPosition(float x, float z);
	void setPosition(Ponto *newPonto);
	//Métodos matemáticos
	float modulo(float valor);
	//Métodos 3D
	float getDistanceToPoint(Ponto *ponto);
};
#endif