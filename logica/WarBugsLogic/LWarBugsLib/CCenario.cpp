#include "CCenario.h"

CCenario::CCenario(int ID, 
				   CPeopleList *players, 
				   CPeopleList *monsters,
				   CPeopleList *npcs,
				   CBolsaList *bolsa,
				   CPortal *saidaNorte,
				   CPortal *saidaSul,
				   CPortal *saidaLeft,
				   CPortal *saidaRight)
{
	this->setID(ID);
	_jogadores = players;//Lista de personagens
	_inimigos = monsters;
	_npcs = npcs;
	_itens = bolsa;
	_saidaNorte = saidaNorte;
	_saidaSul = saidaSul;
	_saidaLeft = saidaLeft;
	_saidaRight = saidaRight;
}
void CCenario::enterScene()
{
}
int CCenario::personagemCount()
{
	return(_jogadores->size());
}
int CCenario::itemCount()
{
	return(_itens->size());
}
CPersonagemJogador *CCenario::getPlayer(int idJogador)
{
	return((CPersonagemJogador*)_jogadores->getPersonagem(idJogador));
}
CInimigo *CCenario::getMonster(int idInimigo)
{
	return((CInimigo*)_inimigos->getPersonagem(idInimigo));
}
CNPC *CCenario::getNpc(int idNpc)
{
	return((CNPC*)_npcs->getPersonagem(idNpc));
}
CBolsa *CCenario::getBag(int idBag)
{
	return (_itens->getBolsa(idBag));
}
	
CPortal *CCenario::getExit(Direcoes idPortal)
{
	switch(idPortal)
	{
	case NORTE:
		return(_saidaNorte);
	case SUL:
		return(_saidaSul);
	case LESTE:
		return(_saidaRight);
	case OESTE:
		return(_saidaLeft);
	}
	return(NULL);
}
void CCenario::setExit(CPortal *newExit, Direcoes idPortal)
{
	switch(idPortal)
	{
	case NORTE:
		_saidaNorte = newExit;
		break;
	case SUL:
		_saidaSul = newExit;
		break;
	case LESTE:
		_saidaRight = newExit;
		break;
	case OESTE:
		_saidaLeft = newExit;
		break;
	}
}
void CCenario::addPlayer(CPersonagem *jogador)
{
	_jogadores->addPersonagem(jogador);
}
void CCenario::addMonster(CPersonagem *inimigo)
{
	_inimigos->addPersonagem(inimigo);
}
void CCenario::addNpc(CPersonagem *npc)
{
	_npcs->addPersonagem(npc);
}
CPersonagemJogador *CCenario::removePlayer(int idJogador)
{
	return((CPersonagemJogador*)_jogadores->removePersonagem(idJogador));
}
CInimigo *CCenario::removeMonster(int idInimigo)
{
	return((CInimigo*)_inimigos->removePersonagem(idInimigo));
}
CNPC *CCenario::removeNPC(int idNPC)
{
	return((CNPC*)_npcs->removePersonagem(idNPC));
}