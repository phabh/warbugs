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
	CPeopleList			* getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase);
	CPeopleList			  getPersonagem(int idTipoPersonagem, int idRaca);
	CPeopleList			* getPersonagem(int idTipoPersonagem, int idRaca, int idCenario);
	
	//Obter Itens
	CItem   * getItem(int id);
	CWeapon * getWeaponEquiped(int idPersonagem);
	CArmor  * getArmorEquiped(int idPersonagem);

	//Obter Cenarios
	CCenarioList  * getListCenario();
	int				getCenarioId(int idPersonagem, int idJogador);
	int				getCenarioId(Raca race);

	//Portal
	CPortal * getPortal(int idCenario, TypeDirecao direcao);

	//Obter Bolsa
	CBolsa      * getBolsa(int id);
	CBolsa      * getBolsaPersonagem(int idPersonagem);
	CBolsa      * getItensInimigo(int idInimigo);
	CBolsa      * getItensNPC(int idNPC);
	CBolsa      * getItensVendedor(int idVendedor);
	CBolsaList  * getListBolsa(int idCenario);

	//Obtem Jogador
	CJogador getJogador(char * login);
	
	//Login
	bool  doLogin(char * login, char * senha, CJogador & jogador);
	
	//Micelandia
	long  novoIdPersonagem();
	long  novoIdBolsas();
	long  novoIdItens();
	int   qtdPersonagemJogador(int idJogador);
	System::String ^ pointFormat(System::String ^ d1);


	//ATUALIZAÇÕES
	//Personagem
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, int nivel, int xp);
	void updatePersonagem(CPersonagem * p1);
	void updatePersonagemJogador(CPersonagemJogador * p1);

	//Bolsa
	void updateBolsa(CBolsa * b1, int idCenario);

	//Inserções
	bool insertPersonagemJogador(CPersonagemJogador * p1, int idJogador);
	void insertPersonagem(CPeopleList p1);
	CItem * relacionaItemPersonagem(int idPersonagem, int idItem);
	void insereItemRelacional(CItem * item, int idPersonagem, int iddeCenario);
	void insereItemRelacional(CItem * item, int idBolsa);

	//deletes
	bool deletePersonagemJogador(int idJogador, int idPersoangem, char * nomePersonagem);

	/*Backup*/
	void backupAll(CCenarioList * cenarioList);
};
#endif