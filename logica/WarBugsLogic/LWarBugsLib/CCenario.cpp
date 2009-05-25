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
CVendedor *CCenario::getVendedor(int idVendedor)
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
CVendedor *CCenario::getVendedorAt(int idVendedor)
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
}
void CCenario::addMonster(CPersonagem *inimigo)
{
	inimigo->setSceneID(_contador->giveID());
	_inimigos->addPersonagem(inimigo);
}
void CCenario::addNpc(CPersonagem *npc)
{
	npc->setSceneID(_contador->giveID());
	_npcs->addPersonagem(npc);
}
void CCenario::addBag(CBolsa *bolsa)
{
	bolsa->setSceneID(_contador->giveID());
	_itens->addBag(bolsa);
}
void CCenario::addVendedor(CVendedor *vendedor)
{
	vendedor->setSceneID(_contador->giveID());
	_vendedores->addPersonagem(vendedor);
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
CVendedor *CCenario::removeVendedor(int idVendedor)
{
	CVendedor *temp = (CVendedor*)_jogadores->removePersonagem(idVendedor);
	_contador->removeID(temp->getSceneID());
	return(temp);
	//return((CVendedor*)_vendedores->removePersonagem(idVendedor));
}
void CCenario::update()
{
	for(int i = 0; i < max(_jogadores->size() , max(_inimigos->size(), _npcs->size())); i=i+1)
	{
		if(i < _inimigos->size())	getMonsterAt(i)->update();
		if(i < _jogadores->size())  getPlayerAt(i)->update();
		if(i < _npcs->size())		getNpcAt(i)->update();
	}
}