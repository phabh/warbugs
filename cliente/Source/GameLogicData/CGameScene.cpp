#include "CGameScene.h"

//-----------------------------------------------------------------------------------------------------------------

CGameScene::CGameScene()
{
	_listaPersonagens = new CListaPersonagem();
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::addBolsa(int idBolsa, float posX, float posZ)
{
	// Inclui uma bolsa no cenário do cliente
	SBolsa bolsaTemp;
	
	bolsaTemp._idBolsa = idBolsa + BOLSA_ID_OFFSET;
	bolsaTemp._x = posX;
	bolsaTemp._z = posZ;
	//bolsaTemp._listaItens->clear();

	//_listaBolsas->add(bolsaTemp);
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
	//_listaBolsas->remove(idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameScene::removePersonagem( CPersonagem *personagem )
{
	_listaPersonagens->removeElement(personagem->getId());
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