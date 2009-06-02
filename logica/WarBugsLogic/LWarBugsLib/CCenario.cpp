#include "CCenario.h"

CCenario::CCenario(int ID, 
				   CPeopleList *players, 
				   CPeopleList *monsters,
				   CPeopleList *npcs,
				   CPeopleList *vendedores,
				   CBolsaList *bolsa,
				   CPortal *saidaNorte,
				   CPortal *saidaSul,
				   CPortal *saidaLeft,
				   CPortal *saidaRight)
{
	_contador = new CObjectCount();
	this->setID(ID);
	_jogadores = players;//Lista de personagens
	_inimigos = monsters;
	_npcs = npcs;
	_itens = bolsa;
	_vendedores = vendedores;
	_saidaNorte = saidaNorte;
	_saidaSul = saidaSul;
	_saidaLeft = saidaLeft;
	_saidaRight = saidaRight;

	if(!_jogadores->isEmpty())
	{
		for(int i = 0; i < _jogadores->size(); i=i+1)
		{
			((CPersonagemJogador*)(_jogadores->getElementAt(i)))->setScene(this);
		}
	}
	if(!_inimigos->isEmpty())
	{
		for(int i = 0; i < _inimigos->size(); i=i+1)
		{
			((CInimigo*)(_inimigos->getElementAt(i)))->setScene(this);
		}
	}
	if(!_npcs->isEmpty())
	{
		for(int i = 0; i < _npcs->size(); i=i+1)
		{
			((CNPC*)(_npcs->getElementAt(i)))->setScene(this);
		}
	}
	if(!_vendedores->isEmpty())
	{
		for(int i = 0; i < _vendedores->size(); i=i+1)
		{
			((CVendedor*)(_vendedores->getElementAt(i)))->setScene(this);
		}
	}
}
void CCenario::enterScene()
{
}
int CCenario::playerCount()
{
	return(_jogadores->size());
}
int CCenario::itemCount()
{
	return(_itens->size());
}
int CCenario::monsterCount()
{
	return(_inimigos->size());
}
int CCenario::NPCCount()
{
	return(_npcs->size());
}
int CCenario::salesmanCount()
{
	return(_vendedores->size());
}
//
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
CVendedor *CCenario::getSalesman(int idVendedor)
{
	return((CVendedor*)_vendedores->getPersonagem(idVendedor));
}
CPersonagemJogador *CCenario::getPlayerAt(int pos)
{
	return((CPersonagemJogador*)_jogadores->getElementAt(pos));
}
CInimigo *CCenario::getMonsterAt(int pos)
{
	return((CInimigo*)_inimigos->getElementAt(pos));
}
CNPC *CCenario::getNpcAt(int pos)
{
	return((CNPC*)_npcs->getElementAt(pos));
}
CBolsa *CCenario::getBagAt(int pos)
{
	return (_itens->getElementAt(pos));
}
CVendedor *CCenario::getSalesmanAt(int idVendedor)
{
	return((CVendedor*)_vendedores->getElementAt(idVendedor));
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

//
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
//
void CCenario::addPlayer(CPersonagem *jogador)
{
	jogador->setSceneID(_contador->giveID());
	_jogadores->addPersonagem(jogador);
	((CPersonagemJogador*)jogador)->setScene(this);
}
void CCenario::addMonster(CPersonagem *inimigo)
{
	inimigo->setSceneID(_contador->giveID());
	_inimigos->addPersonagem(inimigo);
	((CInimigo*)inimigo)->setScene(this);
}
void CCenario::addNpc(CPersonagem *npc)
{
	npc->setSceneID(_contador->giveID());
	_npcs->addPersonagem(npc);
	((CNPC*)npc)->setScene(this);
}
void CCenario::addBag(CBolsa *bolsa)
{
	bolsa->setSceneID(_contador->giveID());
	_itens->addBag(bolsa);
}
void CCenario::addSalesman(CVendedor *vendedor)
{
	vendedor->setSceneID(_contador->giveID());
	_vendedores->addPersonagem(vendedor);
	((CVendedor*)vendedor)->setScene(this);
}
//
CPersonagemJogador *CCenario::removePlayer(int idJogador)
{
	CPersonagemJogador *temp = (CPersonagemJogador*)_jogadores->removePersonagem(idJogador);
	_contador->removeID(temp->getSceneID());
	return(temp);
}
CInimigo *CCenario::removeMonster(int idInimigo)
{
	CInimigo *temp = (CInimigo*)_jogadores->removePersonagem(idInimigo);
	_contador->removeID(temp->getSceneID());
	return(temp);
	//return((CInimigo*)_inimigos->removePersonagem(idInimigo));
}
CNPC *CCenario::removeNPC(int idNPC)
{
	CNPC *temp = (CNPC*)_jogadores->removePersonagem(idNPC);
	_contador->removeID(temp->getSceneID());
	return(temp);
	//return((CNPC*)_npcs->removePersonagem(idNPC));
}
CBolsa *CCenario::removeBag(int idBag)
{
	CBolsa *temp = (CBolsa*)_itens->removeBolsa(idBag);
	_contador->removeID(temp->getSceneID());
	return(temp);
	//return((CBolsa*)_itens->removeBolsa(idBag));
}
CVendedor *CCenario::removeSalesman(int idVendedor)
{
	CVendedor *temp = (CVendedor*)_vendedores->removePersonagem(idVendedor);
	_contador->removeID(temp->getSceneID());
	return(temp);
	//return((CVendedor*)_vendedores->removePersonagem(idVendedor));
}
void CCenario::update()
{
	for(int i = 0; i < max(max(_jogadores->size(), _vendedores->size()) , max(_inimigos->size(), _npcs->size())); i=i+1)
	{
		if(i < _inimigos->size())	getMonsterAt(i)->update();
		if(i < _jogadores->size())  getPlayerAt(i)->update();
		if(i < _npcs->size())		getNpcAt(i)->update();
		if(i < _vendedores->size())	getSalesmanAt(i)->update();
	}
}