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
	Ponto *coordenada;//Posi��o do modelo no espa�o
	int modelo;//ID do modelo 3D
	int textura3D;//Textura do modelo
	int textura2D;//Imagem pra colocar no inventario por exemplo.
	int animacao;//ID da anima��o corrente
	//qqr otra coisa necess�ria pela irrlicht
public:
	/*void initC3DObject(): 
	 inicializa as vari�veis C3DObject com seus valores default
	 */
	void initC3DObject();

	/*void initC3DObject():
	 inicializa as vari�veis C3DObject com os valores passados
	 
	 @param: valores a serem assumidos pelas vari�veis C3DObject
	 */
	void initC3DObject(Ponto *posicao, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);

	/*void initC3DObject():
	 inicializa as vari�veis C3DObject com os valores passados
	 
	 @param: valores a serem assumidos pelas vari�veis C3DObject
	 */
	void initC3DObject(float x, float z, int modeloID = -1, int textura3DID = -1, int animacaoID = -1, int textura2DID = -1);


	/*Ponto *getPosition():
	 retorna a posi��o do modelos 3D no espa�o
	 
	 @return: posi��o X e Z do modelo no espa�o. Retorna no formato da estrutura Ponto
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
	//M�todos matem�ticos
	float modulo(float valor);
	//M�todos 3D
	float getDistanceToPoint(Ponto *ponto);
};
#endif