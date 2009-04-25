#pragma once

#pragma comment (lib,"ws2_32.lib")
#pragma message ("Auto linking WinSock2 library")
#include <winsock2.h>
#include <iostream>
using namespace std;

class CJogador
{
private:
	int _ID;
	char _nome[20];
	char _nascimento[10];
	char _email[30];
	char _login[15];
	char _senha[15];
	sockaddr *_socket;

public:
	CJogador *next;

	CJogador();
	int getID();
	char *getName();
	char *getBirthdate();
	char *getEmail();
	char *getLogin();
	char *getPassword();
	sockaddr *getSocketAddress();
	void setID(int newID);
	void setName(char *value);
	void setBirthdate(char *value);
	void setEmail(char *value);
	void setLogin(char *value);
	void setPassword(char *value);
	void setSocketAddress(sockaddr *socket);
};
