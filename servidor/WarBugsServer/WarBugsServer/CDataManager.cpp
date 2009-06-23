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
	Obs.: virá o personagem de qualquer tipo, o tratamento deve ser feito após
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
		String ^texto = L"getPersonagem(int id): Não foi encontrado nenhum Personagem com este id = "+id;
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

				dado[0] = Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				/*CBolsa * tempBolsa;

				tempBolsa = getBolsaPersonagem(dado[0]);

				if(tempBolsa == NULL)
				{
					tempBolsa = new CBolsa();
				}

				personagem->setBolsa(tempBolsa);*/

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
	Obs.: o id dos personagens listados são os ids de cena
	@param idJogador -> id do jogador
	@return -> lista de personagens do jogador
*/
CPeopleList * CDataManager::getPersonagemJogador(int idJogador)
{
	CPeopleList * Lista = new CPeopleList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT PC.PCID, PC.PGID FROM PERSONAGEM P, JOGADOR_PERSONAGEM JP, PERSONAGEM_CENARIO PC "
			+"WHERE P.PGID = JP.PGID AND P.PGID = PC.PGID AND JP.JDID = "+idJogador;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);
	
	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"getPersonagemJogador(int idJogador): Não foi encontrado nenhum Personagem para o jogador = "+idJogador;
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
		
		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PCID")]->ToString());

		//id de cenário se torna o id do objeto
		personagem->setID(dado);

		Lista->addPersonagem(personagem);

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}
	}

	return Lista;
	
}

/*
	Obtem o personagem que o jogador irá usar para jogar
	Obs.: o id dos personagens listados são os ids de cena
	@param idJogador -> id do jogador
	@return -> o personagem que o jogador irá usar
*/
CPersonagem * CDataManager::getPersonagemJogador(int idJogador, int idPersonagem)
{

	CPeopleList * tempListJogador = getPersonagemJogador(idJogador);

	if(tempListJogador->size() == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possivel obter o Personagem do Jogador!");
		return NULL;	
	}

	CPersonagem * tempPersonagem;

	for(int i = 0; i < tempListJogador->size(); i++)
	{
		tempPersonagem = tempListJogador->getElementAt(i);
		
		if(tempPersonagem->getID() == idPersonagem)
		{
			i = tempListJogador->size();
		}
	}

	CBolsa * tempBolsa = getBolsaPersonagem(tempPersonagem->getID());

	tempPersonagem->setBolsa(tempBolsa);

	return tempPersonagem;
}

/*
	Obtem uma lista de personagens do tipo, raça, e se é um persoangem base
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual raça ele pertence TODAS, NENHUMA, ARANHA
	@param personagemBase -> se é um personagem que tem atributos base
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
		String ^texto = L"getPersonagem(int idTipoPersonagem, int idRaca, bool personagemBase): Não foi encontrado o Persoangem de Tipo"+idTipoPersonagem;
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
	Obtem uma lista de personagens do tipo e raça
	Obs.: A lista ja vem com os inimigos com drop se ele não tiverem itens para eles
	@param idTipoPersonagem -> id do tipo de personagem Jogador, NPC, Inimigo, vendedor
	@param idRaca -> a qual raça ele pertence TODAS, NENHUMA, ARANHA
	@param idCenario-> cenario onde ele está
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
		String ^texto = L"getPersonagem(int idTipoPersonagem, int idRaca, int idCenario): Não foi encontrado o Tipo de Personagem "+idTipoPersonagem+" no cenário "+idCenario;
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

		
		//Ponto de respaw dos bichos
		float x = (float)Double::Parse(dados[nomeCampos->IndexOf(L"PCRESPAWX")]->ToString());
		float z = (float)Double::Parse(dados[nomeCampos->IndexOf(L"PCRESPAWZ")]->ToString());

		personagem->setPosition(x,z);

		//id de cenário
		dado = Int32::Parse(dados[nomeCampos->IndexOf(L"PCID")]->ToString());

		personagem->setID(dado);

		CBolsa * tempBolsa = new CBolsa();

		tempBolsa = getBolsaPersonagem(dado);

		personagem->setBolsa(tempBolsa);

		if(tempBolsa->size() <= 0)
		{
			//Caso o personagem seja um inimigo e não possua itens
			if((int)personagem->getType() == SOLDADO || ((int)personagem->getType() == LIDER && (int)personagem->getRace() == FORMIGA))
			{
				tempBolsa = getBolsaDrop(dado, (int)personagem->getType(), (int)personagem->getRace(), 3);
			}
			else // caso ele seja um vendedor
			if((int)personagem->getType() == VENDEDOR && ((int)personagem->getRace() == ARANHA    || 
				                                (int)personagem->getRace() == BESOURO   || 
												(int)personagem->getRace() == ESCORPIAO ||
												(int)personagem->getRace() == LOUVADEUS ||
												(int)personagem->getRace() == VESPA))
			{
				
				tempBolsa = getBolsaInicialVendedor(dado, (int)personagem->getType(), (int)personagem->getRace(), 180);
			}

			personagem->setBolsa(tempBolsa);
		}


		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		tempList->addPersonagem(personagem);
	}

	return tempList;	
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
		String ^texto = L"getItem(int id): Não foi encontrado nenhum Personagem com este id = "+id;
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

		item->setType((TipoItem)tipoItem);
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

	query = L"INSERT INTO ITEM_RELACIONAL(PCID, ITID) VALES ("
			+idPersonagem+","+idBaseItem+")";

	//se o registro não foi inserido
	if(!_dataBase->insertNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"Não foi possível relacionar o item "+idBaseItem+" com o personagem "+idPersonagem);
		return NULL;
	}
	

	int idRelacional = getIdRelacionalUltimoItem();

	CItem * newItem = getItem(idBaseItem);

	if(newItem == NULL)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possível criar um objeto para o relacionamento do item "+idBaseItem
			                         +" com o personagem "+idPersonagem);
		return NULL;
	}

	//coloca o novo id para o item
	newItem->setID(idRelacional);
	newItem->setBaseID((TypeItens)idBaseItem);

	return newItem;
}


/*
	Obtem o ultimo maior id de item relaiconal
*/
int CDataManager::getIdRelacionalUltimoItem()
{
	String ^ query;
	TDadosBD ^ dados      = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	//seleciona o id ultimo item incluido
	query = L"SELECT MAX(IRID) FROM ITEM_RELACIONAL";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	//se o registro não foi selecionado
	if(numRegs == 0 || numCampos == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possível selecionar o maior id do item relacional");
		return -1;
	}

	//remove o nome do campo
	dados->RemoveAt(0);

	return Int32::Parse(dados[0]->ToString());
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
	String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE "
		    +"IR.PGID = P.PGID AND P.PGIDWEAPON = IR.IRID AND "
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"getWeaponEquiped(): Não foi encontrado o equipamento do Personagem "+idPersonagem;
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
	String ^ query;

	query = L"SELECT IR.* FROM ITEM_RELACIONAL IR, PERSONAGEM P WHERE "
		    +"IR.PGID = P.PGID AND P.PGIDARMOR = IR.IRID AND "
			+"P.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"getArmorEqiuped(): Não foi encontrado a Armadura do Personagem "+idPersonagem;
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
	Obtem todos os cenários do jogo
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
		String ^texto = L"Não foi encontrado nenhum Cenário!";
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

		CPeopleList * tempList = new CPeopleList();
		
		//Lista de Inimigos do Cenário
		CPeopleList * listaInimigos = getPersonagem( SOLDADO, ALLRACE, idcenario);
			
			//retira todos os Soldados das Racas dos personagens jogaveis
			// e os coloca em uma lista temporária
			for(int p = 0; p < listaInimigos->size(); p++)
			{
				switch(listaInimigos->getElementAt(p)->getRace())
				{
					case ARANHA:
					case BESOURO:
					case ESCORPIAO:
					case LOUVADEUS:
					case VESPA:
						{
							tempList->addPersonagem(listaInimigos->removePersonagemAt(p));
							break;
						}
					default:
						{
							break;
						}
				}//end switch
			}//end for


		//Lista de Personagens Jogadores do Cenário
		CPeopleList * listaPersonagem = new CPeopleList();

		//Lista de NPCs do Cenário

			//Primeiro os lideres
			//ele vai pegar todos os lideres de todas as racas
			CPeopleList * listaNPC = getPersonagem( LIDER, ALLRACE, idcenario);

			//caso alguém da lista não for um NPC Lider da raça jogavel
			// ele é considerado um inimigo e incluido na lista de inimigos
			for(int p = 0; p < listaNPC->size(); p++)
			{
				//adiciona os soldados da raca dos personagens jogaveis
				// que estiverem na lista temporária
				if(tempList->size() > 0)
				{
					listaNPC->addPersonagem(tempList->removePersonagemAt(0));
				}

				switch(listaNPC->getElementAt(p)->getRace())
				{
					case ARANHA:
					case BESOURO:
					case ESCORPIAO:
					case LOUVADEUS:
					case VESPA:
						{
							break;
						}
					default:
						{
							listaInimigos->addPersonagem(listaNPC->removePersonagemAt(p));
						}
				}//end switch
			}//end for




		//Lista de Vendedores do Cenário
		CPeopleList * listaVendedores = getPersonagem( VENDEDOR, ALLRACE, idcenario);

		//Lista de Bolsas do Cenário
		CBolsaList  * listaBolsas = getListBolsa(idcenario);


		CPortal * portalSul   = getPortal( idcenario, D_SOUTH);
		CPortal * portalNorte = getPortal( idcenario, D_NORTH);
		CPortal * portalOeste = getPortal( idcenario, D_WEST);
		CPortal * portalLeste = getPortal( idcenario, D_EAST);

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
	Retorna o id do cenário em que o jogador estava na última vez
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

	query = L"SELECT PC.CNID FROM PERSONAGEM_CENARIO PC, JOGADOR_PERSONAGEM JP "
			+" WHERE PC.PGID = JP.PGID AND  JP.JDID = "+idJogador+" " 
			+"	AND PC.PCID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"Não foi encontrado nenhum Cenário!";
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
/*
	Obtem os itens que o personagem estava no inventário(os não equipados)
	Obs. é de todos os personagens NPCs, Inimigos, Jogadores
	@param idPersonagem -> o id do personagem
	@return -> inventário do personagem
*/
CBolsa * CDataManager::getBolsaPersonagem(int idPersonagem)
{
	CBolsa * bolsa = new CBolsa();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1, IR.IRVALBONUS2, IR.IRVALBONUS3, IR.IRVALBONUS4,"
            +" IR.IRVALBONUS5, IR.IRVALBONUS6, IR.IRID, IR.IRDURABILIDADE "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, PERSONAGEM P, PERSONAGEM_CENARIO PC "
			+"WHERE "
			+" I.ITID = IR.ITID AND PC.PGID =  P.PGID AND IR.IRID <> P.PGIDARMOR AND IR.IRID <> P.PGIDWEAPON"
			+" AND PC.PCID = IR.PCID "
			+"AND IR.PCID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"Não foi encontrado nenhum Personagem com este id = "+idPersonagem;
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
	Obtem as bolsas com os itens que estiverem no cenário
	@param idCenario -> o cenário que será pego as bolsas
	@return -> lista de bolsas do cenário
*/
CBolsaList * CDataManager::getListBolsa(int idCenario)
{
	CBolsaList * listaBolsa = new CBolsaList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	String ^ query;

	query = L"SELECT I.*, IR.IRVALBONUS1,IR.IRVALBONUS2,IR.IRVALBONUS3,IR.IRVALBONUS4,"
            +"IR.IRVALBONUS5,IR.IRVALBONUS6,IR.IRDURABILIDADE, IR.IRID, B.BSID,B.BSX,B.BSY,B.BSZ "
			+"FROM ITEMBASE I, ITEM_RELACIONAL IR, BOLSA B "
			+"WHERE "
			+"I.ITID = IR.ITID AND IR.BSID =  B.BSID AND B.CNID = "+idCenario+" "
			+"ORDER BY B.BSID";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		String ^texto = L"Não foi encontrado as bolsas do cenário "+idCenario;
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

			//se for o ultimo registro ele não terá dados para retornar dentro de dados
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
		String ^texto = L"Não foi encontrado o Jogador com Login "+temp;
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
	Obtem o portal do cenário passado e da direção passada
	@param idCenario -> id do cenário
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
		String ^texto = L"Não foi encontrado o Portal para "+idCenario;
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
		String ^texto = L"Não foi possível contar os Personagens";
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
		String ^texto = L"Não foi possível contar as Bolsas";
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
		String ^texto = L"Não foi possível contar os Personagens";
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

//ATUALIZAÇÕES
//Personagem

//Inserções
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

	//se não for inserido com sucesso
	if(_dataBase->insertNow(toChar(query)))
	{
		texto = L"Personagem '"+temp+"' Incluído com sucesso";
		WarBugsLog::_log->Items->Add(texto);

		query = L"INSERT INTO JOGADOR_PERSONAGEM "
				+" VALUES ("+p1->getID()+","+idJogador+")";

		//se não for inserido com sucesso
		if(_dataBase->insertNow(toChar(query)))
		{
			texto = L"Personagem '"+temp+"' vinculado ao Jogador com sucesso";
			WarBugsLog::_log->Items->Add(texto);


			int idCenarioVila;
			idCenarioVila = getCenarioVilaId(p1->getRace());

			if(idCenarioVila > -1)
			{

				//inclui o personagem no cenário da vila correspondente a dele
				query = L"INSERT INTO PERSONAGEM_CENARIO(CNID,PGID) VALUES("+idCenarioVila+","+p1->getID()+")";
				if(_dataBase->insertNow(toChar(query)))
				{
					texto = L"Personagem '"+temp+"' vinculado ao cenário da vila com sucesso";
					WarBugsLog::_log->Items->Add(texto);

					result = true;				
				}
			}

		}
		else
		{
			texto = L"Não foi possivel incluir o personagem '"+temp+"'.";
			WarBugsLog::_log->Items->Add(texto);
		}	

	}
	else
	{
		texto = L"Não foi possivel incluir o personagem '"+temp+"'.";
		WarBugsLog::_log->Items->Add(texto);
	}

	return result;
}


/*
	Retorna a quantidade de persoangens que um jogador possui
	@param idJogador-> id do jogador que será consultado
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
		String ^texto = L"Não foi possível contar os Personagens do Jogador "+idJogador;
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
	Exclui um personagem que o jogador não desejar mais
	@param idJogador -> id do jogador qe quer exluir o personagem
	@param idPersonagem -> id do personagem que será exluido
	@param nomePersonagem -> nome Personagem que será excluido
*/
bool CDataManager::deletePersonagemJogador(int idJogador, int idPersonagem, char * nomePersonagem)
{
	bool result = false;

	String ^ query;
	String ^ temp;
	
	temp = gcnew String(nomePersonagem);


	query = L"DELETE FROM PERSONAGEM_CENARIO PC, JOGADOR_PERSONAGEM JP "
			+" USING JOGADOR_PERSONAGEM JP, PERSONAGEM P, PERSONAGEM_CENARIO PC "
			+" WHERE JP.PGID = P.PGID AND JP.JDID = "+idJogador
			+" AND P.PGID = PC.PGID "
			+" AND PC.PCID = "+idPersonagem
			+" AND P.PGNOME = '"+temp+"' ";

	
	String ^texto;

	//se não for EXCLUIDO com sucesso
	if(_dataBase->deleteNow(toChar(query)))
	{
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PCID = "+idPersonagem;
		
		//se não for EXCLUIDO com sucesso
		if(_dataBase->deleteNow(toChar(query)))
		{
			texto = L"Os Itens do personagem '"+temp+"' foram excluido com sucesso";
		}
		else
		{
			texto = L"Não foi possivel excluir os itens do personagem '"+temp+"'.";
		}

		query = L"DELETE FROM PERSONAGEM P "
				+" USING PERSONAGEM P, PERSONAGEM_CENARIO PC "
				+" WHERE P.PGID = PC.PGID "
				+" AND PC.PCID = "+idPersonagem;
		
		//se não for inserido com sucesso
		if(_dataBase->deleteNow(toChar(query)))
		{
			texto = L"Personagem '"+temp+"' excluido com sucesso";
			result = true;
		}
		else
		{
			texto = L"Não foi possivel excluir o personagem '"+temp+"'.";
		}

	}
	else
	{
		texto = L"Não foi possivel exluir o personagem '"+temp+"' do jogador.";
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
	Salvará todas as informações que estão na memória, para o servidor
*/
void CDataManager::backupAll(CCenarioList * cenarioList)
{

	// 1. Salva Persoangens
		// 1.1 Update do personagem e todas as suas variaveis
	    // 1.2 Atualiza a Localização de todos os Personagens
	// 2. Salva Itens Personagens
		// 2.1 Remove todos os itens que ele possuia no BD
		// 2.3 Insere todos os itens que o persoangem possui no jogo
	// 3. Salva Poderes do Personagem
		// 3.1 Atualiza as informações dos poderes que o personagem possui
	// 4. Salva Informações da formula de mercado se o personagem for o vendedor
		// 4.1 Insere as informações que o vendedor possui naquele momento
	// 5. Salva as bolsas
		// 5.1 Remove as que não existirem mais
		// 5.2 Atualiza as que ainda existirem
		// 5.3 Insere as que não estão salvas
	// 6.Salva os itens que os inimigos possuem com eles

	for(int p = 0; p < cenarioList->size(); p++)
	{
		// salva os personagens jogadores
		for(int a = 0; a < cenarioList->getElementAt(p)->playerCount(); a++)
		{
			updatePersonagemJogador(cenarioList->getElementAt(p)->getPlayerAt(a));		
		}

		//salva as bolsas dos cenários
		for(int u = 0; u < cenarioList->getElementAt(p)->bagCount(); u++)
		{
			updateBolsa(cenarioList->getElementAt(p)->getBagAt(u),cenarioList->getElementAt(p)->getID());
		}

		//salva os itens dos monstros
		for(int l = 0; l < cenarioList->getElementAt(p)->monsterCount(); l++)
		{
			updateItensPersonagem(cenarioList->getElementAt(p)->getMonsterAt(l));
		}

		//salva os itens dos NPCS
		for(int h = 0; h < cenarioList->getElementAt(p)->NPCCount(); h++)
		{
			updateItensPersonagem(cenarioList->getElementAt(p)->getNpcAt(h));
		}

		//salva os itens do vendedor
		for(int e = 0; e < cenarioList->getElementAt(p)->salesmanCount(); e++)
		{
			updateItensPersonagem(cenarioList->getElementAt(p)->getSalesmanAt(e));
		}


	}


}

/*
	Atualiza todos os itens que estão relacionados com os inimigos
	param b1->
*/

/*
	Atualiza todas as bolsa que estiverem no cenário
	param b1 -> bolsa que esrá atualizada no BD
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
	Atualiza o personagem no BD, juntamente com seus itens e cenário onde ele está
	param p1-> personagem que será atualizado	
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

		//não esquecer que o item equipado também entra nesta lista
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PCID = "+p1->getID();
				
		//se exluiu os itens que não estavam com ele
		if(_dataBase->deleteNow(toChar(query)))
		{

			for(int p = 0; p < p1->getBolsa()->size(); p++)
			{
				if(p1->getBolsa()->getElementAt(p) != NULL)
				if(p1->getBolsa()->getElementAt(p)->getID() != NULL)
				{
					insereItemRelacional(p1->getBolsa()->getElementAt(p), -1, p1->getID());					
				}
		
			}

			if(p1->getEquip() != NULL)
			if(p1->getEquip()->arma != NULL)
			if(p1->getEquip()->arma->getID() != NULL)
			{
				insereItemRelacional(p1->getEquip()->arma, -1, p1->getID());
			}


			if(p1->getEquip() != NULL)
			if(p1->getEquip()->armadura != NULL)
			if(p1->getEquip()->armadura->getID() != NULL)
			{
				insereItemRelacional(p1->getEquip()->armadura,-1,p1->getID());
			}
			
			//ATUALIZA O CENÁRIO NO JOGADOR SE ENCONTRA
			query = L"UPDATE PERSONAGEM_CENARIO SET CNID = "+p1->getScene()->getID()
					+" WHERE PCID = "+p1->getID();

			_dataBase->updateNow(toChar(query));

		}
	}
			
}


/*
	Salva os itens dos inimigos no BD
	@param Personagem
*/
void CDataManager::updateItensPersonagem(CPersonagem * p1)
{
	//atualiza o personagem
	String ^ query;

	//deleta os itens que este personagem possui no BD
	query = L"DELETE FROM ITEM_RELACIONAL IR "
			+"USING ITEM_RELACIONAL IR, PERSONAGEM_CENARIO PC "
			+"WHERE PC.PCID = IR.PCID "
			+" AND PC.PCID = "+p1->getID();

	// se houve erro na limpeza das tabelas
	if(!_dataBase->deleteNow(toChar(query)))
	{
		WarBugsLog::_log->Items->Add(L"Não foi possível deletar os itens do personagem "+p1->getID());
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
	@param idPersonagem -> qual persoangem será relacionado
	@param iddeCenario -> qual cenario está relacionado
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
		WarBugsLog::_log->Items->Add(L"Não foi possível inserir o relacionamento entre personagem e item");
		return;		
	}

	if(query)
	{
		item->setID(getIdRelacionalUltimoItem());
	}

}

/*
	Insere um item na tabela relacional
	@param item -> objeto item a ser inserido
	@param idBolsa -> qual bosla será relacionado
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
		WarBugsLog::_log->Items->Add(L"Não foi possível inserir o relacionamento entre personagem e item");
		return;		
	}

	if(!query)
	{
		item->setID(getIdRelacionalUltimoItem());
	}

}

/*
	Retorna o id do cenário das Vilas
	@param race-> raca da vila
	@return o id do cenário

*/
int CDataManager::getCenarioVilaId(Raca race)
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
		WarBugsLog::_log->Items->Add(L"Não foi encontrado cenário para a raca "+tempRace);
		return -1;
	}
	
	for(int p = 0; p < (int)numCampos; p++)
	{
		dados->RemoveAt(0);
	}

	return Int32::Parse(dados[0]->ToString());	
}



/*
	Retorna a Bolsa com os itens que o personagem passado pode dropar
	@param idPersonagem -> para que possa criar a relação entre o item e o personagem
	@param TipoPersonagem -> Tipo de personagem que irá recebr a bolsa
	@param Raca -> a raca do personagem que irá receber a bolsa
	@param qtdItensMaxima -> a quantidade máxima de itens que poderá ter na bolsa
*/
CBolsa * CDataManager::getBolsaDrop(int idPersonagem, int idTipoPersonagem, int idRaca, int qtdItensMaxima)
{
	CBolsa * bolsa = new CBolsa();

	TDadosBD ^ itens = gcnew TDadosBD();
	TDadosBD ^ porcentagem = gcnew TDadosBD();

	getDropItem(idTipoPersonagem, idRaca, itens, porcentagem);

	if(itens->Count == 0 || porcentagem->Count == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não há bolsas de drop para este tipo de personagem = "+idTipoPersonagem+" com esta raça = "+idRaca);
		return bolsa;
	}

	for(int i = 0; i < qtdItensMaxima; i++)
	{
		Random ^ r = gcnew Random();

		CItem * tempItem;
		int index = r->Next(porcentagem->Count);
		
		double porc = Double::Parse(porcentagem[index]->ToString());

		int tempPorcentagem = (int)(100000/(1000*porc));
		
		// se o item foi sorteado
		// quando tempPorcentagem for 1 o item será escolhido com certeza
		if(r->Next(tempPorcentagem) == 0)
		{
			int tempIdItem = Int32::Parse(itens[index]->ToString());

			tempItem = getItem(tempIdItem);

			bolsa->addItem(tempItem);

			insereItemRelacional(tempItem,-1,idPersonagem);
		}
	}

	WarBugsLog::_log->Items->Add(L"Bolsa de Drop criada para este tipo de personagem = "+idTipoPersonagem+" com esta raça = "+idRaca);
	

    return bolsa;	
}


CBolsa * CDataManager::getBolsaInicialVendedor(int idPersonagem, int idTipoPersonagem, int idRaca, int qtdItensMaxima)
{
	CBolsa * bolsa = new CBolsa();

	TDadosBD ^ itens = gcnew TDadosBD();
	TDadosBD ^ porcentagem = gcnew TDadosBD();

	getDropItem(idTipoPersonagem, idRaca, itens, porcentagem);

	if(itens->Count == 0 || porcentagem->Count == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não há bolsas Iniciais para este vendedor = "+idTipoPersonagem+" com esta raça = "+idRaca);
		return bolsa;
	}

	for(int i = 0; (i < qtdItensMaxima) && (i < itens->Count); i++)
	{
		CItem * tempItem;

		int tempIdItem = Int32::Parse(itens[i]->ToString());

		tempItem = getItem(tempIdItem);

		bolsa->addItem(tempItem);

		insereItemRelacional(tempItem,-1,idPersonagem);
	
	}
	

    return bolsa;	


}

void  CDataManager::getInformacaoVendedor(int idVendedor, Collections::ArrayList ^ capital, Collections::ArrayList ^ meta, Collections::ArrayList ^ tempo, Collections::ArrayList ^lua, DateTime periodoInicial, DateTime periodoFinal)
{

	TDadosBD ^ dados = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numCampos;
	unsigned int numRegs;
	String ^ query;

	periodoFinal = periodoFinal.AddDays(1.0);

	String ^ dataInicial = L""+periodoInicial.Year.ToString()+"-";

	if((periodoInicial.Month/10) < 1)
	{
		dataInicial += "0";
	}

	dataInicial += periodoInicial.Month.ToString()+"-";
	
	if((periodoInicial.Day/10) < 1)
	{
		dataInicial += "0";
	}

	dataInicial += periodoInicial.Day.ToString();


	String ^ dataFinal= L""+periodoFinal.Year.ToString()+"-";

	if((periodoFinal.Month/10) < 1)
	{
		dataFinal += "0";
	}

	dataFinal += periodoFinal.Month.ToString()+"-";
	
	if((periodoFinal.Day/10) < 1)
	{
		dataFinal += "0";
	}

	dataFinal += periodoFinal.Day.ToString();


	query = L"SELECT VVMETAATUAL, VVLUAATUAL, VVCAPITALTOTAL, VVHORA, DATE_FORMAT(VVDATA, '%d/%m/%Y') DATAVV"
			+" FROM VALORES_VENDEDOR "
			+" WHERE IDVENDEDOR = "+idVendedor+" AND "
			+" VVDATA BETWEEN '"+dataInicial+"' AND '"+dataFinal+"' "
			+" ORDER BY VVDATA, VVHORA ";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numCampos == 0 || numRegs == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não há dados para montar o gráfico");
		return;
	}

	for(int p = 0; p < (int)numCampos; p++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	for(int p = 0; p < (int)numRegs; p++)
	{
	
		capital->Add(dados[nomeCampos->IndexOf(L"VVCAPITALTOTAL")]->ToString());
		meta->Add(dados[nomeCampos->IndexOf(L"VVMETAATUAL")]->ToString());

		int intLua = Int32::Parse(dados[nomeCampos->IndexOf(L"VVLUAATUAL")]->ToString());

		switch(intLua)
		{
			case MOON_ABGRUNDI:
					lua->Add(L"Abgrundi");
					break;
			case MOON_MABILOG:
					lua->Add(L"Mabilog");
					break;
			case MOON_OBLIVION:
					lua->Add(L"Oblivion");
					break;
			case MOON_RESPLANDORA:
					lua->Add(L"Resplandora");
					break;
			case MOON_SAMARA:
					lua->Add(L"Samara");
					break;
			case MOON_TYPHOONA:
					lua->Add(L"Typhoona");
					break;
		}

		int ano = Int32::Parse(dados[nomeCampos->IndexOf(L"DATAVV")]->ToString()->Substring(6,4));
		int mes = Int32::Parse(dados[nomeCampos->IndexOf(L"DATAVV")]->ToString()->Substring(3,2));
		int dia = Int32::Parse(dados[nomeCampos->IndexOf(L"DATAVV")]->ToString()->Substring(0,2));

		String ^tempString = dados[nomeCampos->IndexOf(L"VVHORA")]->ToString()->Substring(6,2);
		int segundo = Int32::Parse(tempString);

		tempString = dados[nomeCampos->IndexOf(L"VVHORA")]->ToString()->Substring(3,2);
		int minuto  = Int32::Parse(tempString);

		tempString = dados[nomeCampos->IndexOf(L"VVHORA")]->ToString()->Substring(0,2);
		int hora    = Int32::Parse(tempString);

		DateTime ^ dateTime = gcnew DateTime(ano, mes, dia, hora, minuto, segundo);

		tempo->Add(dateTime);
	
		for(int a = 0; a < (int)numCampos; a++)
		{
			nomeCampos->Add(dados[0]);
			dados->RemoveAt(0);
		}

	}

}

bool  CDataManager::atualizaCoeficientesMercado(int Kr, int Kd, int Ko, int Kl, int Kt)
{
	bool resposta = false;

	String ^  query;
	query = L"UPDATE MERCADO SET "
			+" MECORTEDEMANDA = "+Kd
			+", MECORTEOFERTA = "+Ko
			+", MECORTEDURABILIDADE = "+Kr
			+", MEDESCONTOLEALDADE = "+Kl
			+", MEDESCONTOTEMPO = "+Kt
			+" WHERE MEID = 1";


	resposta = _dataBase->updateNow(toChar(query));

	if(resposta)
		WarBugsLog::_log->Items->Add(L"Coeficientes atualizados com sucesso!");
	else
		WarBugsLog::_log->Items->Add(L"Não foi possível atualizar os Coeficientes!");

	return resposta;
}

void  CDataManager::getCoeficientesMercado(int &Kr, int &Kd, int &Ko, int &Kl, int &Kt)
{

	TDadosBD ^ dados = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numCampos = 0;
	unsigned int numRegs   = 0;

	String ^  query;
	query = L"SELECT * FROM MERCADO WHERE MEID = 1";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numCampos == 0 || numRegs == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possivel obter os coeficientes de Mercado!");
		return;
	}

	for(int i = 0; i < numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	
	Kr = Int32::Parse(dados[nomeCampos->IndexOf(L"MECORTEDURABILIDADE")]->ToString());
	Kd = Int32::Parse(dados[nomeCampos->IndexOf(L"MECORTEDEMANDA")]->ToString());
	Ko = Int32::Parse(dados[nomeCampos->IndexOf(L"MECORTEOFERTA")]->ToString());
	Kl = Int32::Parse(dados[nomeCampos->IndexOf(L"MEDESCONTOLEALDADE")]->ToString());
	Kt = Int32::Parse(dados[nomeCampos->IndexOf(L"MEDESCONTOTEMPO")]->ToString());

}

/*
	retorna o id do personagem passando seu tipo e sua Raca
	@param idTipoPersonagem -> Tipo do personagem que será consultado
	@param idRaca -> Raca do personagem que será consultado
	@param idItem -> Vetor de itens que serão retornados
	@param chanceDrop -> a chance de drop de cada item do outro vetor
*/
void CDataManager::getDropItem(int idTipoPersonagem, int idRaca, TDadosBD ^ idItem, TDadosBD ^ chanceDrop)
{
	TDadosBD ^ dados = gcnew TDadosBD();
	unsigned int numCampos = 0;
	unsigned int numRegs   = 0;

	String ^  query;
	query = L"SELECT D.ITID, D.DPCHANCE "
			+" FROM DROP_ITEM D, PERSONAGEM P "
			+" WHERE P.PGID = D.PGID AND "
			+" P.PGTIPOPERSONAGEM = "+idTipoPersonagem
			+" AND P.PGRACA = "+idRaca;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numCampos == 0 || numRegs == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possivel obter os coeficientes de Mercado!");
		return;
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		dados->RemoveAt(0);
	}

	for(int i = 0; i < (int)numRegs; i++)
	{
		idItem->Add(dados[0]);
		chanceDrop->Add(dados[1]);

		dados->RemoveAt(0);
		dados->RemoveAt(0);
	}
}

/*
	
*/
void CDataManager::atualizaMercado()
{
	/*
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numCampos = 0;
	unsigned int numRegs   = 0;

	String ^  query;
	query = L"SELECT D.ITID, D.DPCHANCE "
			+" FROM DROP_ITEM D, PERSONAGEM P "
			+" WHERE P.PGID = D.PGID AND "
			+" P.PGTIPOPERSONAGEM = "+idTipoPersonagem
			+" AND P.PGRACA = "+idRaca;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numCampos == 0 || numRegs == 0)
	{
		WarBugsLog::_log->Items->Add(L"Não foi possivel obter os coeficientes de Mercado!");
		return;
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nome
		dados->RemoveAt(0);
	}	

*/
}