#include "CGameScene.h"

//-----------------------------------------------------------------------------------------------------------------

CGameScene::CGameScene()
{
	_listaPersonagens = new CListaPersonagem();
	_listaBolsas = new ListaBolsa();

	_fileMtx = new CArquivoMatrizes();
	//_fileMtx->reset();
}

//-----------------------------------------------------------------------------------------------------------------

SMatrix CGameScene::loadMyMatrix(int idScene)
{
	_cenario = _fileMtx->getMatrix(idScene);

	return(_cenario);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::addBolsa(SBolsa bolsa)
{
	// Inclui uma bolsa no cenário do cliente
	_listaBolsas->addElement(bolsa, bolsa._idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::addPersonagem( CPersonagem *personagem )
{
	_listaPersonagens->addElement(personagem, personagem->getId());
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::atualizar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::inicializar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::removeBolsa(int idBolsa)
{
	// Remove uma bolsa do cenário do cliente
	_listaBolsas->removeElement(idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::removePersonagem( int idPersonagem )
{
	_listaPersonagens->removeElement(idPersonagem);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::resetar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::setHorario(long hora)
{
	// Cenário do cliente recebe a hora do cenário do servidor
	_horario = hora;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::setLua(int idLua)
{
	// Cenário do cliente recebe a lua corrente do cenário do servidor
	_luaCorrente = (TypeMoon)idLua;
}

//-----------------------------------------------------------------------------------------------------------------