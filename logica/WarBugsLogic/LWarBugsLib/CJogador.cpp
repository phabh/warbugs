#include "CJogador.h"

CJogador::CJogador(void)
{
	setID(-1);
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
CBugSocket * CJogador::getSocket()
{
	return(_socket);
}
CPersonagemJogador *CJogador::getCharacter()
{
	return(_personagem);
}
CCenario * CJogador::getScene()
{
	return(_cenario);
}
bool CJogador::isPlaying()
{
	return(_isPlaying);
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
void CJogador::setSocket(CBugSocket *socket)
{
	_socket = socket;
}
void CJogador::setCharacter(CPersonagemJogador *personagem)
{
	_personagem = personagem;
}
void CJogador::setScene(CCenario * cenario)
{
	_cenario = cenario;
}
void CJogador::setPlaying(bool isplaying)
{
	_isPlaying = isplaying;
}
long CJogador::getBeginTimePing()
{
	return(_TempoEnvioPing);
}
void CJogador::setBeginTimePing(long newTime)
{
	_TempoEnvioPing = newTime;
}
long CJogador::getEndTimePing()
{
	return(_TempoRespostaPing);
}
void CJogador::setEndTimePing(long newTime)
{
	_TempoRespostaPing = newTime;
}
