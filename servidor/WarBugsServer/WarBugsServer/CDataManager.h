#ifndef _DATABASEMANAGER_H_
#define _DATABASEMANAGER_H_

/*
	CDataManager
	Esta classe terá 2 funções básicas:
		- pegar os dados direto do banco de dados e retorna-los como objetos preenchidos
		- salvar os dados no Banco de dados;
*/


#include "CDataBase.h"

#pragma comment (lib,"Libs\\LWarBugsLib.lib")
#pragma message ("WarBugs Library")

#include <CPersonagem.h>
#include <CItem.h>
#include <CBolsa.h>
#include <CBolsaList.h>
#include <CCenario.h>
#include <CPeopleList.h>
#include <CJogador.h>
#include <CCenarioList.h>

class CDataManager
{
private:
	CDataBase * _dataBase;

public:
	CDataManager(CDataBase * db);

	//CONSULTAS
	//Obter persoangens
	CPersonagem			* getPersonagem(int id);
	CPeopleList           getPersonagemJogador(int idJogador);
	CPeopleList			  getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase);
	CPeopleList			  getPersonagem(int idTipoPersonagem, int idRaca);
	CPeopleList			* getPersonagem(int idTipoPersonagem, int idRaca, int idCenario);
	
	//Obter Itens
	CItem   * getItem(int id);
	CWeapon * getWeaponEquiped(int idPersonagem);
	CArmor  * getArmorEquiped(int idPersonagem);

	//Obter Cenarios
	CCenarioList * getListCenario();

	//Portal
	CPortal * getPortal(int idCenario, Direcoes direcao);

	//Obter Bolsa
	CBolsa      * getBolsa(int id);
	CBolsa		  getBolsaPersonagem(int idPersonagem);
	CBolsa		  getBolsaTipoItem(int Tipo);
	CBolsaList  * getListBolsa(int idCenario);

	//Obtem Jogador
	CJogador getJogador(char * login);
	
	//Login
	bool  doLogin(char * login, char * senha, CJogador & jogador);
	
	//Micelandia
	long  numPersonagens();
	long  numBolsas();
	long  numItens();
	int   qtdPersonagemJogador(int idJogador);
	System::String ^ pointFormat(System::String ^ d1);


	//ATUALIZAÇÕES
	//Personagem
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, int nivel, int xp);

	//Inserções
	bool insertPersonagemJogador(CPersonagemJogador * p1, int idJogador);
	void insertPersonagem(CPeopleList p1);

	//deletes
	bool deletePersonagemJogador(int idJogador, int idPersoangem, char * nomePersonagem);
};
#endif