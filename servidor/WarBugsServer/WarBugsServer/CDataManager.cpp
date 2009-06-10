#include "CDataManager.h"
#include "commom.h"
#include <Enumerators.h>

#include <CJogador.h>
#include <CConsumableItem.h>
#include <CQItem.h>
#include <CLoyaltyScroll.h>
#include <CArmor.h>
#include <CWeapon.h>
#include <CVendedor.h>
#include <CCenario.h>
#include <CCenarioList.h>

#include "FunctionsCommom.h"

using namespace System;

CDataManager::CDataManager(CDataBase * db)
{
	_dataBase = db;
}

//CONSULTAS
//Obter persoangens
/*
	Obtem o persoangem pelo id
	Obs.: vir� o personagem de qualquer tipo, o tratamento deve ser feito ap�s
*/
CPersonagem * CDataManager::getPersonagem(int id)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT * FROM PERSONAGEM WHERE PGID = "+id;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Personagem com este id = "+id;
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

	int tipoPersonagem = Int32::Parse(dados[index]->ToString());


	CPersonagem * personagem;

	

	switch(tipoPersonagem)
	{
			case JOGADOR: //Jogador
			{
				personagem = new CPersonagemJogador();

				CEquipamento * tempEquip = new CEquipamento();
				
				tempEquip->armadura = getArmorEquiped(personagem->getID());
				tempEquip->arma     = getWeaponEquiped(personagem->getID());

				((CPersonagemJogador *)personagem)->setEquip(tempEquip);

				dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALARANHA")]->ToString());
				dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALBESOURO")]->ToString());
				dado[2] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALESCORPIAO")]->ToString());
				dado[3] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALLOUVA")]->ToString());
				dado[4] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGLEALVESPA")]->ToString());

				CLealdade * tempLealdade = new CLealdade(dado[0],dado[1],dado[2],dado[3],dado[4]);

				((CPersonagemJogador *)personagem)->setLoyalty(tempLealdade);

				//FICA PRA DEPOIS
				((CPersonagemJogador *)personagem)->setPlayer(-1);

				dado[11] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
				dado[12] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

				((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[11]);
				((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[12]);

				break;
			}
		case LIDER:
			{
				int race = Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				switch((Raca)race)
				{
					case FORMIGA:
						{
							//monta o TanDan
							personagem = new CInimigo();

							break;
						}
					case BESOURO:
					case ARANHA:
					case LOUVADEUS:
					case ESCORPIAO:
					case VESPA:
						{
							personagem = new CNPC();

							break;
						}
				
				}
				break;
			}
		case MAE: //NPC
		case FILHOTE: //NPC
			{
				personagem = new CNPC();

				break;
			}
		case VENDEDOR: //Vendedor
			{
				personagem = new CVendedor();

				break;
			}
		case SOLDADO: //Inimigo
			{
				personagem = NULL;
				int race = Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
				{
					//se for inimigo
					personagem = new CInimigo();

					Raca r = (Raca)race;

					personagem->setRace(r);

					//TESTE
					//((CInimigo *) personagem)->setDestino(personagem->getPosition()->x,personagem->getPosition()->z);

				}
				else
				{
					//se for amigo
					personagem = new CNPC();
				}

				break;
			}
	}


	if(personagem != NULL)
	{
		personagem->setType((TypeClassChars) tipoPersonagem);
		personagem->set2DTexture(Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString()));
		personagem->set3DTexture(Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString()));
		personagem->setModel(Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString()));
	
		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		personagem->setID(dado[0]);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
		dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
		dado[2] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
		dado[3] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
		dado[4] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

		CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

		personagem->setBaseStats(tempHabilidades);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

		personagem->setRace((Raca)dado[0]);

		CBolsa * tempBolsa = new CBolsa();

		personagem->setBolsa(tempBolsa);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGNIVEL")]->ToString());

		personagem->setLevel(dado[0]);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

		personagem->setMoney(dado[0]);

		char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

		personagem->setName(nome);
				
		float posX = float(Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString()));
		float posZ = float(Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString()));

		personagem->setPosition(posX, posZ);

		/*float tempVel = float(Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

		personagem->setMoveSpeed(tempVel);*/

		float tempDir = float(Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
		personagem->setDirection(tempDir);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
		personagem->setRespawnTime(dado[0]);

		//FICA PRA DEPOIS
		personagem->setTarget(NULL);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIA")]->ToString());

		personagem->setXP(dado[0]);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGEXPERIENCIAMAX")]->ToString());

		personagem->setMaxXP(dado[0]);

		dado[0]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGTAXAATAQUE")]->ToString());
		dado[1]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPOCARGA")]->ToString());
		dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGDEFESA")]->ToString());
		dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODERMAX")]->ToString());
		dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDAMAX")]->ToString());
		dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESCORPO")]->ToString());
		dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANOCORPO")]->ToString());
		dado[7]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSPODER")]->ToString());
		dado[8]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGPONTOSVIDA")]->ToString());
		dado[9]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGATAQUESDISTANCIA")]->ToString());
		dado[10] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGDANODISTANCIA")]->ToString());

		personagem->getStats()->setAttackRate(dado[0]);
		personagem->getStats()->setChargeTime(dado[1]);
		personagem->getStats()->setDefense(dado[2]);
		personagem->getStats()->setMaxPM(dado[3]);
		personagem->getStats()->setMaxPV(dado[4]);
		personagem->getStats()->setMeleeAttack(dado[5]);
		personagem->getStats()->setMeleeDamage(dado[6]);
		personagem->getStats()->setPM(dado[7]);
		personagem->getStats()->setPV(dado[8]);
		personagem->getStats()->setRangedAttack(dado[9]);
		personagem->getStats()->setRangedDamage(dado[10]);

		personagem->setState(E_PARADO);
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
	String ^ query;

	query = L"SELECT P.PGID FROM PERSONAGEM P, JOGADOR_PERSONAGEM JP WHERE P.PGID = JP.PGID AND JP.JDID = "+idJogador;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Personagem para o jogador = "+idJogador;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado;

	CPersonagem * personagem;

	for(int i = 0; i < (int)numRegs; i++)
	{
		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		personagem = getPersonagem(dado);

		CBolsa * tempBolsa = getBolsaPersonagem(personagem->getID());

		personagem->setBolsa(tempBolsa);

		Lista.addPersonagem(personagem);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}
	}

	return Lista;
	
}


/*
	Obtem uma lista de personagens do tipo, ra�a, e se � um persoangem base
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual ra�a ele pertence TODAS, NENHUMA, ARANHA
	@param personagemBase -> se � um personagem que tem atributos base
	@return -> lista de personagem
*/
CPeopleList * CDataManager::getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;
	String ^ complemento;

	if(idRaca != ALLRACE && idRaca != NONERACE)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}


	query = 	L"SELECT P.PGID FROM PERSONAGEM P WHERE "+complemento				
				+" P.PGISBASE = "+personagemBase
				+" AND P.PGTIPOPERSONAGEM = "+idTipoPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CPeopleList * Lista = new CPeopleList();
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o Persoangem de Tipo"+idTipoPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado;


	for(int i = 0; i < (int)numRegs; i++)
	{

		CPersonagem * personagem;

		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		personagem = getPersonagem(dado);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		Lista->addPersonagem(personagem);
	}

	return Lista;

}
/*
	Obtem uma lista de personagens do tipo e ra�a
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual ra�a ele pertence TODAS, NENHUMA, ARANHA
	@param idCenario-> cenario onde ele est�
	@return -> lista de personagem
*/
CPeopleList * CDataManager::getPersonagem(int idTipoPersonagem, int idRaca, int idCenario)
{

	CPeopleList * tempList = new CPeopleList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;
	String ^ complemento = L" ";
	if(idRaca != ALLRACE && idRaca != NONERACE)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}

	query = L"SELECT P.PGID, PC.* FROM PERSONAGEM P, PERSONAGEM_CENARIO PC "
		    +"WHERE P.PGID = PC.PGID AND   "
			+"PC.CNID =  "+idCenario+" AND "
			+complemento
			+"P.PGTIPOPERSONAGEM = "+idTipoPersonagem;
		
	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o Tipo de Personagem "+idTipoPersonagem+" no cen�rio "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return tempList;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado;


	for(int i = 0; i < (int)numRegs; i++)
	{
		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		CPersonagem * personagem;

		personagem = getPersonagem(dado);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		tempList->addPersonagem(personagem);
	}

	return tempList;	
}

	
/*
	Obtem uma lista de personagens do tipo e ra�a
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual ra�a ele pertence TODAS, NENHUMA, ARANHA
	@return -> lista de personagem
*/
CPeopleList CDataManager::getPersonagem(int idTipoPersonagem, int idRaca)
{
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;
	String ^ complemento;
	if(idRaca != ALLRACE && idRaca != NONERACE)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}

	query = 	L"SELECT P.PGID FROM PERSONAGEM P WHERE "
				+complemento
				+" P.PGTIPOPERSONAGEM = "+idTipoPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CPeopleList Lista;
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o Personagem de Tipo "+idTipoPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		return Lista;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado;


	for(int i = 0; i < (int)numRegs; i++)
	{

		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

		CPersonagem * personagem;

		personagem = getPersonagem(dado);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
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
	String ^ query;

	query = L"SELECT * FROM ITEMBASE WHERE ITID = "+id;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	CItem * item;
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Personagem com este id = "+id;
		WarBugsLog::_log->Items->Add(texto);		
		return NULL;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];


	int tipoItem = Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());


	switch(tipoItem)
	{
		case USO:
			{
				int tipoUso = Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPOUSO")]->ToString());

				dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITVALOR")]->ToString());
				bool b1 = Int32::Parse(dados[nomeCampos->IndexOf(L"ITISTEMP")]->ToString());
				dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURACAO")]->ToString());

				item = new CConsumableItem();

				((CConsumableItem *)item)->setAtribute((Atrib)tipoUso);
				((CConsumableItem *)item)->setValue(dado[0]);
				((CConsumableItem *)item)->setTemp(b1);
				((CConsumableItem *)item)->setDuration(dado[1]);

				break;
			}
		case ARMA: 
			{

				dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
				dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
				dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
				dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
				dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
				dado[7]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
				dado[8]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				dado[9]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

				item = new CWeapon();

				((CWeapon *)item)->setAll((Raca)dado[2],dado[3],dado[4],dado[5],dado[6],dado[7],dado[8],dado[9]);

				break;
			}
		case ARMADURA: 
			{
				dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITRACA")]->ToString());
				dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
				dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITNIVELMAGICO")]->ToString());

				item = new CArmor();

				((CArmor *)item)->setAll((Raca)dado[2],dado[3],dado[4],dado[5]);

				break;
			}
		case QUEST: 
			{
				item = new CQItem();
				item->setEstado(NAMOCHILA);

				break;
			}
		case SCROLL: 
			{

				dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITMODIFICADOR")]->ToString());
				dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMIN")]->ToString());
				dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDANOMAX")]->ToString());
				dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITVELOCIDADE")]->ToString());
				dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITALCANCE")]->ToString());
				dado[7]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDEFESA")]->ToString());
				dado[8]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDURABILIDADE")]->ToString());
				
				item = new CScroll();
				((CScroll *)item)->setAll(dado[2],dado[3],dado[4],dado[5],dado[6],dado[7],dado[8]);

				break;
			}
		case LSCROLL: 
			{
				dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALBESOURO")]->ToString());
				dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALLOUVA")]->ToString());
				dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALESCORPIAO")]->ToString());
				dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALARANHA")]->ToString());
				dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITLEALVESPA")]->ToString());

				item = new CLoyaltyScroll();
				((CLoyaltyScroll *)item)->setAllLoyalties(dado[3],dado[4],dado[5],dado[2],dado[6]);

				break;
			}

	}

	if(item != NULL)
	{
		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
		item->setID(dado[0]);

		item->setBaseID((TypeItens)dado[0]);

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDMODELO")]->ToString());
		dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTEXTURA")]->ToString());
		dado[2] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDHUD")]->ToString());

		item->set2DTexture(dado[2]);
		item->set3DTexture(dado[1]);
		item->setModel(dado[0]);	
	
		dado[0]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITIDTIPOITEM")]->ToString());
		dado[1]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITPRECO")]->ToString());

		bool b2  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITDROPAVEL")]->ToString());

		item->setType((TipoItem)dado[0]);
		item->setPrice(dado[1]);
		item->setDropable(b2);

		item->setEstado(NAMOCHILA);
	}


	return item;	
}

/*
	Atribui o item passado para o personagem passado
	@param idPersonagem
	@param iditem -> id Base do item
	@return -> item que foi passado com os novos atributos
*/
CItem * CDataManager::relacionaItemPersonagem(int idPersonagem, int idBaseItem)
{
	
	String ^ query;

	query = L"INSERT INTO ITEM_RELACIONAL(PGID, ITID) VALES ("
			+idPersonagem+","+idBaseItem+")";

	//se o registro n�o foi inserido
	if(!_dataBase->insertNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel relacionar o item "+idBaseItem+" com o personagem "+idPersonagem);
		return NULL;
	}
	

	TDadosBD ^ dados      = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	//seleciona o id ultimo item incluido
	query = L"SELECT MAX(IRID) FROM ITEM_RELACIONAL";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	//se o registro n�o foi selecionado
	if(numRegs == 0 || numCampos == 0)
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel criar um objeto para o relacionamento do item "+idBaseItem
			                         +" com o personagem "+idPersonagem);
		return NULL;
	}

	//remove o nome do campo
	dados->RemoveAt(0);

	CItem * newItem = getItem(idBaseItem);

	if(newItem == NULL)
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel criar um objeto para o relacionamento do item "+idBaseItem
			                         +" com o personagem "+idPersonagem);
		return NULL;
	}

	//coloca o novo id para o item
	newItem->setID(Int32::Parse(dados[0]->ToString()));
	newItem->setBaseID((TypeItens)idBaseItem);

	return newItem;
}


/*
	Obtem a arma que o personagem est� equipado
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
	String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE "
		    +"IR.PGID = P.PGID AND P.PGIDWEAPON = IR.IRID AND "
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o equipamento do Personagem "+idPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		arma = new CWeapon();
		arma->setID(-1);
		return arma;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];

	dado[0]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
	dado[1]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());
	dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
	dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS1")]->ToString());
	dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS2")]->ToString());
	dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS3")]->ToString());
	dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS4")]->ToString());
	dado[7]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS5")]->ToString());
	dado[8]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS6")]->ToString());
	dado[10] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRDURABILIDADE")]->ToString());

	dado[11] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRID")]->ToString());

	/*
	modificador
	dano minimo
	dano maximo
	alcance
	velocidade
	durabilidade
	*/

	arma = (CWeapon *)getItem(dado[0]);

	CWeapon * armaResposta = new CWeapon(arma->getBaseID(),
										 arma->getEstado(),
										 arma->getPrice(),
										 arma->isDropable(),
										 arma->getRace(),
										 arma->getMod()+dado[3],
										 arma->getMinDamage()+dado[4],
										 arma->getMaxDamage()+dado[5],
										 arma->getRange()+dado[6],
										 arma->getSpeed()+dado[7],
										 arma->getDurability()+dado[10],
										 arma->getMagicLevel()
										 );

	armaResposta->setID(dado[11]);
	armaResposta->set2DTexture(arma->get2DTexture());
	armaResposta->set3DTexture(arma->get3DTexture());
	armaResposta->setModel(arma->getModel());

	return armaResposta;
}
/*
	Obtem a armadura que o personagem est� equipado
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
	String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE "
		    +"IR.PGID = P.PGID AND P.PGIDARMOR = IR.IRID AND "
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado a Armadura do Personagem "+idPersonagem;
		WarBugsLog::_log->Items->Add(texto);		
		armadura = new CArmor();
		armadura->setID(-1);
		return armadura;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	int dado[15];

	dado[0]  = Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
	dado[1]  = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());
	dado[2]  = Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
	dado[3]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS1")]->ToString());
	dado[4]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS2")]->ToString());
	dado[5]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS3")]->ToString());
	dado[6]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS4")]->ToString());
	dado[7]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS5")]->ToString());
	dado[8]  = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS6")]->ToString());
	dado[10] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRDURABILIDADE")]->ToString());
	dado[11] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRID")]->ToString());


	/*
	defesa
	durabilidade
	*/

	armadura = (CArmor *)getItem(dado[0]);

	CArmor * armaduraResposta = new CArmor(armadura->getBaseID(),
										 armadura->getEstado(),
										 armadura->getPrice(),
										 armadura->isDropable(),
										 armadura->getRace(),
										 armadura->getDef()+dado[3],
										 armadura->getDurability()+dado[10],
										 armadura->getMagicLevel()
										 );

	armaduraResposta->setID(dado[11]);
	armaduraResposta->set2DTexture(armadura->get2DTexture());
	armaduraResposta->set3DTexture(armadura->get3DTexture());
	armaduraResposta->setModel(armadura->getModel());

	return armaduraResposta;
}

//Obter Cenarios
/*
	Obtem todos os cen�rios do jogo
	@return -> o lista de cenarios
*/

CCenarioList * CDataManager::getListCenario()
{
	CCenarioList * listCenario = new CCenarioList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT * FROM CENARIO";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Cen�rio!";
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

		int idcenario = Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());
		
		CPeopleList * listaInimigos = getPersonagem( SOLDADO, ALLRACE, idcenario);
		CPeopleList * listaPersonagem = new CPeopleList();
		CPeopleList * listaNPC = new CPeopleList();
		CPeopleList * listaVendedores = new CPeopleList();
		CBolsaList  * listaBolsas = getListBolsa(idcenario);
		CPortal * portalSul = getPortal(idcenario,D_SOUTH);
		CPortal * portalNorte = getPortal(idcenario,D_NORTH);
		CPortal * portalOeste = getPortal(idcenario,D_WEST);
		CPortal * portalLeste = getPortal(idcenario,D_EAST);

		CCenario * cenarioTemp = new CCenario(idcenario, listaPersonagem, listaInimigos, listaNPC, listaVendedores, listaBolsas, portalNorte, portalSul, portalOeste, portalLeste);

		for(int k = 0; k < listaInimigos->size(); k++)
		{
			cenarioTemp->getMonsterAt(k)->setScene(cenarioTemp);
		}

		listCenario->addCenario(cenarioTemp);

		for(int j = 0; j < (int)numCampos; j++)
		{
			dados->RemoveAt(0);
		}		
		
	}
	

	return listCenario;
}

/*
	Retorna o id do cen�rio em que o jogador estava na �ltima vez
	@param idPersonagem -> id do Personagem que o jogador estava usando
	@param idJogador -> Id do jogador
	return id do cenario
*/
int	CDataManager::getCenarioId(int idPersonagem, int idJogador)
{
	int idCenario = -1;

	CCenarioList * listCenario = new CCenarioList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT C.CNID FROM CENARIO C, PERSONAGEM_CENARIO PC, JOGADOR_PERSONAGEM JP "
		    +"WHERE PC.PGID = JP.PGID AND C.CNID  = PC.CNID AND "
			+"JP.JDID = "+idJogador
			+" AND JP.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Cen�rio!";
		WarBugsLog::_log->Items->Add(texto);		
		return -1;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	idCenario = Int32::Parse(dados[0]->ToString());

	return idCenario;
}


//Obter Bolsa
CBolsa * CDataManager::getBolsa(int id)
{
	//CBolsa * bolsa;

	return NULL;
}
/*
	Obtem os itens que o personagem estava no invent�rio(os equipados n�o)
	@param idPersonagem -> o id do personagem
	@return -> invent�rio do personagem
*/
CBolsa * CDataManager::getBolsaPersonagem(int idPersonagem)
{
	CBolsa * bolsa = new CBolsa();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1, IR.IRPRECO, IR.IRVALBONUS2, IR.IRVALBONUS3, IR.IRVALBONUS4,"
            +" IR.IRVALBONUS5, IR.IRVALBONUS6, IR.IRID, IR.IRDURABILIDADE "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, PERSONAGEM P "
			+"WHERE "
			+" I.ITID = IR.ITID AND IR.PGID =  P.PGID AND IR.IRID <> P.PGIDARMOR AND IR.IRID <> P.PGIDWEAPON"
			+"AND IR.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado nenhum Personagem com este id = "+idPersonagem;
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

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
		item = getItem(dado[0]);

		int tipoItem = Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());

		dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS1")]->ToString());
		dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS2")]->ToString());
		dado[2] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS3")]->ToString());
		dado[3] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS4")]->ToString());
		dado[4] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS5")]->ToString());
		dado[5] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS6")]->ToString());
		dado[6] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRDURABILIDADE")]->ToString());
		dado[7] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRID")]->ToString());

		item->setID(dado[7]);
		item->setDurability(dado[6]);

		switch((TipoItem)tipoItem)
		{
			case USO:
				{
				
				
					break;
				}
			case ARMA: 
				{

					((CWeapon *)item)->setID(dado[7]);
					((CWeapon *)item)->setAll(((CWeapon *)item)->getRace(),dado[0],dado[1],dado[2],dado[3],dado[4],dado[6],dado[5]);

					break;
				}
			case ARMADURA: 
				{
					((CArmor *)item)->setID(dado[7]);
					((CArmor *)item)->setAll(((CArmor *)item)->getRace(),dado[0],dado[6],dado[1]);

					break;
				}
			case QUEST: 
				{


					break;
				}
			case SCROLL: 
				{

					break;
				}
			case LSCROLL: 
				{

					break;
				}

		}

		bolsa->addItem(item);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}
	}


	return bolsa;
}

/*
	Obtem as bolsas com os itens que estiverem no cen�rio
	@param idCenario -> o cen�rio que ser� pego as bolsas
	@return -> lista de bolsas do cen�rio
*/
CBolsaList * CDataManager::getListBolsa(int idCenario)
{
	CBolsaList * listaBolsa = new CBolsaList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1,IR.IRPRECO,IR.IRVALBONUS2,IR.IRVALBONUS3,IR.IRVALBONUS4,"
            +"IR.IRVALBONUS5,IR.IRVALBONUS6,IR.IRDURABILIDADE, IR.IRID, B.BSID,B.BSX,B.BSY,B.BSZ "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, BOLSA B "
			+"WHERE "
			+"I.ITID = IR.ITID AND IR.BSID =  B.BSID AND B.CNID = "+idCenario+" "
			+"ORDER BY B.BSID";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado as bolsas do cen�rio "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return listaBolsa;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}	

	for(int i = 0; i < (int)numRegs; i++)
	{
		CBolsa bolsa;

		int idBolsa = Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
		int idBolsaAnterior = Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());

		bolsa.setID(idBolsa);

		while(idBolsa == idBolsaAnterior)
		{

			CItem * item;
			int dado[15];
			dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
			
			item = getItem(dado[0]);

			int tipoItem = Int32::Parse(dados[nomeCampos->IndexOf(L"ITTIPO")]->ToString());

			dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS1")]->ToString());
			dado[1] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS2")]->ToString());
			dado[2] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS3")]->ToString());
			dado[3] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS4")]->ToString());
			dado[4] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS5")]->ToString());
			dado[5] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRVALBONUS6")]->ToString());
			dado[6] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRDURABILIDADE")]->ToString());
			dado[7] = Int32::Parse(dados[nomeCampos->IndexOf(L"IRID")]->ToString());

			switch((TipoItem)tipoItem)
			{
				case USO:
					{
						break;
					}
				case ARMA: 
					{

						((CWeapon *)item)->setID(dado[7]);
						((CWeapon *)item)->setAll(((CWeapon *)item)->getRace(),dado[0],dado[1],dado[2],dado[3], dado[4],dado[6],dado[5]);

						break;
					}
				case ARMADURA: 
					{
						((CArmor *)item)->setID(dado[7]);
						((CArmor *)item)->setAll(((CArmor *)item)->getRace(), dado[0], dado[6], dado[1]);

						break;
					}
				case QUEST: 
					{

						break;
					}
				case SCROLL: 
					{

						break;
					}
				case LSCROLL: 
					{

						break;
					}

			}

			float tempX = float(Double::Parse(dados[nomeCampos->IndexOf(L"BSX")]->ToString()));
			float tempY = float(Double::Parse(dados[nomeCampos->IndexOf(L"BSY")]->ToString()));
			float tempZ = float(Double::Parse(dados[nomeCampos->IndexOf(L"BSZ")]->ToString()));

			bolsa.setPosition(tempX,tempZ);

			bolsa.addItem(item);

			for(int j = 0; j < (int)numCampos; j++)
			{
				dados->RemoveAt(0);
			}

			//se for o ultimo registro ele n�o ter� dados para retornar dentro de dados
			if(i < (int) (numRegs-1))
			{
				idBolsaAnterior = Int32::Parse(dados[nomeCampos->IndexOf(L"BSID")]->ToString());
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

CJogador CDataManager::getJogador(char * login)
{
	CJogador jogador;

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;
	String ^ temp = gcnew String(login);

	query = L"SELECT * FROM JOGADOR WHERE JDLOGIN = \""+temp+"\"";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o Jogador com Login "+temp;
		WarBugsLog::_log->Items->Add(texto);		
		jogador.setID(-1);
		return jogador;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	jogador.setID(Int32::Parse(dados[nomeCampos->IndexOf(L"JDID")]->ToString()));
	jogador.setBirthdate(toChar(dados[nomeCampos->IndexOf(L"JDDATANASC")]->ToString()));
	jogador.setEmail(toChar(dados[nomeCampos->IndexOf(L"JDEMAIL")]->ToString()));
	jogador.setPassword(toChar(dados[nomeCampos->IndexOf(L"JDSENHA")]->ToString()));
	jogador.setName(toChar(dados[nomeCampos->IndexOf(L"JDNOME")]->ToString()));
	jogador.setLogin(toChar(dados[nomeCampos->IndexOf(L"JDLOGIN")]->ToString()));

	return jogador;
}
	

/*
	Obtem o portal do cen�rio passado e da dire��o passada
	@param idCenario -> id do cen�rio
	@param direcao -> direcao
	@return -> o portal
*/
CPortal * CDataManager::getPortal(int idCenario, TypeDirecao direcao)
{
	CPortal * portal = new CPortal();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;
	int tempInt = (int)direcao;

	query = L"SELECT P.* FROM PORTAL P, PORTAL_CENARIO PC "
			+"WHERE P.PTID = PC.PTID AND "
			+"P.PTDIRECAO = "+tempInt
			+" AND PC.CNID = "+idCenario;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi encontrado o Portal para "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return portal;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	portal = new CPortal(Int32::Parse(dados[nomeCampos->IndexOf(L"PTID")]->ToString()),
						 Int32::Parse(dados[nomeCampos->IndexOf(L"PTIDCENARIODEST")]->ToString()),
						 float(Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTX")]->ToString())),
					     float(Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTZ")]->ToString())));


	portal->setPosition(float(Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCX")]->ToString())),
					   float(Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCZ")]->ToString())));



	return portal;
}


//Login
/*
	processa as informa��es de login e verifica se o usu�rio e senha passados s�o v�lidos
	@param login -> login do usu�rio
	@param senha -> senha do usu�rio
	@param jogador -> o objeto jogador que ser� retornado caso as informa��es estejam corretas
	@retun -> se usuario e senha s�o v�lidos retorna true
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
long  CDataManager::novoIdPersonagem()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	String ^ query;

	query = L"SELECT MAX(PGID) NOVOID FROM PERSONAGEM";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi poss�vel contar os Personagens";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	result = Int32::Parse(dados[0]->ToString());

	return result+1;
}

long  CDataManager::novoIdBolsas()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	String ^ query;

	query = L"SELECT MAX(BSID) NOVOID FROM BOLSA";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi poss�vel contar as Bolsas";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	result = Int32::Parse(dados[0]->ToString());

	return result+1;
}

long  CDataManager::novoIdItens()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	String ^ query;

	query = L"SELECT MAX(ITID)NOVOID FROM ITEMBASE";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi poss�vel contar os Personagens";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		dados->RemoveAt(0);
	}

	result = Int32::Parse(dados[0]->ToString());

	return result+1;
}

//ATUALIZA��ES
//Personagem
void CDataManager::updatePersonagem(int id, float posX, float posZ)
{}

void CDataManager::updatePersonagem(int id, int nivel, int xp)
{}

//Inser��es
bool CDataManager::insertPersonagemJogador(CPersonagemJogador * p1, int idJogador)
{
	bool result = false;

	String ^ query;
	String ^ temp;
	
	p1->setID(novoIdPersonagem());

	temp = gcnew String(p1->getName());

	int tempRaca = p1->getRace();

	String ^ moveSpeed = L""+p1->getMoveSpeed();
	moveSpeed = pointFormat(moveSpeed);

	String ^ direction = L""+p1->getDirection();
	direction = pointFormat(direction);

	String ^ x = L""+p1->getPosition()->x;
	x = pointFormat(x);

	String ^ z = L""+p1->getPosition()->z;
	z = pointFormat(z);


	query = L"INSERT INTO PERSONAGEM "
			//+"(PGID,PGNOME,PGNIVEL,PGDINHEIRO,PGEXPERIENCIA,PGEXPERIENCIAMAX,PGPONTOSVIDA,PGPONTOSVIDAMAX,"
			//+"PGPONTOSPODER,PGPONTOSPODERMAX,PGDIRECAO,PGVELOCIDADE,PGRACA,PGTEMPORESPAW,PGFORCA,PGAGILIDADE,PGDESTREZA,"
			//+"PGRESISTENCIA,PGINSTINTO,PGATAQUESDISTANCIA,PGATAQUESCORPO,PGDANOCORPO,PGDANODISTANCIA,PGDEFESA,PGTAXAATAQUE,"
			//+"PGTEMPOCARGA,PGTIPOPERSONAGEM,PGLEALARANHA,PGLEALBESOURO,PGLEALESCORPIAO,PGLEALLOUVA,PGLEALVESPA,PGIDARMOR,"
			//+"PGIDWEAPON,PGX,PGZ,PGY,PGIDTEXTURA,PGIDMODELO,PGBONUSPOINTSPRIMARIAS,PGBONUSPOINTSPODER,PGISBASE, PGIDHUD)"
			+" VALUES ("+
			p1->getID()+",\""+
			temp+"\","+
			p1->getLevel()+","+
			p1->getMoney()+","+
			p1->getXP()+","+
			p1->getMaxXP()+","+
			p1->getStats()->getPV()+","+
			p1->getStats()->getMaxPV()+","+
			p1->getStats()->getPM()+","+
			p1->getStats()->getMaxPM()+","+
			direction+","+
			moveSpeed+","+
			tempRaca+","+
			p1->getRespawnTime()+","+
			p1->getFOR()+","+
			p1->getAGI()+","+
			p1->getDES()+","+
			p1->getRES()+","+
			p1->getINS()+","+
			p1->getStats()->getRangedAttack()+","+
			p1->getStats()->getMeleeAttack()+","+
			p1->getStats()->getMeleeDamage()+","+
			p1->getStats()->getRangedDamage()+","+
			p1->getStats()->getDefense()+","+
			p1->getStats()->getAttackRate()+","+
			p1->getStats()->getChargeTime()+","+
			(int)JOGADOR+","+
			p1->getLoyalty()->getLoyaltyToSpider()+","+
			p1->getLoyalty()->getLoyaltyToBeetle()+","+
			p1->getLoyalty()->getLoyaltyToScorpion()+","+
			p1->getLoyalty()->getLoyaltyToMantis()+","+
			p1->getLoyalty()->getLoyaltyToWasp()+","+
			p1->getEquip()->armadura->getID()+","+
			p1->getEquip()->arma->getID()+","+
			x+","+
			z+",0,"+
			p1->get3DTexture()+","+
			p1->getModel()+","+
			p1->getPointsLeft()+","+
			p1->getSkillPointsLeft()+",0,"+
			p1->get2DTexture()+");";

	
	String ^texto;

	//se n�o for inserido com sucesso
	if(_dataBase->insertNow(toChar(query)))
	{
		texto = L"Personagem '"+temp+"' Inclu�do com sucesso";

		query = L"INSERT INTO JOGADOR_PERSONAGEM "
				+" VALUES ("+p1->getID()+","+idJogador+")";

		
		//se n�o for inserido com sucesso
		if(_dataBase->insertNow(toChar(query)))
		{
			texto = L"Personagem '"+temp+"' Inclu�do com sucesso";



			int idCenarioVila;
			idCenarioVila = getCenarioId(p1->getRace());

			if(idCenarioVila > -1)
			{

				//inclui o personagem no cen�rio da vila correspondente a dele
				query = L"INSERT INTO PERSONAGEM_CENARIO(CNID,PGID) VALUES("+idCenarioVila+","+p1->getID()+")";
				if(_dataBase->insertNow(toChar(query)))
				{}
			}



			result = true;
		}
		else
		{
			texto = L"N�o foi possivel incluir o personagem '"+temp+"'.";
		}

		WarBugsLog::_log->Items->Add(texto);	

	}
	else
	{
		texto = L"N�o foi possivel incluir o personagem '"+temp+"'.";
	}

	WarBugsLog::_log->Items->Add(texto);

	return result;

}

void CDataManager::insertPersonagem(CPeopleList p1)
{}


/*
	Retorna a quantidade de persoangens que um jogador possui
	@param idJogador-> id do jogador que ser� consultado
*/
int CDataManager::qtdPersonagemJogador(int idJogador)
{
	int result = 0;

	TDadosBD ^ dados      = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	String ^ query;

	query = L"SELECT COUNT(PGID) FROM JOGADOR_PERSONAGEM WHERE JDID = "+idJogador;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"N�o foi poss�vel contar os Personagens do Jogador "+idJogador;
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}	
	
	
	for(int i = 0; i < (int)numCampos; i++)
	{
		dados->RemoveAt(0);
	}

	result = Int32::Parse(dados[0]->ToString());

	return result;	
}

/*
	Exclui um personagem que o jogador n�o desejar mais
	@param idJogador -> id do jogador qe quer exluir o personagem
	@param idPersonagem -> id do personagem que ser� exluido
	@param nomePersonagem -> nome Personagem que ser� excluido
	
*/
bool CDataManager::deletePersonagemJogador(int idJogador, int idPersonagem, char * nomePersonagem)
{
	bool result = false;

	String ^ query;
	String ^ temp;
	
	temp = gcnew String(nomePersonagem);


	query = L"DELETE FROM JOGADOR_PERSONAGEM JP"
			+" USING JOGADOR_PERSONAGEM JP, PERSONAGEM P"
			+" WHERE JP.PGID = P.PGID AND JP.JDID = "+idJogador
			+" AND P.PGID = "+idPersonagem
			+" AND P.PGNOME = '"+temp+"'";

	
	String ^texto;

	//se n�o for EXCLUIDO com sucesso
	if(_dataBase->deleteNow(toChar(query)))
	{
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PGID = "+idPersonagem;
		
		//se n�o for EXCLUIDO com sucesso
		if(_dataBase->deleteNow(toChar(query)))
		{
			texto = L"Os Itens do personagem '"+temp+"' foram excluido com sucesso";
			result = true;
		}
		else
		{
			texto = L"N�o foi possivel excluir os itens do personagem '"+temp+"'.";
		}

		query = L"DELETE FROM PERSONAGEM WHERE PGID = "+idPersonagem;
		
		//se n�o for inserido com sucesso
		if(_dataBase->deleteNow(toChar(query)))
		{
			texto = L"Personagem '"+temp+"' excluido com sucesso";
			result = true;
		}
		else
		{
			texto = L"N�o foi possivel excluir o personagem '"+temp+"'.";
		}

	}
	else
	{
		texto = L"N�o foi possivel exluir o personagem '"+temp+"'.";
	}

	WarBugsLog::_log->Items->Add(texto);

	return result;

}

/*
	Transforma ',' em '.'
*/
String ^ CDataManager::pointFormat(String ^ d1)
{
	char * c = toChar(d1);

	for(int i = 0; i < (int)strlen(c); i++)
	{
		if(c[i] == ',')
		{
			c[i] = '.';
		}
	}

	d1 = gcnew String(c);

	return d1;

}

/*
	Salvar� todas as informa��es que est�o na mem�ria, para o servidor
*/
void CDataManager::backupAll(CCenarioList * cenarioList)
{

	// 1. Salva Persoangens
		// 1.1 Update do personagem e todas as suas variaveis
	    // 1.2 Atualiza a Localiza��o de todos os Personagens
	// 2. Salva Itens Personagens
		// 2.1 Remove todos os itens que ele possuia no BD
		// 2.3 Insere todos os itens que o persoangem possui no jogo
	// 3. Salva Poderes do Personagem
		// 3.1 Atualiza as informa��es dos poderes que o personagem possui
	// 4. Salva Informa��es da formula de mercado se o personagem for o vendedor
		// 4.1 Insere as informa��es que o vendedor possui naquele momento
	// 5. Salva as bolsas
		// 5.1 Remove as que n�o existirem mais
		// 5.2 Atualiza as que ainda existirem
		// 5.3 Insere as que n�o est�o salvas
	// 6.Salva os itens que os inimigos possuem com eles

	for(int p = 0; p < cenarioList->size(); p++)
	{
		// salva os personagens jogadores
		for(int a = 0; a < cenarioList->getElementAt(p)->playerCount(); a++)
		{
			updatePersonagemJogador(cenarioList->getElementAt(p)->getPlayerAt(a));		
		}

		//salva as bolsas dos cen�rios
		for(int u = 0; u < cenarioList->getElementAt(p)->bagCount(); u++)
		{
			updateBolsa(cenarioList->getElementAt(p)->getBagAt(u),cenarioList->getElementAt(p)->getID());
		}

		//salva os itens dos monstros
		for(int l = 0; l < cenarioList->getElementAt(p)->monsterCount(); l++)
		{
			updatePersonagem(cenarioList->getElementAt(p)->getMonsterAt(l));
		}

		//salva os itens dos NPCS
		for(int h = 0; h < cenarioList->getElementAt(p)->NPCCount(); h++)
		{
			updatePersonagem(cenarioList->getElementAt(p)->getNpcAt(h));
		}

		//salva os itens do vendedor
		for(int e = 0; e < cenarioList->getElementAt(p)->salesmanCount(); e++)
		{
			updatePersonagem(cenarioList->getElementAt(p)->getSalesmanAt(e));
		}


	}


}

/*
	Atualiza todos os itens que est�o relacionados com os inimigos
	param b1->
*/

/*
	Atualiza todas as bolsa que estiverem no cen�rio
	param b1 -> bolsa que esr� atualizada no BD
*/
void CDataManager::updateBolsa(CBolsa * b1, int idCenario)
{
	String ^ query;

	int tempItem[9][8];

	query = L"DELETE FROM ITEM_RELACIONAL WHERE BSID = "+b1->getID();

	_dataBase->deleteNow(toChar(query));

	query = L"DELETE FROM BOLSA WHERE BSID = "+b1->getID();

	_dataBase->deleteNow(toChar(query));

	query = L"INSERT INTO BOLSA VALUES ("+novoIdBolsas()+","+pointFormat(L""+b1->getPosition()->x)+",0,"
		+pointFormat(L""+b1->getPosition()->z)+","+idCenario+")";

	_dataBase->insertNow(toChar(query));

	
	for(int p = 0; p < b1->size(); p++)
	{
		if(b1->getElementAt(p) != NULL)
		if(b1->getElementAt(p)->getID() != NULL)
		{
		
			insereItemRelacional(b1->getElementAt(p),b1->getID());

		}

	}
}

/*
	Atualiza o personagem no BD, juntamente com seus itens e cen�rio onde ele est�
	param p1-> personagem que ser� atualizado	
*/
void CDataManager::updatePersonagemJogador(CPersonagemJogador * p1)
{
	//atualiza o personagem
	String ^ query;

	query = L"UPDATE PERSONAGEM SET "
			+"  PGNIVEL = "+p1->getLevel()
			+", PGDINHEIRO = "+p1->getMoney()
			+", PGEXPERIENCIA = "+p1->getXP()
			+", PGEXPERIENCIAMAX = "+p1->getMaxXP()
			+", PGPONTOSVIDA = "+p1->getStats()->getPV()
			+", PGPONTOSVIDAMAX = "+p1->getStats()->getMaxPV()
			+", PGPONTOSPODER = "+p1->getStats()->getPM()
			+", PGPONTOSPODERMAX = "+p1->getStats()->getMaxPM()
			+", PGDIRECAO = "+pointFormat(L""+p1->getDirection())
			+", PGVELOCIDADE = "+pointFormat(L""+p1->getMoveSpeed())
			+", PGFORCA = "+p1->getFOR()
			+", PGAGILIDADE = "+p1->getAGI()
			+", PGDESTREZA = "+p1->getDES()
			+", PGRESISTENCIA = "+p1->getRES()
			+", PGINSTINTO = "+p1->getINS()
			+", PGATAQUEDISTANCIA = "+p1->getStats()->getRangedAttack()
			+", PGATAQUECORPO = "+p1->getStats()->getMeleeAttack()
			+", PGDANOCORPO = "+p1->getStats()->getMeleeDamage()
			+", PGDANODISTANCIA = "+p1->getStats()->getRangedDamage()
			+", PGDEFESA = "+p1->getStats()->getDefense()
			+", PGTAXAATAQUE = "+p1->getStats()->getAttackRate()
			+", PGTEMPOCARGA = "+p1->getStats()->getChargeTime()
			+", PGLEALARANHA = "+p1->getLoyalty()->getLoyaltyToSpider()
			+", PGLEALBESOURO = "+p1->getLoyalty()->getLoyaltyToBeetle()
			+", PGLEALESCORPIAO = "+p1->getLoyalty()->getLoyaltyToScorpion()
			+", PGLEALLOUVA = "+p1->getLoyalty()->getLoyaltyToMantis()
			+", PGLEALVESPA = "+p1->getLoyalty()->getLoyaltyToWasp()
			+", PGIDARMOR = "+(p1->getEquip()->armadura != NULL ? p1->getEquip()->armadura->getID() : -1)
			+", PGIDWEAPON = "+(p1->getEquip()->arma != NULL ? p1->getEquip()->arma->getID() : -1)
			+", PGX = "+p1->getPosition()->x
			+", PGZ = "+p1->getPosition()->z
			+", PGBONUSPOINTSPRIMARIAS = "+p1->getPointsLeft()
			+", PGBONUSPOINTSPODER = "+p1->getSkillPointsLeft()
			+"  WHERE PGID = "+p1->getID();

	if(_dataBase->updateNow(toChar(query)))
	{

		//n�o esquecer que o item equipado tamb�m entra nesta lista
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PGID = "+p1->getID();
				
		//se exluiu os itens que n�o estavam com ele
		if(_dataBase->deleteNow(toChar(query)))
		{

			for(int p = 0; p < p1->getBolsa()->size(); p++)
			{
				if(p1->getBolsa()->getElementAt(p) != NULL)
				if(p1->getBolsa()->getElementAt(p)->getID() != NULL)
				{
					insereItemRelacional(p1->getBolsa()->getElementAt(p), p1->getID(), -1);					
				}
		
			}

			if(p1->getEquip() != NULL)
			if(p1->getEquip()->arma != NULL)
			if(p1->getEquip()->arma->getID() != NULL)
			{
				insereItemRelacional(p1->getEquip()->arma, p1->getID(), -1);
			}


			if(p1->getEquip() != NULL)
			if(p1->getEquip()->armadura != NULL)
			if(p1->getEquip()->armadura->getID() != NULL)
			{
				insereItemRelacional(p1->getEquip()->armadura, p1->getID(), -1);
			}
			
			//ATUALIZA O CEN�RIO NO JOGADOR SE ENCONTRA
			query = L"UPDATE PERSONAGEM_CENARIO SET CNID = "+p1->getScene()->getSceneID()
					+", PGID = "+p1->getID()+" WHERE PGID = "+p1->getID();

			_dataBase->updateNow(toChar(query));

		}
	}
			
}


/*
	Salva os itens dos inimigos no BD
	@param Personagem
*/
void CDataManager::updatePersonagem(CPersonagem * p1)
{
	//atualiza o personagem
	String ^ query;

	//deleta os itens que este personagem possui no BD
	query = L"DELETE FROM ITEM_RELACIONAL IR "
			+"USING ITEM_RELACIONAL IR, PERSONAGEM_CENARIO PC "
			+"WHERE PC.PCID = IR.PCID "
			+" AND PC.PGID = -1 "
			+" AND PC.PCID = "+p1->getID();

	// se houve erro na limpeza das tabelas
	if(!_dataBase->deleteNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel deletar os itens do personagem "+p1->getID());
		return;
	}

	//insere todos os itens que o personagem possui no jogo
	for(int p = 0; p < p1->getBolsa()->size(); p++)
	{
		if(p1->getBolsa()->getElementAt(p) != NULL)
		if(p1->getBolsa()->getElementAt(p)->getID() != NULL)
		{
			insereItemRelacional(p1->getBolsa()->getElementAt(p), -1, p1->getID());
		}
	}
}





/*
	Insere um item na tabela relacional
	@param item -> objeto item a ser inserido
	@param idPersonagem -> qual persoangem ser� relacionado
	@param iddeCenario -> qual cenario est� relacionado
*/
void CDataManager::insereItemRelacional(CItem * item, int idPersonagem, int iddeCenario)
{
	String ^ query;
	int tempNome = (int)item->getBaseID();

	switch(item->getType())
	{
		case ARMA:
			{

				query = L"INSERT INTO ITEM_RELACIONAL(ITID, PGID, PCID, IRDURABILIDADE, "
						+"IRVALBONUS1, IRVALBONUS2, IRVALBONUS3, IRVALBONUS4, "
						+"IRVALBONUS5, IRVALBONUS6) VALUES ( "
						+tempNome+", "+idPersonagem+", "+iddeCenario+", "+item->getDurability()+", "
						+((CWeapon *)item)->getMod()+", "+((CWeapon *)item)->getMinDamage()+", "+((CWeapon *)item)->getMaxDamage()+", "
						+((CWeapon *)item)->getSpeed()+", "+((CWeapon *)item)->getRange()+", "+((CWeapon *)item)->getMagicLevel()+")";

				break;
			}
		case ARMADURA:
			{
				query = L"INSERT INTO ITEM_RELACIONAL(ITID, PGID, PCID, IRDURABILIDADE, "
						+"IRVALBONUS1, IRVALBONUS2) VALUES ( "
						+tempNome+", "+idPersonagem+", "+iddeCenario+", "+item->getDurability()+", "
						+((CArmor *)item)->getDef()+", "+((CArmor *)item)->getMagicLevel()+")";

				break;
			}
		case QUEST:
		case LSCROLL:
		case SCROLL:
		case USO:
			{
				query = L"INSERT INTO ITEM_RELACIONAL(ITID, PGID, PCID, IRDURABILIDADE) VALUES ( "
						+tempNome+", "+idPersonagem+", "+iddeCenario+", "+item->getDurability()+")";
				break;
			}
	}


	if(!query  || !_dataBase->insertNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel inserir o relacionamento entre personagem e item");
		return;		
	}

}

/*
	Insere um item na tabela relacional
	@param item -> objeto item a ser inserido
	@param idBolsa -> qual bosla ser� relacionado
*/
void CDataManager::insereItemRelacional(CItem * item, int idBolsa)
{
	String ^ query;

	int tempNome = (int)item->getBaseID();

	switch(item->getType())
	{
		case ARMA:
			{

				query = L"INSERT INTO ITEM_RELACIONAL(ITID, BSID, IRDURABILIDADE, "
						+"IRVALBONUS1, IRVALBONUS2, IRVALBONUS3, IRVALBONUS4, "
						+"IRVALBONUS5, IRVALBONUS6) VALUES ( "
						+tempNome+", "+idBolsa+", "+item->getDurability()+", "
						+((CWeapon *)item)->getMod()+", "+((CWeapon *)item)->getMinDamage()+", "+((CWeapon *)item)->getMaxDamage()+", "
						+((CWeapon *)item)->getSpeed()+", "+((CWeapon *)item)->getRange()+", "+((CWeapon *)item)->getMagicLevel()+")";

				break;
			}
		case ARMADURA:
			{
				query = L"INSERT INTO ITEM_RELACIONAL(ITID, BSID, IRDURABILIDADE, "
						+"IRVALBONUS1, IRVALBONUS2) VALUES ( "
						+tempNome+", "+idBolsa+", "+item->getDurability()+", "
						+((CArmor *)item)->getDef()+", "+((CArmor *)item)->getMagicLevel()+")";

				break;
			}
		case QUEST:
		case LSCROLL:
		case SCROLL:
		case USO:
			{
				query = L"INSERT INTO ITEM_RELACIONAL(ITID, BSID, IRDURABILIDADE) VALUES ( "
						+tempNome+", "+idBolsa+", "+item->getDurability()+")";
				break;
			}
	}


	if(!query  || !_dataBase->insertNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"N�o foi poss�vel inserir o relacionamento entre personagem e item");
		return;		
	}

}

/*
	Retorna o id do cen�rio das Vilas
	@param race-> raca da vila
	@return o id do cen�rio

*/
int CDataManager::getCenarioId(Raca race)
{
	String ^ query;

	unsigned int numCampos = 0;
	unsigned int numRegs   = 0;

	TDadosBD ^ dados = gcnew TDadosBD();

	int tempRace = (int)race;

	query = L"SELECT CNID FROM CENARIO WHERE CNISVILA = 1 AND CNRACA = "+tempRace;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numCampos == 0 || numRegs == 0)
	{
		WarBugsLog::_log->Items->Add(L"N�o foi encontrado cen�rio para a raca "+tempRace);
		return -1;
	}
	
	for(int p = 0; p < (int)numCampos; p++)
	{
		dados->RemoveAt(0);
	}

	return Int32::Parse(dados[0]->ToString());	
}

CBolsa * CDataManager::getItensInimigo(int idInimigo)
{
	CBolsa * bolsa = new CBolsa();


	return bolsa;
}
