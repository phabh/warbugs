#include "CCenario.h"

void CCenario::initMatrix()
{
	for(int i = 0; i < MAPMAXCOL; i = i + 1)
	{
		for(int j = 0; j < MAPMAXCOL; j = j + 1)
		{
			matrizDeCaminhamento[i][j] = NAOPASSAVEL;
		}
	}
}
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
	initMatrix();
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
			_jogadores->getElementAt(i)->setSceneID(_contador->giveID());
			((CPersonagemJogador*)(_jogadores->getElementAt(i)))->setScene(this);
		}
	}
	if(!_inimigos->isEmpty())
	{
		for(int i = 0; i < _inimigos->size(); i=i+1)
		{
			_inimigos->getElementAt(i)->setSceneID(_contador->giveID());
			((CInimigo*)(_inimigos->getElementAt(i)))->setScene(this);
		}
	}
	if(!_npcs->isEmpty())
	{
		for(int i = 0; i < _npcs->size(); i=i+1)
		{
			_npcs->getElementAt(i)->setSceneID(_contador->giveID());
			((CNPC*)(_npcs->getElementAt(i)))->setScene(this);
		}
	}
	if(!_vendedores->isEmpty())
	{
		for(int i = 0; i < _vendedores->size(); i=i+1)
		{
			_vendedores->getElementAt(i)->setSceneID(_contador->giveID());
			((CVendedor*)(_vendedores->getElementAt(i)))->setScene(this);
		}
	}
	if(!_itens->isEmpty())
	{
		for(int i = 0; i < _itens->size(); i=i+1)
		{
			_itens->getElementAt(i)->setSceneID(_contador->giveID());
			//_itens->getElementAt(i)->setScene(this);
		}
	}
}
bool CCenario::isSceneFull()
{
	return(_jogadores->size() < MAXPLAYERSINSCENE);
}
bool CCenario::haveLoyaltyRequired(CPersonagemJogador *jogador)
{
	return(jogador->getLoyalty()->getLoyaltyTo(_lealdadeNecessaria) >= _quantidadeNecessaria);
}
int CCenario::playerCount()
{
	return(_jogadores->size());
}
int CCenario::bagCount()
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
CPeopleList *CCenario::getPlayerList()
{
	return(_jogadores);
}
CPeopleList *CCenario::getMonsterList()
{
	return(_inimigos);
}
CPeopleList *CCenario::getNPCList()
{
	return(_npcs);
}
CPeopleList *CCenario::getSalesmanList()
{
	return(_vendedores);
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
	return (_itens->getBag(idBag));
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
CPortal *CCenario::getExit(TypeDirecao idPortal)
{
	switch(idPortal)
	{
	case D_NORTH:
		return(_saidaNorte);
	case D_SOUTH:
		return(_saidaSul);
	case D_EAST:
		return(_saidaRight);
	case D_WEST:
		return(_saidaLeft);
	}
	return(NULL);
}
Raca CCenario::getRaceNeeded()
{
	return(_lealdadeNecessaria);
}
int CCenario::getRaceNeededAsInt()
{
	return(_quantidadeNecessaria);
}
int CCenario::getLoyaltyRequired()
{
	return((int)_quantidadeNecessaria);
}
//
void CCenario::setExit(CPortal *newExit, TypeDirecao idPortal)
{
	switch(idPortal)
	{
	case D_NORTH:
		_saidaNorte = newExit;
		break;
	case D_SOUTH:
		_saidaSul = newExit;
		break;
	case D_EAST:
		_saidaRight = newExit;
		break;
	case D_WEST:
		_saidaLeft = newExit;
		break;
	}
}
void CCenario::setRaceNeeded(Raca race)
{
	 _lealdadeNecessaria = race;
}
void CCenario::setLoyaltyRequired(int value)
{
	_quantidadeNecessaria = value;
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
	CBolsa *temp = (CBolsa*)_itens->removeBag(idBag);
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
Ponto *CCenario::getQuadCenter(int linha, int coluna)
{
	Ponto *center = new Ponto();

	center->x = ((float)(linha * TAMQUADRANTE)) + ((float)(TAMQUADRANTE/2));
	center->z = ((float)(coluna * TAMQUADRANTE)) + ((float)(TAMQUADRANTE/2));

	return(center);
}

//-----------------------------------------------------------------------------------------------------------------

Ponto *CCenario::getQuadCenter(int idQuad)
{
	int linha, coluna;

	getQuadLinhaColuna(idQuad, linha, coluna);

	return getQuadCenter(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

Ponto *CCenario::getQuadCenter(Ponto *posicao)
{
	int linha, coluna;

	getQuadLinhaColuna(posicao, linha, coluna);

	return getQuadCenter(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

void CCenario::getQuadLinhaColuna(Ponto *posicao, int &linha, int &coluna)
{
	linha  = (int)(posicao->z / TAMQUADRANTE); // TAMQUADRANTE é a dimensão de um quadrante em pixels
	coluna = (int)(posicao->x / TAMQUADRANTE);
}

//-----------------------------------------------------------------------------------------------------------------

void CCenario::getQuadLinhaColuna(int idQuad, int &linha, int &coluna)
{
	linha  = idQuad / MAPMAXCOL;
	coluna = idQuad % MAPMAXCOL;
}

//-----------------------------------------------------------------------------------------------------------------

int CCenario::getQuadID(Ponto *posicao)
{
	int linha, coluna;

	getQuadLinhaColuna(posicao, linha, coluna);

	return getQuadID(linha, coluna);
}

//-----------------------------------------------------------------------------------------------------------------

int CCenario::getQuadID(int linha, int coluna)
{
	return ( coluna + (linha * MAPMAXCOL) );
}