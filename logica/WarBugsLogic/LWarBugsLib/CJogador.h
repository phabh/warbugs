#pragma once

#include "CBugSocket.h"
#include <iostream>
using namespace std;
#include "CWarBugObject.h"
#include "CPersonagemJogador.h"
#include "CCenario.h"

class CJogador : public CWarBugObject
{
private:
	char					_nome[20];
	char					_nascimento[10];
	char					_email[30];
	char					_login[15];
	char					_senha[15];
	CBugSocket *			_socket;
	CPersonagemJogador *	_personagem;
	CCenario *              _cenario;

public:

							CJogador();
	char *					getName();
	char *					getBirthdate();
	char *					getEmail();
	char *					getLogin();
	char *					getPassword();
	CBugSocket *			getSocket();
	CPersonagemJogador *	getCharacter();
	CCenario *              getScene();

	void					setName(char *value);
	void					setBirthdate(char *value);
	void					setEmail(char *value);
	void					setLogin(char *value);
	void					setPassword(char *value);
	void					setSocket(CBugSocket * socket);
	void					setCharacter(CPersonagemJogador * personagem);
	void					setScene(CCenario * cenario);
};
