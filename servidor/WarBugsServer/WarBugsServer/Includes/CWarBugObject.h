#pragma once
/*
* Classe CWarBugObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
*/

class CWarBugObject;

//Define a criação da classe
#ifndef _COBJECT_H_
#define _COBJECT_H_
#include<iostream>
using namespace std;
#include "Enumerators.h"
/*
Classe CObjectCount
Classe criada excluisivamente no intúito de contar a quantidade de objetos, podendo assim 
atribuir IDs diferentes e únicos aos mesmos
*/
class CObjectCount
{
private:
    int _objCount;//Contador de Objetos
	int *_buffer;//Buffer que armazena os IDs removidos
	int _bufferSize;//Tamanho do buffer
public:
	//Construtor do contador, apenas zera o inteiro objCont
	CObjectCount();
	/*int giveID(): 
	 incrementa o contador e retorna o valor que possuia no inicio do método
	 caso o buffer esteja vazio. Do contrário, retorna o primeiro id do buffer
	 
	 @return: valor de objCount antes de ser incrementado
	 */
	int giveID();
	/*int removeID(): 
	 remove um elemento do contador e armazena-o em um buffer
	 
	 @param: int ID: ID a ser removido e acrescentado ao buffer
	 */
	void removeID(int ID);
	/*int objectCount(): 
	 conta a quantidade atual de objetos criados
	 
	 @return: valor atual do contador
	 */
	int objectCount();
};
// -------------------------------------------------------------------------------------------------------------------
class CWarBugObject abstract
{
private:
	int _id;//ID único de um objeto
	int _sceneId;//ID único de um objeto em uma cena
public:
	/*int getID(): 
	 retorna o ID geral de um objeto
	 
	 @return: ID do objeto
	 */
	int getID();
	/*void setID()
	 modifica o ID do objeto para o valor dado
	 
	 @param: int newID: novo ID do objeto
	 */
	void setID(int newID);
	/*int getID(): 
	 retorna o ID de cena de um objeto
	 
	 @return: ID de cena do objeto
	 */
	int getSceneID();
	/*void setID()
	 modifica o ID de cena do objeto para o valor dado
	 
	 @param: int newID: novo ID de cena do objeto
	 */
	void setSceneID(int newID);
	//Irá atualizar o objeto em seu estado atual, variará drasticamente entre os tipos de objeto
	void update();
};
#endif