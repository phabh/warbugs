#pragma once
/*
* Classe CObject
*
* Vers�o: 0.5
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
*/

class CWarBugObject;

//Define a cria��o da classe
#ifndef _COBJECT_H_
#define _COBJECT_H_
#include<iostream>
using namespace std;
#include "Enumerators.h"
/*
Classe CObjectCount
Classe criada excluisivamente no intuito de contar a quantidade de objetos, podendo assim 
atribuir IDs diferentes e �nicos aos mesmos
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
	 *incrementa o contador e retorna o valor que possuia no inicio do m�todo
	 *caso o buffer esteja vazio. Do contr�rio, retorna o primeiro id do buffer
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
	int _id;//ID �nico de um objeto
	int _sceneId;//ID �nico de um objeto em uma cena
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
	 *inicializa o objeto, dando para ele um ID �nico e incrementando o contador de objetos
	 *
	 *@param: CObjectCount &counter: contador de objetos que ir� gerar o ID
	 *        OBS: - CRIAR APENS UM CONTADOR DURANTE TODO O PROGRAMA, CASO CONTR�RIO OS IDs N�O SER�O MAIS �NICOS
	 */
	void initialize(CObjectCount *counter);
	/* Retorna um valor citado no enum TipoClasse
	 * AVISOS COM RELA��O AO GETCLASS:
	 * 1- TODA CLASSE DEVER� SER CADASTRADA NO ENUM TipoCLasse, COM EXCE��O DA CObjectCount.
	 * 2- TODA CLASSE CADASTRADA NO ENUM DEVER� TER O M�TODO REIMPLEMENTADO EM SUA DEFINI��O, PARA QUE POSSA SER USADO
	 * Carrega informa��es do Banco de Dados
	 * NECESSITA DE IMPLEMENTA��O DA PARTE DE COMUNICA��O E DEFINI��O DO PROTOCOLO DE COMUNICA��O
	 */
	TipoClasse getClass();
	//Ir� carregar as informa��es necess�rias para preencher os atributos dos objetos
	void loadDBData();
	//Ir� atualizar o objeto em seu estado atual, variar� drasticamente entre os tipos de objeto
	void update();
};
#endif