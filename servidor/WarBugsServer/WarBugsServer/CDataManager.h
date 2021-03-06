#ifndef _DATABASEMANAGER_H_
#define _DATABASEMANAGER_H_

/*
	CDataManager
	Esta classe ter� 2 fun��es b�sicas:
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
	CPeopleList         * getPersonagemJogador(int idJogador);
	CPersonagem         * getPersonagemJogador(int idJogador, int idPersonagem);
	CPeopleList			* getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase);
	CPeopleList			* getPersonagem(int idTipoPersonagem, int idRaca, int idCenario);
	
	//Obter Itens
	CItem   * getItem(int id);
	CWeapon * getWeaponEquiped(int idPersonagem);
	CArmor  * getArmorEquiped(int idPersonagem);
	int       getIdRelacionalUltimoItem();

	//Obter Cenarios
	CCenarioList  * getListCenario();
	int				getCenarioId(int idPersonagem, int idJogador);
	int				getCenarioVilaId(Raca race);

	//Portal
	CPortal * getPortal(int idCenario, TypeDirecao direcao);

	//Obter Bolsa
	CBolsa      * getBolsaPersonagem(int idPersonagem);
	CBolsaList  * getListBolsa(int idCenario);
	CBolsa		* getBolsaDrop(int idPersonagem, int idTipoPersonagem, int idRaca, int qtdItensMaxima);
	CBolsa      * getBolsaInicialVendedor(int idPersonagem, int idTipoPersonagem, int idRaca, int qtdItensMaxima);

	//Obtem Jogador
	CJogador getJogador(char * login);

	//Obter Mercado
	void atualizaMercado();
	void atualizaVendedor(int idVendedor);
	
	//Login
	bool  doLogin(char * login, char * senha, CJogador & jogador);
	
	//Micelandia
	long  novoIdPersonagem();
	long  novoIdBolsas();
	long  novoIdItens();
	int   qtdPersonagemJogador(int idJogador);
	System::String ^ pointFormat(System::String ^ d1);
	void  getInformacaoVendedor(int idVendedor, System::Collections::ArrayList ^ capital, System::Collections::ArrayList ^ meta, System::Collections::ArrayList ^ tempo, System::Collections::ArrayList ^lua, System::DateTime periodoInicial, System::DateTime periodoFinal);
	bool  atualizaCoeficientesMercado(int Kr, int Kd, int Ko, int Kl, int Kt);
	void  getCoeficientesMercado(int &Kr, int &Kd, int &Ko, int &Kl, int &Kt);
	void  getDropItem(int idTipoPersonagem, int idRaca, TDadosBD ^ idItem, TDadosBD ^ chanceDrop);


	//ATUALIZA��ES
	//Personagem
	void updateItensPersonagem(CPersonagem * p1);
	void updatePersonagemJogador(CPersonagemJogador * p1);

	//Bolsa
	void updateBolsa(CBolsa * b1, int idCenario);

	//Inser��es
	bool insertPersonagemJogador(CPersonagemJogador * p1, int idJogador);
	CItem * relacionaItemPersonagem(int idPersonagem, int idItem);
	void insereItemRelacional(CItem * item, int idPersonagem, int iddeCenario);
	void insereItemRelacional(CItem * item, int idBolsa);

	//deletes
	bool deletePersonagemJogador(int idJogador, int idPersoangem, char * nomePersonagem);

	/*Backup*/
	void backupAll(CCenarioList * cenarioList);
};
#endif