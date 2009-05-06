#include "CDataManager.h"
#include "FunctionsCommom.h"
#include "commom.h"

#include <CJogador.h>
#include <CConsumableItem.h>
#include <CQItem.h>
#include <CLoyaltyScroll.h>
#include <CCenario.h>

CDataManager::CDataManager(CDataBase * db)
{
	_dataBase = db;
}

//CONSULTAS
//Obter persoangens
/*
	Obtem o persoangem pelo id
	Obs.: virá o personagem de qualquer tipo, o tratamento deve ser feito após
*/
CPersonagem * CDataManager::getPersonagem(int id)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT * FROM PERSONAGEM WHERE PGID = "+id;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem com este id = "+id;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int index = nomeCampos->IndexOf("PGTIPOPERSONAGEM");

	int dado[15];

	int tipoPersonagem = System::Int32::Parse(dados[index]->ToString());


	CPersonagem * personagem;

	switch(tipoPersonagem)
	{
		case 0: //Jogador
			{
				personagem = new CPersonagemJogador();
				
				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CPersonagemJogador *)personagem)->setID(dado[0]);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
				dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
				dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

				CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

				((CPersonagemJogador *)personagem)->setBaseStats(tempHabilidades);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				((CPersonagemJogador *)personagem)->setRace((Raca)dado[0]);

				CEquipamento * tempEquip = new CEquipamento();
				
				tempEquip->armadura = getArmorEquiped(personagem->getID());
				tempEquip->arma     = getWeaponEquiped(personagem->getID());

				((CPersonagemJogador *)personagem)->setEquip(tempEquip);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

				((CPersonagemJogador *)personagem)->setLevel(dado[0]);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
				dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
				dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

				CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

				((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

				((CPersonagemJogador *)personagem)->setMoney(dado[0]);

				char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

				((CPersonagemJogador *)personagem)->setName(nome);
				
				//dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				//FICA PRA DEPOIS
				((CPersonagemJogador *)personagem)->setPlayer(-1);

				float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

				((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

				//dado = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				//FICA PRA DEPOIS
				((CPersonagemJogador *)personagem)->setTarget(NULL);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

				((CPersonagemJogador *)personagem)->setXP(dado[0]);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

				((CPersonagemJogador *)personagem)->setXPToNextLv(dado[0]);

				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
				dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
				dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
				dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
				dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
				dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
				dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
				dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
				dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
				dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

				((CPersonagemJogador *)personagem)->getStats()->setAttackRate(dado[0]);
				((CPersonagemJogador *)personagem)->getStats()->setChargeTime(dado[1]);
				((CPersonagemJogador *)personagem)->getStats()->setDefense(dado[2]);
				((CPersonagemJogador *)personagem)->getStats()->setMaxPM(dado[3]);
				((CPersonagemJogador *)personagem)->getStats()->setMaxPV(dado[4]);
				((CPersonagemJogador *)personagem)->getStats()->setMeleeAttack(dado[5]);
				((CPersonagemJogador *)personagem)->getStats()->setMeleeDamage(dado[6]);
				((CPersonagemJogador *)personagem)->getStats()->setPM(dado[7]);
				((CPersonagemJogador *)personagem)->getStats()->setPV(dado[8]);
				((CPersonagemJogador *)personagem)->getStats()->setRangedAttack(dado[9]);
				((CPersonagemJogador *)personagem)->getStats()->setRangedDamage(dado[10]);

				break;
			}
		case 1: //NPC
			{
				personagem = NULL;
				/*
				personagem = new CNPC();
				
				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CNPC *)personagem)->setID(dado[0]);

				float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CNPC *)personagem)->setPosition(posX,posZ);*/

				break;
			}
		case 2: //Vendedor
			{
				personagem = NULL;
/*				personagem = new CVendedor();
				
				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CVendedor *)personagem)->setID(dado[0]);

				float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CVendedor *)personagem)->setPosition(posX,posZ);
*/
				break;
			}
		case 3: //Inimigo
			{
				personagem = NULL;
				/*
				personagem = new CInimigo();
				
				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CInimigo *)personagem)->setID(dado[0]);

				float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CInimigo *)personagem)->setPosition(posX,posZ);*/

				break;
			}
	}


	return personagem;
}

/*
	Obtem a lista de jogadores que um jogador possui
	@param idJogador -> id do jogador
	@return -> lista de personagens do jogador
*/
CPeopleList CDataManager::getPersonagemJogador(int idJogador)
{
	CPeopleList Lista;

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT P.* FROM PERSONAGEM P, JOGADOR_PERSONAGEM JP WHERE P.PGID = JP.PGID AND JP.JDID = "+idJogador;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem para o jogador = "+idJogador;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];

	CPersonagem * personagem;

	for(int i = 0; i < numRegs; i++)
	{
		personagem = new CPersonagemJogador();
		
		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		((CPersonagemJogador *)personagem)->setID(dado[0]);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
		dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
		dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
		dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
		dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

		CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

		((CPersonagemJogador *)personagem)->setBaseStats(tempHabilidades);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

		((CPersonagemJogador *)personagem)->setRace((Raca)dado[0]);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDARMOR")]->ToString());
		dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDWEAPON")]->ToString());

		CEquipamento * tempEquip = new CEquipamento();
		
		tempEquip->armadura = getArmorEquiped(personagem->getID());
		tempEquip->arma     = getWeaponEquiped(personagem->getID());

		((CPersonagemJogador *)personagem)->setEquip(tempEquip);


		CBolsa tempBolsa;

		tempBolsa = getBolsaPersonagem(personagem->getID());

		for(int i = 0; i < tempBolsa.size(); i++)
		{
			((CPersonagemJogador *)personagem)->addItem(tempBolsa.getItem(
		}

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

		((CPersonagemJogador *)personagem)->setLevel(dado[0]);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
		dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
		dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
		dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
		dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

		CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

		((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

		((CPersonagemJogador *)personagem)->setMoney(dado[0]);

		char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

		((CPersonagemJogador *)personagem)->setName(nome);
		
		//dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		//FICA PRA DEPOIS
		((CPersonagemJogador *)personagem)->setPlayer(idJogador);

		float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
		float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

		((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

		((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

		//dado = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		//FICA PRA DEPOIS
		((CPersonagemJogador *)personagem)->setTarget(NULL);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

		((CPersonagemJogador *)personagem)->setXP(dado[0]);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

		((CPersonagemJogador *)personagem)->setXPToNextLv(dado[0]);

		dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
		dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
		dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
		dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
		dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
		dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
		dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
		dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
		dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
		dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
		dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

		((CPersonagemJogador *)personagem)->getStats()->setAttackRate(dado[0]);
		((CPersonagemJogador *)personagem)->getStats()->setChargeTime(dado[1]);
		((CPersonagemJogador *)personagem)->getStats()->setDefense(dado[2]);
		((CPersonagemJogador *)personagem)->getStats()->setMaxPM(dado[3]);
		((CPersonagemJogador *)personagem)->getStats()->setMaxPV(dado[4]);
		((CPersonagemJogador *)personagem)->getStats()->setMeleeAttack(dado[5]);
		((CPersonagemJogador *)personagem)->getStats()->setMeleeDamage(dado[6]);
		((CPersonagemJogador *)personagem)->getStats()->setPM(dado[7]);
		((CPersonagemJogador *)personagem)->getStats()->setPV(dado[8]);
		((CPersonagemJogador *)personagem)->getStats()->setRangedAttack(dado[9]);
		((CPersonagemJogador *)personagem)->getStats()->setRangedDamage(dado[10]);

		Lista.addPersonagem(personagem);

		for(int i = 0; i < numCampos; i++)
		{
			dados->RemoveAt(0);
		}
	}

	return Lista;
	
}


/*
	Obtem uma lista de personagens do tipo, raça, e se é um persoangem base
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual raça ele pertence TODAS, NENHUMA, ARANHA
	@param personagemBase -> se é um personagem que tem atributos base
	@return -> lista de personagem
*/
CPeopleList CDataManager::getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	System::String ^ complemento;

	if(idRaca != TODAS && idRaca != NENHUMA)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}


	query = 	L"SELECT P.* FROM PERSONAGEM P WHERE "+complemento				
				+" P.PGISBASE = "+personagemBase
				+" AND P.PGTIPOPERSONAGEM = "+idTipoPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CPeopleList Lista;
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado";
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
			case 0: //Jogador
				{
					personagem = new CPersonagemJogador();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CPersonagemJogador *)personagem)->setID(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CPersonagemJogador *)personagem)->setRace((Raca)dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDARMOR")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDWEAPON")]->ToString());

					CEquipamento * tempEquip = new CEquipamento();
					
					tempEquip->armadura = (CArmor  *) getItem(dado[0]);
					tempEquip->arma     = (CWeapon *)getItem(dado[1]);

					((CPersonagemJogador *)personagem)->setEquip(tempEquip);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

					((CPersonagemJogador *)personagem)->setLevel(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

					CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CPersonagemJogador *)personagem)->setMoney(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);
					
					//dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

					((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

					//dado = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setTarget(NULL);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

					((CPersonagemJogador *)personagem)->setXP(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

					((CPersonagemJogador *)personagem)->setXPToNextLv(dado[0]);

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
					dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
					dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
					dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
					dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

					((CPersonagemJogador *)personagem)->getStats()->setAttackRate(dado[0]);
					((CPersonagemJogador *)personagem)->getStats()->setChargeTime(dado[1]);
					((CPersonagemJogador *)personagem)->getStats()->setDefense(dado[2]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPM(dado[3]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPV(dado[4]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CPersonagemJogador *)personagem)->getStats()->setPM(dado[7]);
					((CPersonagemJogador *)personagem)->getStats()->setPV(dado[8]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedDamage(dado[10]);

					break;
				}
			case 1: //NPC
				{
					personagem = NULL;
/*					personagem = new CNPC();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX,posZ);
*/
					break;
				}
			case 2: //Vendedor
				{
					personagem = NULL;
					/*				personagem = new CVendedor();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX,posZ);
	*/
					break;
				}
			case 3: //Inimigo
				{
					personagem = NULL;
					/*
					personagem = new CInimigo();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CInimigo *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CInimigo *)personagem)->setPosition(posX,posZ);*/

					break;
				}
		}

		Lista.addPersonagem(personagem);
	}

	return Lista;

}
/*
	Obtem uma lista de personagens do tipo e raça
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual raça ele pertence TODAS, NENHUMA, ARANHA
	@param idCenario-> cenario onde ele está
	@return -> lista de personagem
*/
CPeopleList CDataManager::getPersonagem(int idTipoPersonagem, int idRaca, int idCenario)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	System::String ^ complemento;
	if(idRaca != TODAS && idRaca != NENHUMA)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}

	query = L"SELECT P.* FROM PERSONAGEM P, PERSONAGEM_CENARIO PC"
		    +"WHERE P.PGID = PC.PGID AND   "
			+"PC.CNID =  "+idCenario+" AND "
			+complemento
			+"P.PGTIPOPERSONAGEM = "+idTipoPersonagem;
		
	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CPeopleList Lista;
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado";
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
			case 0: //Jogador
				{
					personagem = new CPersonagemJogador();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CPersonagemJogador *)personagem)->setID(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CPersonagemJogador *)personagem)->setRace((Raca)dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDARMOR")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDWEAPON")]->ToString());

					CEquipamento * tempEquip = new CEquipamento();
					
					tempEquip->armadura = (CArmor  *)getItem(dado[0]);
					tempEquip->arma     = (CWeapon *)getItem(dado[1]);

					((CPersonagemJogador *)personagem)->setEquip(tempEquip);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

					((CPersonagemJogador *)personagem)->setLevel(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

					CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CPersonagemJogador *)personagem)->setMoney(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);
					
					//dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

					((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

					//dado = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setTarget(NULL);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

					((CPersonagemJogador *)personagem)->setXP(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

					((CPersonagemJogador *)personagem)->setXPToNextLv(dado[0]);

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
					dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
					dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
					dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
					dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

					((CPersonagemJogador *)personagem)->getStats()->setAttackRate(dado[0]);
					((CPersonagemJogador *)personagem)->getStats()->setChargeTime(dado[1]);
					((CPersonagemJogador *)personagem)->getStats()->setDefense(dado[2]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPM(dado[3]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPV(dado[4]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CPersonagemJogador *)personagem)->getStats()->setPM(dado[7]);
					((CPersonagemJogador *)personagem)->getStats()->setPV(dado[8]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedDamage(dado[10]);

					break;
				}
			case 1: //NPC
				{
					personagem = NULL;
					/*
					personagem = new CNPC();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX,posZ);
*/
					break;
				}
			case 2: //Vendedor
				{
					personagem = NULL;
					/*
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX,posZ);
	*/
					break;
				}
			case 3: //Inimigo
				{
					
					personagem = NULL;
					/*
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CInimigo *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CInimigo *)personagem)->setPosition(posX,posZ);*/

					break;
				}
		}

		Lista.addPersonagem(personagem);
	}

	return Lista;	
}

	
/*
	Obtem uma lista de personagens do tipo e raça
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual raça ele pertence TODAS, NENHUMA, ARANHA
	@return -> lista de personagem
*/
CPeopleList CDataManager::getPersonagem(int idTipoPersonagem, int idRaca)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	System::String ^ complemento;
	if(idRaca != TODAS && idRaca != NENHUMA)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}

	query = 	L"SELECT P.* FROM PERSONAGEM P WHERE "
				+complemento
				+" P.PGTIPOPERSONAGEM = "+idTipoPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CPeopleList Lista;
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado";
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
			case 0: //Jogador
				{
					personagem = new CPersonagemJogador();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CPersonagemJogador *)personagem)->setID(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CPersonagemJogador *)personagem)->setRace((Raca)dado[0]);

					CEquipamento * tempEquip = new CEquipamento();
					
					tempEquip->armadura = getArmorEquiped(personagem->getID());
					tempEquip->arma     = getWeaponEquiped(personagem->getID());

					((CPersonagemJogador *)personagem)->setEquip(tempEquip);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

					((CPersonagemJogador *)personagem)->setLevel(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

					CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

					((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CPersonagemJogador *)personagem)->setMoney(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);
					
					//dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

					((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

					//dado = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setTarget(NULL);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

					((CPersonagemJogador *)personagem)->setXP(dado[0]);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

					((CPersonagemJogador *)personagem)->setXPToNextLv(dado[0]);

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
					dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
					dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
					dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
					dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

					((CPersonagemJogador *)personagem)->getStats()->setAttackRate(dado[0]);
					((CPersonagemJogador *)personagem)->getStats()->setChargeTime(dado[1]);
					((CPersonagemJogador *)personagem)->getStats()->setDefense(dado[2]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPM(dado[3]);
					((CPersonagemJogador *)personagem)->getStats()->setMaxPV(dado[4]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CPersonagemJogador *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CPersonagemJogador *)personagem)->getStats()->setPM(dado[7]);
					((CPersonagemJogador *)personagem)->getStats()->setPV(dado[8]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CPersonagemJogador *)personagem)->getStats()->setRangedDamage(dado[10]);

					break;
				}
			case 1: //NPC
				{
					personagem = NULL;
/*
					personagem = new CNPC();
					
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX,posZ);
*/
					break;
				}
			case 2: //Vendedor
				{
					personagem = NULL;
					/*
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX,posZ);
	*/
					break;
				}
			case 3: //Inimigo
				{
					
					personagem = NULL;
					/*
					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CInimigo *)personagem)->setID(dado[0]);

					float posX = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CInimigo *)personagem)->setPosition(posX,posZ);*/

					break;
				}
		}

		Lista.addPersonagem(personagem);
	}

	return Lista;	
}

//Obter Itens
/*
	Obtem o item do id especificado
	@param id -> id do Item
	@return -> o item selecionado
*/
CItem * CDataManager::getItem(int id)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT * FROM ITEMBASE ITID = "+id;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CItem * item;
	
	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem com este id = "+id;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	int tipoItem = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());


	switch(tipoItem)
	{
		case USO:
			{
				int tipoUso = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPOUSO")]->ToString());

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVALOR")]->ToString());
				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITISTEMP")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURACAO")]->ToString());

				item = new CConsumableItem((Atrib)tipoUso,dado[0],b1,dado[1]);


				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CConsumableItem *)item)->setDescricao(str);

				b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CConsumableItem *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CConsumableItem *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CConsumableItem *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CConsumableItem *)item)->setPreco(dado[0]);

				/*
				switch(tipoUso)
				{
				case NENHUM:
					{
						item = new CConsumableItem();
						break;
					}
				case PV:
					{
						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPOUSO")]->ToString());
						item = new CConsumableItem(PV,);
						break;
					}
				case PM:
					{
						item = new CConsumableItem();
						break;
					}
				case FOR:
					{
						item = new CConsumableItem();
						break;
					}
				case DES: 
					{
						item = new CConsumableItem();
						break;
					}
				case AGI: 
					{
						item = new CConsumableItem();
						break;
					}
				case RES:
					{
						item = new CConsumableItem();
						break;
					}
				case INS:
					{
						item = new CConsumableItem();
						break;
					}
				case ATTACKMELEE: 
					{
						item = new CConsumableItem();
						break;
					}
				case ATTACKRANGED:
					{
						item = new CConsumableItem();
						break;
					}
				case DAMAGEMELEE: 
					{
						item = new CConsumableItem();
						break;
					}
				case DAMAGERANGED:
					{
						item = new CConsumableItem();
						break;
					}
				case DEFESA:
					{
						item = new CConsumableItem();
						break;
					}				
				}
				*/


				break;
			}
		case ARMA: 
			{

				item = new CWeapon();


				//((CWeapon *)item)->initialize(


				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CWeapon *)item)->setDescricao(str);

				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CWeapon *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CWeapon *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CWeapon *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CWeapon *)item)->setPreco(dado[0]);

				break;
			}
		case ARMADURA: 
			{

				item = new CArmor();

				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CArmor *)item)->setDescricao(str);

				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CArmor *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CArmor *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CArmor *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CArmor *)item)->setPreco(dado[0]);

				break;
			}
		case QUEST: 
			{
				item = new CQItem();

				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CQItem *)item)->setDescricao(str);

				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CQItem *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CQItem *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CQItem *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CQItem *)item)->setPreco(dado[0]);

				break;
			}
		case SCROLL: 
			{
				
				item = new CScroll();

				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CScroll *)item)->setDescricao(str);

				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CScroll *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CScroll *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CScroll *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CScroll *)item)->setPreco(dado[0]);

				break;
			}
		case LSCROLL: 
			{

				item = new CLoyaltyScroll();

				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CLoyaltyScroll *)item)->setDescricao(str);

				bool b1 = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				((CLoyaltyScroll *)item)->setDropable(b1);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CLoyaltyScroll *)item)->setID(dado[0]);

				str = toChar(dados[nomeCampos->IndexOf(L"nome")]->ToString());
				((CLoyaltyScroll *)item)->setNome(str);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());
				((CLoyaltyScroll *)item)->setPreco(dado[0]);

				break;
			}

	}


	return item;	
}







/*
	Obtem a arma que o personagem está equipado
	@param idPersonagem -> id do personagem
	@return -> arma
*/
CWeapon * CDataManager::getWeaponEquiped(int idPersonagem)
{
	CWeapon * arma;
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE"
		    +"IR.PGID = P.PGID AND P.PGIDARMOR = IR.ITID AND"
			+"P.PGID = "+idPersoangem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado";
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];

	dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
	dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());
	dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
	dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS1")]->ToString());
	dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS2")]->ToString());
	dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS3")]->ToString());
	dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS4")]->ToString());
	dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS5")]->ToString());
	dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS6")]->ToString());
	dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS7")]->ToString());
	dado[10] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"IRPRECO")]->ToString());


	/*
	modificador
	dano minimo
	dano maximo
	alcance
	velocidade
	durabilidade
	*/

	arma = (CWeapon *)getItem(dado[0]);

	dado[10] += arma->getPreco();
	
	CWeapon * armaResposta = new CWeapon();


	return arma;
}
/*
	Obtem a armadura que o personagem está equipado
	@param idPersonagem -> id do personagem
	@return -> armadura
*/
CArmor * CDataManager::getArmorEquiped(int idPersonagem)
{}

//Obter Cenarios
/*
	Obtem o objeto cenario com o id especificado
	@param id -> id do Cenario
	@return -> o cenario selecionado	
*/
CCenario * CDataManager::getCenario(int id)
{
	CCenario * cenario;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT * FROM CENARIO CNID = "+id;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem com este id = "+id;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	int i = System::Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());

	cenario = new CCenario(i,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	return cenario;
}

CCenario * CDataManager::getListCenario()
{
	CCenario * cenario;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT * FROM CENARIO";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem com este id = ";
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	int i = System::Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());

	cenario = new CCenario(i,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	return cenario;
}

//Obter Bolsa
CBolsa * CDataManager::getBolsa(int id)
{
	CBolsa * bolsa;

	return bolsa;
}

CBolsa CDataManager::getBolsaPersonagem(int idPersonagem)
{
	CBolsa bolsa;

	return bolsa;
}

CBolsa CDataManager::getBolsaTipoItem(int Tipo)
{
	CBolsa bolsa;

	return bolsa;
}

CBolsaList * CDataManager::getListBolsa(int idCenario)
{
	CBolsaList * bolsa;

	return bolsa;
}


//Obtem Jogador
CJogador CDataManager::getJogador(int id)
{
	CJogador jogador;

	return jogador;
}

CJogador CDataManager::getJogador(char * login)
{
	CJogador jogador;

	return jogador;
}
	
//Login
bool  CDataManager::doLogin(char * login, char * senha, CJogador * jogador)
{
	bool result;

	return result;
}
	
//Micelandia
long  CDataManager::numPersonagens()
{
	long result;

	return result;
}

long  CDataManager::numBolsas()
{
	long result;

	return result;
}

long  CDataManager::numItens()
{
	long result;

	return result;
}

//ATUALIZAÇÕES
//Personagem
void CDataManager::updatePersonagem(int id, float posX, float posZ)
{}

void CDataManager::updatePersonagem(int id, int nivel, int xp)
{}

//Inserções
void CDataManager::insertPersonagem(CPersonagem * p1)
{}
void CDataManager::insertPersonagem(CPeopleList p1)
{}