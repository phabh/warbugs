#pragma once
/*
* Classe CObject
*
* Versão: 0.5
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
Classe criada excluisivamente no intuito de contar a quantidade de objetos, podendo assim 
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
	/*int giveID()
	 *incrementa o contador e retorna o valor que possuia no inicio do método
	 *caso o buffer esteja vazio. Do contrário, retorna o primeiro id do buffer
	 *
	 *@return: valor de objCount antes de ser incrementado
	 */
	int giveID();
	/*int removeID()
	 *remove um elemento do contador e armazena-o em um buffer
	 *
	 *@param: int ID: ID a ser removido e acrescentado ao buffer
	 */
	void removeID(int ID);
	/*int objectCount()
	 *conta a quantidade atual de objetos criados
	 *
	 *@return: valor atual do contador
	 */
	int objectCount();
};
// -------------------------------------------------------------------------------------------------------------------
class CWarBugObject abstract
{
private:
	int _id;//ID único de um objeto
	int _sceneId;//ID único de um objeto em uma cena
	int *_idBuffer;
public:
	CWarBugObject();
public:
	int getID();
	void setID(int newID);
	int getSceneID();
	void setSceneID(int newID);
protected:
	/*void initialize(CObjectCount &counter)
	 *inicializa o objeto, dando para ele um ID único e incrementando o contador de objetos
	 *
	 *@param: CObjectCount &counter: contador de objetos que irá gerar o ID
	 *        OBS: - CRIAR APENS UM CONTADOR DURANTE TODO O PROGRAMA, CASO CONTRÁRIO OS IDs NÃO SERÃO MAIS ÚNICOS
	 */
	void initialize(CObjectCount *counter);
	/* Retorna um valor citado no enum TipoClasse
	 * AVISOS COM RELAÇÃO AO GETCLASS:
	 * 1- TODA CLASSE DEVERÁ SER CADASTRADA NO ENUM TipoCLasse, COM EXCEÇÃO DA CObjectCount.
	 * 2- TODA CLASSE CADASTRADA NO ENUM DEVERÁ TER O MÉTODO REIMPLEMENTADO EM SUA DEFINIÇÃO, PARA QUE POSSA SER USADO
	 * Carrega informações do Banco de Dados
	 * NECESSITA DE IMPLEMENTAÇÃO DA PARTE DE COMUNICAÇÃO E DEFINIÇÃO DO PROTOCOLO DE COMUNICAÇÃO
	 */
	TipoClasse getClass();
	//Irá carregar as informações necessárias para preencher os atributos dos objetos
	void loadDBData();
	//Irá atualizar o objeto em seu estado atual, variará drasticamente entre os tipos de objeto
	void update();
};
#endif