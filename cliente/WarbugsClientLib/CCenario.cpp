#pragma once

#include "CCenario.h"

CCenario::CCenario()
{
	_listaPersonagens = new CListaPersonagem();
}

void CCenario::addBolsa(int idBolsa, int posX, int posZ)
{
	// Inclui uma bolsa no cenário do cliente
	
	SBolsa bolsaTemp;
	
	bolsaTemp._idBolsa = idBolsa;
	bolsaTemp._x = posX;
	bolsaTemp._z = posZ;
	//bolsaTemp._listaItens->clear();

	//_listaBolsas->add(bolsaTemp);
}

void CCenario::addPersonagem( CPersonagem personagem )
{
	//_listaPersonagens->add(personagem);
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

void CCenario::removePersonagem()
{
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