/*
	CDataManager
	Esta classe terá 2 funções básicas:
		- pegar os dados direto do banco de dados e retorna-los como objetos preenchidos
		- salvar os dados no Banco de dados;
*/
#pragma once

#include "CDataBase.h"
#include "CPersonagem.h"

class CDataManger
{
private:
	CDataBase * _dataBase

public:
	CDataManager(CDataBase * db);

	//CONSULTAS
	//Obter persoangens
	CPersonagem getPersonagem(int id);
	CPersonagem getPersonagem(int idJogador);
	CPersonagem getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase);
	
	//Obter Itens
	CItem getItem(int id);
	CItem getItem(int Tipo);

	//Obter Cenarios
	CCenario getCenario(int id);

	//Obtem Jogador
	CJogador getJogador(int id);
	CJogador getJogador(char * login);
	
	//Login
	bool  doLogin(char * login, char * senha, CJogador * jogador);
	
	//Micelandia
	long  numPersonagens();
	long  numBolsas();
	long  numItens();

	//ATUALIZAÇÕES
	//Personagem
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, int nivel, int xp);
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, float posX, float posZ);
	void updatePersonagem(int id, float posX, float posZ);
	

};