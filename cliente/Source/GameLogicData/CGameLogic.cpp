#include "CGameLogic.h"

//-----------------------------------------------------------------------------------------------------------------

CGameLogic::CGameLogic()
{
	_listaPersonagens = new CListaPersonagem();
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::addBolsa(int idBolsa, float posX, float posZ)
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

void CGameLogic::addPersonagem( CPersonagem *personagem )
{
	_listaPersonagens->addElement(personagem, personagem->getId());
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::atualizar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::inicializar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::removeBolsa(int idBolsa)
{
	// Remove uma bolsa do cenário do cliente
	//_listaBolsas->remove(idBolsa);
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::removePersonagem( CPersonagem *personagem )
{
	_listaPersonagens->removeElement(personagem->getId());
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::resetar()
{
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::setHorario(long hora)
{
	// Cenário do cliente recebe a hora do cenário do servidor
	_horario = hora;
}

//-----------------------------------------------------------------------------------------------------------------

void CGameLogic::setLua(int idLua)
{
	// Cenário do cliente recebe a lua corrente do cenário do servidor
	_luaCorrente = (tipoLua)idLua;
}

//-----------------------------------------------------------------------------------------------------------------