#include "CJogador.h"

CJogador::CJogador(void)
{
	next = NULL;
}
int CJogador::getID()
{
	return(_ID);
}
char *CJogador::getName()
{
	return(_nome);
}
char *CJogador::getBirthdate()
{
	return(_nascimento);
}
char *CJogador::getEmail()
{
	return(_email);
}
char *CJogador::getLogin()
{
	return(_login);
}
char *CJogador::getPassword()
{
	return(_senha);
}
sockaddr *CJogador::getSocketAddress()
{
	return(_socket);
}
void CJogador::setID(int newID)
{
	_ID = newID;
}
void CJogador::setName(char *value)
{
	if(sizeof(_nome) >= strlen(value))
	{
		strcpy_s(_nome, value);
	}
}
void CJogador::setBirthdate(char *value)
{
	if(sizeof(_nascimento) >= strlen(value))
	{
		strcpy_s(_nascimento, value);
	}
}
void CJogador::setEmail(char *value)
{
	if(sizeof(_email) >= strlen(value))
	{
		strcpy_s(_email, value);
	}
}
void CJogador::setLogin(char *value)
{
	if(sizeof(_login) >= strlen(value))
	{
		strcpy_s(_login, value);
	}
}
void CJogador::setPassword(char *value)
{
	if(sizeof(_senha) >= strlen(value))
	{
		strcpy_s(_senha, value);
	}
}
void CJogador::setSocketAddress(sockaddr *socket)
{
	_socket = socket;
}