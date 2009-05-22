#pragma once

#include "CCenario.h"

CCenario::CCenario()
{
	_listaPersonagens = new CListaPersonagem();
}

void CCenario::addBolsa(int idBolsa, float posX, float posZ)
{
	// Inclui uma bolsa no cenário do cliente
	SBolsa bolsaTemp;
	
	bolsaTemp._idBolsa = idBolsa + BOLSA_ID_OFFSET;
	bolsaTemp._x = posX;
	bolsaTemp._z = posZ;
	//bolsaTemp._listaItens->clear();

	//_listaBolsas->add(bolsaTemp);
}

void CCenario::addPersonagem( CPersonagem *personagem )
{
	_listaPersonagens->addElement(personagem, personagem->getId());
}

void CCenario::atualizar()
{
}

void CCenario::inicializar()
{
}

void CCenario::removeBolsa(int idBolsa)
{
	// Remove uma bolsa do cenário do cliente
	//_listaBolsas->remove(idBolsa);
}

void CCenario::removePersonagem( CPersonagem *personagem )
{
	_listaPersonagens->removeElement(personagem->getId());
}

void CCenario::resetar()
{
}

void CCenario::setHorario(long hora)
{
	// Cenário do cliente recebe a hora do cenário do servidor
	_horario = hora;
}

void CCenario::setLua(int idLua)
{
	// Cenário do cliente recebe a lua corrente do cenário do servidor
	_luaCorrente = (tipoLua)idLua;
}