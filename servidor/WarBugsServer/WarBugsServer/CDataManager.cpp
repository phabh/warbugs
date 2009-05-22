#include "CDataManager.h"
#include "FunctionsCommom.h"
#include "commom.h"
#include <Enumerators.h>

#include <CJogador.h>
#include <CConsumableItem.h>
#include <CQItem.h>
#include <CLoyaltyScroll.h>
#include <CArmor.h>
#include <CWeapon.h>
#include <CCenario.h>
#include <CCenarioList.h>

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

	for(int i = 0; i < (int)numCampos; i++)
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
			case JOGADOR: //Jogador
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

				CBolsa tempBolsa;

				tempBolsa = getBolsaPersonagem(personagem->getID());

				((CPersonagemJogador *)personagem)->setBolsa(&tempBolsa);

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

				float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

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

				//Colocar a bolsa de itens para o personagem


				break;
			}
		case LIDER:
			{
				personagem = NULL;
				int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				if(race == FORMIGA)
				{
					//monta o TanDan
				}
				break;
			}
		case MAE: //NPC
		case FILHOTE: //NPC
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
		case VENDEDOR: //Vendedor
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
		case SOLDADO: //Inimigo
			{
				personagem = NULL;
				int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
				{
					//se for inimigo
				}
				else
				{
					//se for amigo
				}

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

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];

	CPersonagem * personagem;

	for(int i = 0; i < (int)numRegs; i++)
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

		((CPersonagemJogador *)personagem)->setBolsa(&tempBolsa);

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
		
		((CPersonagemJogador *)personagem)->setPlayer(idJogador);

		float posX = (float) System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
		float posZ = (float) System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

		((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString());

		((CPersonagemJogador *)personagem)->setSpeed(dado[0]);

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

		for(int i = 0; i < (int)numCampos; i++)
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

	if(idRaca != ALLRACE && idRaca != NONERACE)
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
		System::String ^texto = L"Não foi encontrado o Persoangem de Tipo"+idTipoPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < (int)numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
				case JOGADOR: 
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

					CBolsa tempBolsa;

					tempBolsa = getBolsaPersonagem(personagem->getID());

					((CPersonagemJogador *)personagem)->setBolsa(&tempBolsa);

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

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

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
			case LIDER: //NPC
				{
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());
					
					if(race == FORMIGA)
					{
						//monta o TanDan
					}
				}
			case MAE: //NPC
			case FILHOTE: //NPC
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
			case VENDEDOR: //Vendedor
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
			case SOLDADO: //Inimigo
				{
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
					}
					else
					{
						//se for amigo
					}
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
	if(idRaca != ALLRACE && idRaca != NONERACE)
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
		System::String ^texto = L"Não foi encontrado o Tipo de Personagem "+idTipoPersonagem+" no cenário "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < (int)numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
				case JOGADOR: //Jogador
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

					CBolsa tempBolsa;

					tempBolsa = getBolsaPersonagem(personagem->getID());

					((CPersonagemJogador *)personagem)->setBolsa(&tempBolsa);

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

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

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
				case LIDER: //NPC
				{
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());
					if(race == FORMIGA)
					{
						//monta o inimigo
					}
					personagem = NULL;
					break;
				}
				case FILHOTE: //NPC
				case MAE: //NPC
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
				case VENDEDOR: //Vendedor
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
				case SOLDADO: //Inimigo
				{
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
					}
					else
					{
						//se for amigo
					}
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
	if(idRaca != ALLRACE && idRaca != NONERACE)
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
		System::String ^texto = L"Não foi encontrado o Personagem de Tipo "+idTipoPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	for(int i = 0; i < (int)numRegs; i++)
	{
		int tipoPersonagem = System::Int32::Parse(dados[nomeCampos->IndexOf("PGTIPOPERSONAGEM")]->ToString());


		CPersonagem * personagem;

		switch(tipoPersonagem)
		{
			case JOGADOR: //Jogador
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

					CBolsa tempBolsa;

					tempBolsa = getBolsaPersonagem(personagem->getID());

					((CPersonagemJogador *)personagem)->setBolsa(&tempBolsa);

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

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

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
			case LIDER: //NPC
				{
					personagem = NULL;

					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race == FORMIGA)
					{
						//monta o TANDAN
					}

					break;
				}
			case FILHOTE: //NPC
			case MAE: //NPC
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
			case VENDEDOR: //Vendedor
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
			case SOLDADO: //Inimigo
				{
					
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
					}
					else
					{
						//se for amigo
					}
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

	for(int i = 0; i < (int)numCampos; i++)
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
				bool b1 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITISTEMP")]->ToString());
				bool b2 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURACAO")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				item = new CConsumableItem((TypeItens)dado[2],NAMOCHILA,dado[3],b2,(Atrib)tipoUso,dado[0],b1,dado[1]);

/*
				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CConsumableItem *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CConsumableItem *)item)->setID(dado[0]);
/*
				str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CConsumableItem *)item)->setNome(str);*/


				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

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

				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

				dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
				dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
				dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
				dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
				dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
				dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
				dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

				item = new CWeapon((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[5],dado[4],dado[6],dado[7],dado[8],dado[9]);
/*
				string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CWeapon *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CWeapon *)item)->setID(dado[0]);
/*
				str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CWeapon *)item)->setNome(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

				break;
			}
		case ARMADURA: 
			{
				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

				dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
				dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
				dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

				item = new CArmor((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[4],dado[5]);

				/*string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CArmor *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CArmor *)item)->setID(dado[0]);

				/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CArmor *)item)->setNome(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

				break;
			}
		case QUEST: 
			{

				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

				item = new CQItem((TypeItens) dado[0],NAMOCHILA,dado[1],b2,NULL);

				/*string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CQItem *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CQItem *)item)->setID(dado[0]);

				/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CQItem *)item)->setNome(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

				break;
			}
		case SCROLL: 
			{

				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

				dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
				dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
				dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
				dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
				dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
				dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
				dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				
				item = new CScroll((TypeItens)dado[0],NAMOCHILA,dado[1],b2,dado[2],dado[4],dado[3],dado[5],dado[6],dado[7],dado[8]);

				/*string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CScroll *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CScroll *)item)->setID(dado[0]);

				/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CScroll *)item)->setNome(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

				break;
			}
		case LSCROLL: 
			{
				dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
				dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

				bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

				dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALARANHA")]->ToString());
				dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALBESOURO")]->ToString());
				dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALLOUVA")]->ToString());
				dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALESCORPIAO")]->ToString());
				dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALVESPA")]->ToString());

				item = new CLoyaltyScroll((TypeItens)dado[0], NAMOCHILA,dado[1],b2,dado[2],dado[3],dado[4],dado[5],dado[6]);

				/*string str;
				str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
				((CLoyaltyScroll *)item)->setDescricao(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CLoyaltyScroll *)item)->setID(dado[0]);

				/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
				((CLoyaltyScroll *)item)->setNome(str);*/

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

				item->set2DTexture(dado[2]);
				item->set3DTexture(dado[1]);
				item->setModel(dado[0]);

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
		    +"IR.PGID = P.PGID AND P.PGIDWEAPON = IR.ITID AND"
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado o equipamento do Personagem "+idPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < (int)numCampos; i++)
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

	dado[10] += arma->getPrice();

	CWeapon * armaResposta = new CWeapon(arma->getNome(),
										 arma->getEstado(),
										 dado[10],
										 arma->isDropable(),
										 arma->getRace(),
										 arma->getMod()+dado[3],
										 arma->getMinDamage()+dado[4],
										 arma->getMaxDamage()+dado[5],
										 arma->getRange()+dado[6],
										 arma->getSpeed()+dado[7],
										 arma->getDurability()+dado[8],
										 arma->getMagicLevel()
										 );

	armaResposta->setID(arma->getID());
	armaResposta->set2DTexture(arma->get2DTexture());
	armaResposta->set3DTexture(arma->get3DTexture());
	armaResposta->setModel(arma->getModel());

	return armaResposta;
}
/*
	Obtem a armadura que o personagem está equipado
	@param idPersonagem -> id do personagem
	@return -> armadura
*/
CArmor * CDataManager::getArmorEquiped(int idPersonagem)
{
	CArmor * armadura;
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE"
		    +"IR.PGID = P.PGID AND P.PGIDARMOR = IR.ITID AND"
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado a Armadura do Personagem "+idPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < (int)numCampos; i++)
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
	defesa
	durabilidade
	*/

	armadura = (CArmor *)getItem(dado[0]);

	CArmor * armaduraResposta = new CArmor(armadura->getNome(),
										 armadura->getEstado(),
										 armadura->getPrice()+dado[10],
										 armadura->isDropable(),
										 armadura->getRace(),
										 armadura->getDef()+dado[3],
										 armadura->getDurability()+dado[4],
										 armadura->getMagicLevel()
										 );

	armaduraResposta->setID(armadura->getID());
	armaduraResposta->set2DTexture(armadura->get2DTexture());
	armaduraResposta->set3DTexture(armadura->get3DTexture());
	armaduraResposta->setModel(armadura->getModel());

	return armaduraResposta;
}

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

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	int i = System::Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());

	cenario = new CCenario(i,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	return cenario;
}

CCenarioList * CDataManager::getListCenario()
{
	CCenarioList * listCenario = new CCenarioList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT * FROM CENARIO";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Cenário!";
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	CCenario * cenarioTemp;
	
	for(int i = 0; i < (int)numRegs; i++)
	{

		int idcenario = System::Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());
		CPeopleList * listaInimigos   = &getPersonagem( SOLDADO, ALLRACE, idcenario);
		CPeopleList * listaPersonagem = new CPeopleList();
		CPeopleList * listaNPC		  = new CPeopleList();
		CBolsaList * listaBolsas      = getListBolsa(idcenario);
		CPortal * portalSul           = getPortal(idcenario,SUL);
		CPortal * portalNorte		  = getPortal(idcenario,NORTE);
		CPortal * portalOeste		  = getPortal(idcenario,OESTE);
		CPortal * portalLeste		  = getPortal(idcenario,LESTE);

		cenarioTemp = new CCenario(idcenario, listaPersonagem, listaInimigos, listaNPC, listaBolsas, portalNorte, portalSul, portalOeste, portalLeste);

		listCenario->addCenario(cenarioTemp);

		for(int j = 0; j < (int)numCampos; j++)
		{
			dados->RemoveAt(0);
		}		
		
	}
	

	return listCenario;
}

//Obter Bolsa
CBolsa * CDataManager::getBolsa(int id)
{
	CBolsa * bolsa;

	return bolsa;
}
/*
	Obtem os itens que o personagem estava no inventário(os equipados não)
	@param idPersonagem -> o id do personagem
	@return -> inventário do personagem
*/
CBolsa CDataManager::getBolsaPersonagem(int idPersonagem)
{
	CBolsa bolsa;

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1,IR.IRPRECO,IR.IRVALBONUS2,IR.IRVALBONUS3,IR.IRVALBONUS4,"
            +"IR.IRVALBONUS5,IR.IRVALBONUS6,IR.IRVALBONUS7 "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, PERSONAGEM P "
			+"WHERE "
			+" I.ITID = IR.ITID AND IR.PGID =  P.PGID AND IR.ITID <> P.PGIDARMOR AND IR.ITID <> P.PGIDWEAPON"
			+"AND IR.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Personagem com este id = "+idPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return bolsa;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	for(int i = 0; i < (int)numRegs; i++)
	{

		CItem * item;
		
		int dado[15];

		int tipoItem = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());


		switch((TipoItem)tipoItem)
		{
			case USO:
				{
					int tipoUso = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPOUSO")]->ToString());

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVALOR")]->ToString());
					bool b1 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITISTEMP")]->ToString());
					bool b2 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURACAO")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					item = new CConsumableItem((TypeItens)dado[2],NAMOCHILA,dado[3],b2,(Atrib)tipoUso,dado[0],b1,dado[1]);


					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CConsumableItem *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CConsumableItem *)item)->setID(dado[0]);

					/*
					str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CConsumableItem *)item)->setNome(str);*/


					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					


					break;
				}
			case ARMA: 
				{

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
					dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
					dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
					dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

					item = new CWeapon((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[5],dado[4],dado[6],dado[7],dado[8],dado[9]);

					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CWeapon *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CWeapon *)item)->setID(dado[0]);

					/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CWeapon *)item)->setNome(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					break;
				}
			case ARMADURA: 
				{
					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

					item = new CArmor((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[4],dado[5]);

					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CArmor *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CArmor *)item)->setID(dado[0]);

					/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CArmor *)item)->setNome(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					break;
				}
			case QUEST: 
				{

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

					item = new CQItem((TypeItens) dado[0],NAMOCHILA,dado[1],b2,NULL);

					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CQItem *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CQItem *)item)->setID(dado[0]);

					/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CQItem *)item)->setNome(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					break;
				}
			case SCROLL: 
				{

					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
					dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
					dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
					
					item = new CScroll((TypeItens)dado[0],NAMOCHILA,dado[1],b2,dado[2],dado[4],dado[3],dado[5],dado[6],dado[7],dado[8]);

					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CScroll *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CScroll *)item)->setID(dado[0]);

					/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CScroll *)item)->setNome(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					break;
				}
			case LSCROLL: 
				{
					dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
					dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

					bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

					dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALARANHA")]->ToString());
					dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALBESOURO")]->ToString());
					dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALLOUVA")]->ToString());
					dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALESCORPIAO")]->ToString());
					dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALVESPA")]->ToString());

					item = new CLoyaltyScroll((TypeItens)dado[0], NAMOCHILA,dado[1],b2,dado[2],dado[3],dado[4],dado[5],dado[6]);

					/*string str;
					str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
					((CLoyaltyScroll *)item)->setDescricao(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CLoyaltyScroll *)item)->setID(dado[0]);

					/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
					((CLoyaltyScroll *)item)->setNome(str);*/

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

					item->set2DTexture(dado[2]);
					item->set3DTexture(dado[1]);
					item->setModel(dado[0]);

					break;
				}

		}

		bolsa.addItem(item);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}
	}


	return bolsa;
}

CBolsa CDataManager::getBolsaTipoItem(int Tipo)
{
	CBolsa bolsa;

	return bolsa;
}

/*
	Obtem as bolsas com os itens que estiverem no cenário
	@param idCenario -> o cenário que será pego as bolsas
	@return -> lista de bolsas do cenário
*/
CBolsaList * CDataManager::getListBolsa(int idCenario)
{
	CBolsaList * listaBolsa;

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1,IR.IRPRECO,IR.IRVALBONUS2,IR.IRVALBONUS3,IR.IRVALBONUS4,"
            +"IR.IRVALBONUS5,IR.IRVALBONUS6,IR.IRVALBONUS7,B.BSID,B.BSX,B.BSY,B.BSZ "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, BOLSA B "
			+"WHERE "
			+"I.ITID = IR.ITID AND IR.BSID =  B.BSID AND B.CNID = "+idCenario+" "
			+"ORDER BY B.BSID";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado as bolsas do cenário "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	for(int i = 0; i < (int)numRegs; i++)
	{
		CBolsa bolsa;

		int idBolsa = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
		int idBolsaAnterior = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());

		bolsa.setID(idBolsa);

		while(idBolsa == idBolsaAnterior)
		{

			CItem * item;
			int dado[15];
			int tipoItem = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());

			switch((TipoItem)tipoItem)
			{
				case USO:
					{
						int tipoUso = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPOUSO")]->ToString());

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVALOR")]->ToString());
						bool b1 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITISTEMP")]->ToString());
						bool b2 = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURACAO")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						item = new CConsumableItem((TypeItens)dado[2],NAMOCHILA,dado[3],b2,(Atrib)tipoUso,dado[0],b1,dado[1]);


						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CConsumableItem *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CConsumableItem *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CConsumableItem *)item)->setNome(str);*/


						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						


						break;
					}
				case ARMA: 
					{

						dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

						dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
						dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
						dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
						dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
						dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
						dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
						dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
						dado[9]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

						item = new CWeapon((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[5],dado[4],dado[6],dado[7],dado[8],dado[9]);

						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CWeapon *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CWeapon *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CWeapon *)item)->setNome(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						break;
					}
				case ARMADURA: 
					{
						dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

						dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
						dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
						dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
						dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

						item = new CArmor((TypeItens)dado[0],NAMOCHILA,dado[1],b2,(Raca)dado[2],dado[3],dado[4],dado[5]);

						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CArmor *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CArmor *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CArmor *)item)->setNome(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						break;
					}
				case QUEST: 
					{

						dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

						item = new CQItem((TypeItens) dado[0],NAMOCHILA,dado[1],b2,NULL);

						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CQItem *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CQItem *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CQItem *)item)->setNome(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						break;
					}
				case SCROLL: 
					{

						dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

						dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
						dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
						dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
						dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
						dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
						dado[7]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
						dado[8]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
						
						item = new CScroll((TypeItens)dado[0],NAMOCHILA,dado[1],b2,dado[2],dado[4],dado[3],dado[5],dado[6],dado[7],dado[8]);

						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CScroll *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CScroll *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CScroll *)item)->setNome(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						break;
					}
				case LSCROLL: 
					{
						dado[0]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
						dado[1]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

						bool b2  = System::Boolean::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

						dado[2]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALARANHA")]->ToString());
						dado[3]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALBESOURO")]->ToString());
						dado[4]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALLOUVA")]->ToString());
						dado[5]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALESCORPIAO")]->ToString());
						dado[6]  = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALVESPA")]->ToString());

						item = new CLoyaltyScroll((TypeItens)dado[0], NAMOCHILA,dado[1],b2,dado[2],dado[3],dado[4],dado[5],dado[6]);

						/*string str;
						str = toChar(dados[nomeCampos->IndexOf(L"ITDESCRICAO")]->ToString());
						((CLoyaltyScroll *)item)->setDescricao(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
						((CLoyaltyScroll *)item)->setID(dado[0]);

						/*str = toChar(dados[nomeCampos->IndexOf(L"ITNOME")]->ToString());
						((CLoyaltyScroll *)item)->setNome(str);*/

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

						item->set2DTexture(dado[2]);
						item->set3DTexture(dado[1]);
						item->setModel(dado[0]);

						break;
					}

			}

			dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSX")]->ToString());
			dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSY")]->ToString());
			dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSZ")]->ToString());

			bolsa.setPosition(dado[0],dado[2]);

			bolsa.addItem(item);

			for(int j = 0; j < (int)numCampos; j++)
			{
				dados->RemoveAt(0);
			}

			//se for o ultimo registro ele não terá dados para retornar dentro de dados
			if(i < (int) (numRegs-1))
			{
				idBolsaAnterior = System::Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
			}
			else
			{
				idBolsaAnterior = -1;
			}

		}//fim while

		listaBolsa->addBag(&bolsa);

	}//fim for


	return listaBolsa;
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

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	System::String ^ temp = gcnew System::String(login);

	query = L"SELECT * FROM JOGADOR WHERE JDLOGIN = \""+temp+"\"";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado o Jogador com Login "+temp;
		WarBugsLog::_log->Items->Add(texto);		
		jogador.setID(-1);
		return jogador;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	jogador.setID(System::Int32::Parse(dados[nomeCampos->IndexOf(L"JDID")]->ToString()));
	jogador.setBirthdate(toChar(dados[nomeCampos->IndexOf(L"JDDATANASC")]->ToString()));
	jogador.setEmail(toChar(dados[nomeCampos->IndexOf(L"JDEMAIL")]->ToString()));
	jogador.setPassword(toChar(dados[nomeCampos->IndexOf(L"JDSENHA")]->ToString()));
	jogador.setName(toChar(dados[nomeCampos->IndexOf(L"JDNOME")]->ToString()));
	jogador.setLogin(toChar(dados[nomeCampos->IndexOf(L"JDLOGIN")]->ToString()));

	return jogador;
}
	

/*
	Obtem o portal do cenário passado e da direção passada
	@param idCenario -> id do cenário
	@param direcao -> direcao
	@return -> o portal
*/
CPortal * CDataManager::getPortal(int idCenario, Direcoes direcao)
{
	CPortal * portal;

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	int tempInt = (int)direcao;

	query = L"SELECT P.* FROM PORTAL P, PORTAL_CENARIO PC "
			+"WHERE P.PTID = PC.PTID AND "
			+"P.PTDIRECAO = "+tempInt
			+" AND PC.CNID = "+idCenario;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado o Portal para "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return portal;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	portal = new CPortal(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PTID")]->ToString()),
						 System::Int32::Parse(dados[nomeCampos->IndexOf(L"PTIDCENARIODEST")]->ToString()),
						 System::Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTX")]->ToString()),
					     System::Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTZ")]->ToString()));


	portal->setPosition(System::Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCX")]->ToString()),
					   System::Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCZ")]->ToString()));



	return portal;
}


//Login
/*
	processa as informações de login e verifica se o usuário e senha passados são válidos
	@param login -> login do usuário
	@param senha -> senha do usuário
	@param jogador -> o objeto jogador que será retornado caso as informações estejam corretas
	@retun -> se usuario e senha são válidos retorna true
*/
bool  CDataManager::doLogin(char * login, char * senha, CJogador & jogador)
{
	bool result = false;

	CJogador j;
	//jogador = NULL;

	j = getJogador(login);

	if(j.getID() != -1)
	{
		if( strcmp(login,j.getLogin()) == 0 && strcmp(senha,j.getPassword()) == 0)
		{
			jogador = j;
			result = true;
		}
	}

	return result;
}
	
//Micelandia
long  CDataManager::numPersonagens()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	System::String ^ query;

	query = L"SELECT COUNT(PGID) NOVOID FROM PERSONAGEM";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi possível contar os Personagens";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	result = System::Int32::Parse(dados[0]->ToString());

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
void CDataManager::insertPersonagemJogador(CPersonagemJogador * p1)
{
	System::String ^ query;
	System::String ^ temp;
	temp = gcnew System::String(p1->getName());

	int tempRaca = p1->getRace();


	query = L"INSERT INTO `personagem` "
		    +"(`PGID`,`PGNOME`,`PGNIVEL`,`PGDINHEIRO`,"
			+"`PGEXPERIENCIA`,`PGEXPERIENCIAMAX`,`PGPONTOSVIDA`,"
			+"`PGPONTOSVIDAMAX`,`PGPONTOSPODER`,`PGPONTOSPODERMAX`,"
			+"`PGDIRECAO`,`PGVELOCIDADE`,`PGRACA`,`PGTEMPORESPAW`,"
			+"`PGFORCA`,`PGAGILIDADE`,`PGDESTREZA`,`PGRESISTENCIA`,"
			+"`PGINSTINTO`,`PGATAQUESDISTANCIA`,`PGATAQUESCORPO`,"
			+"`PGDANOCORPO`,`PGDANODISTANCIA`,`PGDEFESA`,`PGTAXAATAQUE`,"
			+"`PGTEMPOCARGA`,`PGTIPOPERSONAGEM`,`PGLEALARANHA`,`PGLEALBESOURO`,"
			+"`PGLEALESCORPIAO`,`PGLEALLOUVA`,`PGLEALVESPA`,`PGIDARMOR`,"
			+"`PGIDWEAPON`,`PGX`,`PGZ`,`PGY`,`PGIDTEXTURA`,`PGIDMODELO`,"
			+"`PGBONUSPOINTSPRIMARIAS`,`PGBONUSPOINTSPODER`,`PGISBASE`,`PGIDHUD`)"
			+" VALUES ("+numPersonagens()+",\""+temp+"\","+p1->getLevel()+","+p1->getMoney()
			+","+p1->getXP()+","+p1->getMaxXP()+","+p1->getStats()->getPV()
			+","+p1->getStats()->getMaxPV()+","+p1->getStats()->getPM()+","+p1->getStats()->getMaxPM()
			+","+p1->getDirection()+","+p1->getMoveSpeed()+","+tempRaca+","+p1->getRespawnTime()
			+","+p1->getFOR()+","+p1->getAGI()+","+p1->getDES()+","+p1->getRES()
			+","+p1->getINS()+","+p1->getStats()->getRangedAttack()+","+p1->getStats()->getMeleeAttack()
			+","+p1->getStats()->getMeleeDamage()+","+p1->getStats()->getRangedDamage()+","+p1->getStats()->getDefense()+","+p1->getStats()->getAttackRate()
			+","+p1->getStats()->getChargeTime()+","+(int)JOGADOR+","+p1->getLoyalty()->getLoyaltyToSpider()+","+p1->getLoyalty()->getLoyaltyToBeetle()
			+","+p1->getLoyalty()->getLoyaltyToScorpion()+","+p1->getLoyalty()->getLoyaltyToMantis()+","+p1->getLoyalty()->getLoyaltyToWasp()+","+p1->getEquip()->armadura->getID()
			+","+p1->getEquip()->arma->getID()+","+p1->getPosition()->x+","+p1->getPosition()->z+","+0+","+p1->get3DTexture()+","+p1->getModel()
			+","+p1->getSkillPointsLeft()+","+p1->getPointsLeft()+",0,"+p1->get2DTexture()+")";

	
	System::String ^texto;

	//se não for inserido com sucesso
	if(_dataBase->insertNow(toChar(query)))
	{
		texto = L"Personagem '"+temp+"' Incluído com sucesso";
	}
	else
	{
		texto = L"Não foi possivel incluir o personagem '"+temp+"'.";
	}

	WarBugsLog::_log->Items->Add(texto);			

}

void CDataManager::insertPersonagem(CPeopleList p1)
{}