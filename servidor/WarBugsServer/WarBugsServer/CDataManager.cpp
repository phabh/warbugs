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
#include <CVendedor.h>
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
				
				//FICA PRA DEPOIS
				((CPersonagemJogador *)personagem)->setPlayer(-1);

				float posX = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString()));
				float posZ = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString()));

				((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

				float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

				((CPersonagemJogador *)personagem)->setMoveSpeed(tempVel);

				float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
				((CPersonagemJogador *)personagem)->setDirection(tempDir);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
				((CPersonagemJogador *)personagem)->setRespawnTime(dado[0]);

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

				dado[11] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
				dado[12] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

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

				((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[11]);
				((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[12]);

				break;
			}
		case LIDER:
			{
				int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				switch((Raca)race)
				{
					case FORMIGA:
						{
							//monta o TanDan
							personagem = new CInimigo();

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

							((CInimigo *)personagem)->setID(dado[0]);

							char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

							((CPersonagemJogador *)personagem)->setName(nome);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
							dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
							dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
							dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
							dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

							CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

							((CInimigo *)personagem)->setBaseStats(tempHabilidades);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

							((CInimigo *)personagem)->setRace((Raca)dado[0]);

							CBolsa tempBolsa;

/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

							((CInimigo *)personagem)->setBolsa(&tempBolsa);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

							((CInimigo *)personagem)->setMoney(dado[0]);

							float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
							float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

							((CInimigo *)personagem)->setPosition(posX, posZ);

							float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

							((CInimigo *)personagem)->setMoveSpeed(tempVel);

							float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
							((CInimigo *)personagem)->setDirection(tempDir);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
							((CInimigo *)personagem)->setRespawnTime(dado[0]);

							//FICA PRA DEPOIS
							((CInimigo *)personagem)->setTarget(NULL);

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

							((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
							((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
							((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
							((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
							((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
							((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
							((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
							((CInimigo *)personagem)->getStats()->setPM(dado[7]);
							((CInimigo *)personagem)->getStats()->setPV(dado[8]);
							((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
							((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

							break;
						}
					case BESOURO:
					case ARANHA:
					case LOUVADEUS:
					case ESCORPIAO:
					case VESPA:
						{
							personagem = new CNPC();

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

							((CNPC *)personagem)->setID(dado[0]);

							char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
							dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
							dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
							dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
							dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

							CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

							((CNPC *)personagem)->setBaseStats(tempHabilidades);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

							((CNPC *)personagem)->setRace((Raca)dado[0]);

							CBolsa tempBolsa;

/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

							((CNPC *)personagem)->setBolsa(&tempBolsa);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

							((CNPC *)personagem)->setMoney(dado[0]);

							float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
							float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

							((CNPC *)personagem)->setPosition(posX, posZ);

							float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

							((CNPC *)personagem)->setMoveSpeed(tempVel);

							float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
							((CNPC *)personagem)->setDirection(tempDir);

							dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
							((CNPC *)personagem)->setRespawnTime(dado[0]);

							//FICA PRA DEPOIS
							((CNPC *)personagem)->setTarget(NULL);

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

							((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
							((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
							((CNPC *)personagem)->getStats()->setDefense(dado[2]);
							((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
							((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
							((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
							((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
							((CNPC *)personagem)->getStats()->setPM(dado[7]);
							((CNPC *)personagem)->getStats()->setPV(dado[8]);
							((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
							((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);

							break;
						}
				
				}
				break;
			}
		case MAE: //NPC
		case FILHOTE: //NPC
			{
				personagem = new CNPC();

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CNPC *)personagem)->setID(dado[0]);

				char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

				((CPersonagemJogador *)personagem)->setName(nome);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
				dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
				dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

				CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

				((CNPC *)personagem)->setBaseStats(tempHabilidades);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				((CNPC *)personagem)->setRace((Raca)dado[0]);

				CBolsa tempBolsa;

/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

				((CNPC *)personagem)->setBolsa(&tempBolsa);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

				((CNPC *)personagem)->setMoney(dado[0]);

				float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CNPC *)personagem)->setPosition(posX, posZ);

				float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

				((CNPC *)personagem)->setMoveSpeed(tempVel);

				float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
				((CNPC *)personagem)->setDirection(tempDir);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
				((CNPC *)personagem)->setRespawnTime(dado[0]);

				//FICA PRA DEPOIS
				((CNPC *)personagem)->setTarget(NULL);

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

				((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
				((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
				((CNPC *)personagem)->getStats()->setDefense(dado[2]);
				((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
				((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
				((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
				((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
				((CNPC *)personagem)->getStats()->setPM(dado[7]);
				((CNPC *)personagem)->getStats()->setPV(dado[8]);
				((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
				((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);


				break;
			}
		case VENDEDOR: //Vendedor
			{
				personagem = new CVendedor();

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

				((CVendedor *)personagem)->setID(dado[0]);

				char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

				((CPersonagemJogador *)personagem)->setName(nome);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
				dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
				dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
				dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
				dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

				CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

				((CVendedor *)personagem)->setBaseStats(tempHabilidades);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				((CVendedor *)personagem)->setRace((Raca)dado[0]);

				CBolsa tempBolsa;

/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

				((CVendedor *)personagem)->setBolsa(&tempBolsa);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

				((CVendedor *)personagem)->setMoney(dado[0]);

				float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
				float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

				((CVendedor *)personagem)->setPosition(posX, posZ);

				float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

				((CVendedor *)personagem)->setMoveSpeed(tempVel);

				float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
				((CVendedor *)personagem)->setDirection(tempDir);

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
				((CVendedor *)personagem)->setRespawnTime(dado[0]);

				//FICA PRA DEPOIS
				((CVendedor *)personagem)->setTarget(NULL);

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

				((CVendedor *)personagem)->getStats()->setAttackRate(dado[0]);
				((CVendedor *)personagem)->getStats()->setChargeTime(dado[1]);
				((CVendedor *)personagem)->getStats()->setDefense(dado[2]);
				((CVendedor *)personagem)->getStats()->setMaxPM(dado[3]);
				((CVendedor *)personagem)->getStats()->setMaxPV(dado[4]);
				((CVendedor *)personagem)->getStats()->setMeleeAttack(dado[5]);
				((CVendedor *)personagem)->getStats()->setMeleeDamage(dado[6]);
				((CVendedor *)personagem)->getStats()->setPM(dado[7]);
				((CVendedor *)personagem)->getStats()->setPV(dado[8]);
				((CVendedor *)personagem)->getStats()->setRangedAttack(dado[9]);
				((CVendedor *)personagem)->getStats()->setRangedDamage(dado[10]);
				break;
			}
		case SOLDADO: //Inimigo
			{
				personagem = NULL;
				int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

				if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
				{
					//se for inimigo
					personagem = new CInimigo();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CInimigo *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CInimigo *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CInimigo *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

					int secret;

					for(int p = 0; p < 3; p++)
					{
						srand((unsigned int)time(NULL));

						secret = rand()%3;

						switch(((CInimigo *)personagem)->getRace())
						{
							case CUPIM:       //USO
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(28); //Polpa de Cupim

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case FORMIGA:     //USO
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(27); //Polpa de Formiga

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case BARBEIRO:    //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(34); //Tesoura de Barbeiro

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case BARATA:	  //USO
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(29); //Polpa de Barata

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case TATUBOLINHA: //USO
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(30); //Polpa de Tatu

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case LIBELULA:    //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(31); //Asas de Libélula

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case PERCEVEJO:   //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(32); //Perfume de Percevejo

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case ABELHA:      //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(33); //Mel de Abelha

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case LAGARTIXA:	  //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(36); //Ovo de Lagartixa

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case CALANGO:     //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(35); //Rabo de Calango

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case SAPO:		  //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(37); //Língua de Sapo

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
							case JOANINHA:	  //QUEST
								{
									break;
								}
							case CAMALEAO:	  //QUEST
								{
									if(secret == 0)
									{
										CItem * itemTemp;

										itemTemp = getItem(38); //Língua de Camaleão

										tempBolsa.addItem(itemTemp);
									}
									break;
								}
						}
						
					}

					((CInimigo *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CInimigo *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CInimigo *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CInimigo *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CInimigo *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CInimigo *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CInimigo *)personagem)->setTarget(NULL);

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

					((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
					((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
					((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
					((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
					((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
					((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CInimigo *)personagem)->getStats()->setPM(dado[7]);
					((CInimigo *)personagem)->getStats()->setPV(dado[8]);
					((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

				}
				else
				{
					//se for amigo
					personagem = new CNPC();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CNPC *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CNPC *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CNPC *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CNPC *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CNPC *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CNPC *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CNPC *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CNPC *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CNPC *)personagem)->setTarget(NULL);

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

					((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
					((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
					((CNPC *)personagem)->getStats()->setDefense(dado[2]);
					((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
					((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
					((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CNPC *)personagem)->getStats()->setPM(dado[7]);
					((CNPC *)personagem)->getStats()->setPV(dado[8]);
					((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);
				}

				break;
			}
	}


	if(personagem != NULL)
	{
		personagem->setType((TypeClassChars) tipoPersonagem);
		personagem->set2DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString()));
		personagem->set3DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString()));
		personagem->set2DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString()));
	
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

		float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

		((CPersonagemJogador *)personagem)->setMoveSpeed(tempVel);

		float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
		((CPersonagemJogador *)personagem)->setDirection(tempDir);

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
		((CPersonagemJogador *)personagem)->setRespawnTime(dado[0]);

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

		dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString());
		dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString());
		dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString());
		dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
		dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

		((CPersonagemJogador *)personagem)->setModel(dado[0]);
		((CPersonagemJogador *)personagem)->set3DTexture(dado[1]);
		((CPersonagemJogador *)personagem)->set2DTexture(dado[2]);
		((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[3]);
		((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[4]);

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
					
					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CPersonagemJogador *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CPersonagemJogador *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CPersonagemJogador *)personagem)->setRespawnTime(dado[0]);

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

					dado[11] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
					dado[12] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

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

					((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[11]);
					((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[12]);

					break;
				}
			case LIDER:
				{
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					switch((Raca)race)
					{
						case FORMIGA:
							{
								//monta o TanDan
								personagem = new CInimigo();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CInimigo *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								((CPersonagemJogador *)personagem)->setName(nome);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CInimigo *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CInimigo *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CInimigo *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CInimigo *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CInimigo *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CInimigo *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CInimigo *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CInimigo *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CInimigo *)personagem)->setTarget(NULL);

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

								((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
								((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
								((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
								((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
								((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
								((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CInimigo *)personagem)->getStats()->setPM(dado[7]);
								((CInimigo *)personagem)->getStats()->setPV(dado[8]);
								((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
						case BESOURO:
						case ARANHA:
						case LOUVADEUS:
						case ESCORPIAO:
						case VESPA:
							{
								personagem = new CNPC();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CNPC *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CNPC *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CNPC *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CNPC *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CNPC *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CNPC *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CNPC *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CNPC *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CNPC *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CNPC *)personagem)->setTarget(NULL);

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

								((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
								((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
								((CNPC *)personagem)->getStats()->setDefense(dado[2]);
								((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
								((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
								((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CNPC *)personagem)->getStats()->setPM(dado[7]);
								((CNPC *)personagem)->getStats()->setPV(dado[8]);
								((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
					
					}
					break;
				}
			case MAE: //NPC
			case FILHOTE: //NPC
				{
					personagem = new CNPC();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CNPC *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CNPC *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CNPC *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CNPC *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CNPC *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CNPC *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CNPC *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CNPC *)personagem)->setTarget(NULL);

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

					((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
					((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
					((CNPC *)personagem)->getStats()->setDefense(dado[2]);
					((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
					((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
					((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CNPC *)personagem)->getStats()->setPM(dado[7]);
					((CNPC *)personagem)->getStats()->setPV(dado[8]);
					((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);


					break;
				}
			case VENDEDOR: //Vendedor
				{
					personagem = new CVendedor();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CVendedor *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CVendedor *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CVendedor *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CVendedor *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CVendedor *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CVendedor *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CVendedor *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CVendedor *)personagem)->setTarget(NULL);

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

					((CVendedor *)personagem)->getStats()->setAttackRate(dado[0]);
					((CVendedor *)personagem)->getStats()->setChargeTime(dado[1]);
					((CVendedor *)personagem)->getStats()->setDefense(dado[2]);
					((CVendedor *)personagem)->getStats()->setMaxPM(dado[3]);
					((CVendedor *)personagem)->getStats()->setMaxPV(dado[4]);
					((CVendedor *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CVendedor *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CVendedor *)personagem)->getStats()->setPM(dado[7]);
					((CVendedor *)personagem)->getStats()->setPV(dado[8]);
					((CVendedor *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CVendedor *)personagem)->getStats()->setRangedDamage(dado[10]);
					break;
				}
			case SOLDADO: //Inimigo
				{
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
						personagem = new CInimigo();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CInimigo *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CPersonagemJogador *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CInimigo *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CInimigo *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

						int secret;

						for(int p = 0; p < 3; p++)
						{
							srand((unsigned int)time(NULL));

							secret = rand()%3;

							switch(((CInimigo *)personagem)->getRace())
							{
								case CUPIM:       //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(28); //Polpa de Cupim

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case FORMIGA:     //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(27); //Polpa de Formiga

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARBEIRO:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(34); //Tesoura de Barbeiro

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARATA:	  //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(29); //Polpa de Barata

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case TATUBOLINHA: //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(30); //Polpa de Tatu

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LIBELULA:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(31); //Asas de Libélula

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case PERCEVEJO:   //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(32); //Perfume de Percevejo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case ABELHA:      //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(33); //Mel de Abelha

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LAGARTIXA:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(36); //Ovo de Lagartixa

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case CALANGO:     //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(35); //Rabo de Calango

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case SAPO:		  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(37); //Língua de Sapo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case JOANINHA:	  //QUEST
									{
										break;
									}
								case CAMALEAO:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(38); //Língua de Camaleão

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
							}
							
						}

						((CInimigo *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CInimigo *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CInimigo *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CInimigo *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CInimigo *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CInimigo *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CInimigo *)personagem)->setTarget(NULL);

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

						((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
						((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
						((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
						((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
						((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
						((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CInimigo *)personagem)->getStats()->setPM(dado[7]);
						((CInimigo *)personagem)->getStats()->setPV(dado[8]);
						((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

					}
					else
					{
						//se for amigo
						personagem = new CNPC();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CNPC *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CNPC *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CNPC *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CNPC *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

		/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

						((CNPC *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CNPC *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CNPC *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CNPC *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CNPC *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CNPC *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CNPC *)personagem)->setTarget(NULL);

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

						((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
						((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
						((CNPC *)personagem)->getStats()->setDefense(dado[2]);
						((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
						((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
						((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CNPC *)personagem)->getStats()->setPM(dado[7]);
						((CNPC *)personagem)->getStats()->setPV(dado[8]);
						((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);
					}

					break;
				}
		}


		if(personagem != NULL)
		{
			personagem->setType((TypeClassChars) tipoPersonagem);
			personagem->set2DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString()));
			personagem->set3DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString()));
			personagem->setModel(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString()));
		
		}

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
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
CPeopleList * CDataManager::getPersonagem(int idTipoPersonagem, int idRaca, int idCenario)
{

	CPeopleList * tempList = new CPeopleList();

	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();
	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;
	System::String ^ query;
	System::String ^ complemento = L" ";
	if(idRaca != ALLRACE && idRaca != NONERACE)
	{
		complemento = L"P.PGRACA = "+idRaca+" AND ";
	}

	query = L"SELECT P.* FROM PERSONAGEM P, PERSONAGEM_CENARIO PC "
		    +"WHERE P.PGID = PC.PGID AND   "
			+"PC.CNID =  "+idCenario+" AND "
			+complemento
			+"P.PGTIPOPERSONAGEM = "+idTipoPersonagem;
		
	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado o Tipo de Personagem "+idTipoPersonagem+" no cenário "+idCenario;
		WarBugsLog::_log->Items->Add(texto);		
		return tempList;	
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
					
					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CPersonagemJogador *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CPersonagemJogador *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CPersonagemJogador *)personagem)->setRespawnTime(dado[0]);

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

					dado[11] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
					dado[12] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

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

					((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[11]);
					((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[12]);

					break;
				}
			case LIDER:
				{
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					switch((Raca)race)
					{
						case FORMIGA:
							{
								//monta o TanDan
								personagem = new CInimigo();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CInimigo *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								((CPersonagemJogador *)personagem)->setName(nome);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CInimigo *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CInimigo *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CInimigo *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CInimigo *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CInimigo *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CInimigo *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CInimigo *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CInimigo *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CInimigo *)personagem)->setTarget(NULL);

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

								((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
								((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
								((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
								((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
								((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
								((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CInimigo *)personagem)->getStats()->setPM(dado[7]);
								((CInimigo *)personagem)->getStats()->setPV(dado[8]);
								((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
						case BESOURO:
						case ARANHA:
						case LOUVADEUS:
						case ESCORPIAO:
						case VESPA:
							{
								personagem = new CNPC();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CNPC *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CNPC *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CNPC *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CNPC *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CNPC *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CNPC *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CNPC *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CNPC *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CNPC *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CNPC *)personagem)->setTarget(NULL);

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

								((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
								((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
								((CNPC *)personagem)->getStats()->setDefense(dado[2]);
								((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
								((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
								((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CNPC *)personagem)->getStats()->setPM(dado[7]);
								((CNPC *)personagem)->getStats()->setPV(dado[8]);
								((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
					
					}
					break;
				}
			case MAE: //NPC
			case FILHOTE: //NPC
				{
					personagem = new CNPC();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CNPC *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CNPC *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CNPC *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CNPC *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CNPC *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CNPC *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CNPC *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CNPC *)personagem)->setTarget(NULL);

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

					((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
					((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
					((CNPC *)personagem)->getStats()->setDefense(dado[2]);
					((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
					((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
					((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CNPC *)personagem)->getStats()->setPM(dado[7]);
					((CNPC *)personagem)->getStats()->setPV(dado[8]);
					((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);


					break;
				}
			case VENDEDOR: //Vendedor
				{
					personagem = new CVendedor();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CVendedor *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CVendedor *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CVendedor *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CVendedor *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CVendedor *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CVendedor *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CVendedor *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CVendedor *)personagem)->setTarget(NULL);

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

					((CVendedor *)personagem)->getStats()->setAttackRate(dado[0]);
					((CVendedor *)personagem)->getStats()->setChargeTime(dado[1]);
					((CVendedor *)personagem)->getStats()->setDefense(dado[2]);
					((CVendedor *)personagem)->getStats()->setMaxPM(dado[3]);
					((CVendedor *)personagem)->getStats()->setMaxPV(dado[4]);
					((CVendedor *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CVendedor *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CVendedor *)personagem)->getStats()->setPM(dado[7]);
					((CVendedor *)personagem)->getStats()->setPV(dado[8]);
					((CVendedor *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CVendedor *)personagem)->getStats()->setRangedDamage(dado[10]);
					break;
				}
			case SOLDADO: //Inimigo
				{
					personagem = NULL;

					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
						personagem = new CInimigo();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CInimigo *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CPersonagemJogador *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CInimigo *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CInimigo *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

						int secret;

						for(int p = 0; p < 3; p++)
						{
							srand((unsigned int)time(NULL));

							secret = rand()%3;

							switch(((CInimigo *)personagem)->getRace())
							{
								case CUPIM:       //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(28); //Polpa de Cupim

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case FORMIGA:     //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(27); //Polpa de Formiga

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARBEIRO:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(34); //Tesoura de Barbeiro

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARATA:	  //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(29); //Polpa de Barata

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case TATUBOLINHA: //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(30); //Polpa de Tatu

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LIBELULA:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(31); //Asas de Libélula

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case PERCEVEJO:   //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(32); //Perfume de Percevejo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case ABELHA:      //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(33); //Mel de Abelha

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LAGARTIXA:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(36); //Ovo de Lagartixa

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case CALANGO:     //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(35); //Rabo de Calango

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case SAPO:		  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(37); //Língua de Sapo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case JOANINHA:	  //QUEST
									{
										break;
									}
								case CAMALEAO:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(38); //Língua de Camaleão

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
							}
							
						}

						((CInimigo *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CInimigo *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CInimigo *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CInimigo *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CInimigo *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CInimigo *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CInimigo *)personagem)->setTarget(NULL);

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

						((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
						((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
						((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
						((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
						((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
						((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CInimigo *)personagem)->getStats()->setPM(dado[7]);
						((CInimigo *)personagem)->getStats()->setPV(dado[8]);
						((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

					}
					else
					{
						//se for amigo
						personagem = new CNPC();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CNPC *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CNPC *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CNPC *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CNPC *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

		/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

						((CNPC *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CNPC *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CNPC *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CNPC *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CNPC *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CNPC *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CNPC *)personagem)->setTarget(NULL);

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

						((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
						((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
						((CNPC *)personagem)->getStats()->setDefense(dado[2]);
						((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
						((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
						((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CNPC *)personagem)->getStats()->setPM(dado[7]);
						((CNPC *)personagem)->getStats()->setPV(dado[8]);
						((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);
					}

					break;
				}
		}


		if(personagem != NULL)
		{
			personagem->setType((TypeClassChars) tipoPersonagem);
			personagem->set2DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString()));
			personagem->set3DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString()));
			personagem->setModel(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString()));
		
		}

		for(int i = 0; i < (int)numCampos; i++)
		{
			dados->RemoveAt(0);
		}

		tempList->addPersonagem(personagem);
	}

	return tempList;	
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
					
					//FICA PRA DEPOIS
					((CPersonagemJogador *)personagem)->setPlayer(-1);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CPersonagemJogador *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CPersonagemJogador *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CPersonagemJogador *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CPersonagemJogador *)personagem)->setRespawnTime(dado[0]);

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

					dado[11] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPRIMARIAS")]->ToString());
					dado[12] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGBONUSPOINTSPODER")]->ToString());

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

					((CPersonagemJogador *)personagem)->setPointsToDistribute(dado[11]);
					((CPersonagemJogador *)personagem)->setSkillPointsToDistribute(dado[12]);

					break;
				}
			case LIDER:
				{
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					switch((Raca)race)
					{
						case FORMIGA:
							{
								//monta o TanDan
								personagem = new CInimigo();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CInimigo *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								((CPersonagemJogador *)personagem)->setName(nome);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CInimigo *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CInimigo *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CInimigo *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CInimigo *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CInimigo *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CInimigo *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CInimigo *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CInimigo *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CInimigo *)personagem)->setTarget(NULL);

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

								((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
								((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
								((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
								((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
								((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
								((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CInimigo *)personagem)->getStats()->setPM(dado[7]);
								((CInimigo *)personagem)->getStats()->setPV(dado[8]);
								((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
						case BESOURO:
						case ARANHA:
						case LOUVADEUS:
						case ESCORPIAO:
						case VESPA:
							{
								personagem = new CNPC();

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

								((CNPC *)personagem)->setID(dado[0]);

								char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
								dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
								dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
								dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
								dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

								CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

								((CNPC *)personagem)->setBaseStats(tempHabilidades);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

								((CNPC *)personagem)->setRace((Raca)dado[0]);

								CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

								((CNPC *)personagem)->setBolsa(&tempBolsa);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

								((CNPC *)personagem)->setMoney(dado[0]);

								float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
								float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

								((CNPC *)personagem)->setPosition(posX, posZ);

								float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

								((CNPC *)personagem)->setMoveSpeed(tempVel);

								float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
								((CNPC *)personagem)->setDirection(tempDir);

								dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
								((CNPC *)personagem)->setRespawnTime(dado[0]);

								//FICA PRA DEPOIS
								((CNPC *)personagem)->setTarget(NULL);

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

								((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
								((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
								((CNPC *)personagem)->getStats()->setDefense(dado[2]);
								((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
								((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
								((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
								((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
								((CNPC *)personagem)->getStats()->setPM(dado[7]);
								((CNPC *)personagem)->getStats()->setPV(dado[8]);
								((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
								((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);

								break;
							}
					
					}
					break;
				}
			case MAE: //NPC
			case FILHOTE: //NPC
				{
					personagem = new CNPC();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CNPC *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CNPC *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CNPC *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CNPC *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CNPC *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CNPC *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CNPC *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CNPC *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CNPC *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CNPC *)personagem)->setTarget(NULL);

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

					((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
					((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
					((CNPC *)personagem)->getStats()->setDefense(dado[2]);
					((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
					((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
					((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CNPC *)personagem)->getStats()->setPM(dado[7]);
					((CNPC *)personagem)->getStats()->setPV(dado[8]);
					((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);


					break;
				}
			case VENDEDOR: //Vendedor
				{
					personagem = new CVendedor();

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

					((CVendedor *)personagem)->setID(dado[0]);

					char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

					((CPersonagemJogador *)personagem)->setName(nome);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
					dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
					dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
					dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
					dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

					CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

					((CVendedor *)personagem)->setBaseStats(tempHabilidades);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					((CVendedor *)personagem)->setRace((Raca)dado[0]);

					CBolsa tempBolsa;

	/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

					((CVendedor *)personagem)->setBolsa(&tempBolsa);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

					((CVendedor *)personagem)->setMoney(dado[0]);

					float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
					float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

					((CVendedor *)personagem)->setPosition(posX, posZ);

					float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

					((CVendedor *)personagem)->setMoveSpeed(tempVel);

					float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
					((CVendedor *)personagem)->setDirection(tempDir);

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
					((CVendedor *)personagem)->setRespawnTime(dado[0]);

					//FICA PRA DEPOIS
					((CVendedor *)personagem)->setTarget(NULL);

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

					((CVendedor *)personagem)->getStats()->setAttackRate(dado[0]);
					((CVendedor *)personagem)->getStats()->setChargeTime(dado[1]);
					((CVendedor *)personagem)->getStats()->setDefense(dado[2]);
					((CVendedor *)personagem)->getStats()->setMaxPM(dado[3]);
					((CVendedor *)personagem)->getStats()->setMaxPV(dado[4]);
					((CVendedor *)personagem)->getStats()->setMeleeAttack(dado[5]);
					((CVendedor *)personagem)->getStats()->setMeleeDamage(dado[6]);
					((CVendedor *)personagem)->getStats()->setPM(dado[7]);
					((CVendedor *)personagem)->getStats()->setPV(dado[8]);
					((CVendedor *)personagem)->getStats()->setRangedAttack(dado[9]);
					((CVendedor *)personagem)->getStats()->setRangedDamage(dado[10]);
					break;
				}
			case SOLDADO: //Inimigo
				{
					personagem = NULL;
					int race = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

					if(race != BESOURO && race != ARANHA && race != ESCORPIAO && race != LOUVADEUS && race != VESPA)
					{
						//se for inimigo
						personagem = new CInimigo();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CInimigo *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CPersonagemJogador *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CInimigo *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CInimigo *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

						int secret;

						for(int p = 0; p < 3; p++)
						{
							srand((unsigned int)time(NULL));

							secret = rand()%3;

							switch(((CInimigo *)personagem)->getRace())
							{
								case CUPIM:       //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(28); //Polpa de Cupim

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case FORMIGA:     //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(27); //Polpa de Formiga

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARBEIRO:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(34); //Tesoura de Barbeiro

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case BARATA:	  //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(29); //Polpa de Barata

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case TATUBOLINHA: //USO
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(30); //Polpa de Tatu

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LIBELULA:    //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(31); //Asas de Libélula

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case PERCEVEJO:   //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(32); //Perfume de Percevejo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case ABELHA:      //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(33); //Mel de Abelha

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case LAGARTIXA:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(36); //Ovo de Lagartixa

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case CALANGO:     //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(35); //Rabo de Calango

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case SAPO:		  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(37); //Língua de Sapo

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
								case JOANINHA:	  //QUEST
									{
										break;
									}
								case CAMALEAO:	  //QUEST
									{
										if(secret == 0)
										{
											CItem * itemTemp;

											itemTemp = getItem(38); //Língua de Camaleão

											tempBolsa.addItem(itemTemp);
										}
										break;
									}
							}
							
						}

						((CInimigo *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CInimigo *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CInimigo *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CInimigo *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CInimigo *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CInimigo *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CInimigo *)personagem)->setTarget(NULL);

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

						((CInimigo *)personagem)->getStats()->setAttackRate(dado[0]);
						((CInimigo *)personagem)->getStats()->setChargeTime(dado[1]);
						((CInimigo *)personagem)->getStats()->setDefense(dado[2]);
						((CInimigo *)personagem)->getStats()->setMaxPM(dado[3]);
						((CInimigo *)personagem)->getStats()->setMaxPV(dado[4]);
						((CInimigo *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CInimigo *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CInimigo *)personagem)->getStats()->setPM(dado[7]);
						((CInimigo *)personagem)->getStats()->setPV(dado[8]);
						((CInimigo *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CInimigo *)personagem)->getStats()->setRangedDamage(dado[10]);

					}
					else
					{
						//se for amigo
						personagem = new CNPC();

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGID")]->ToString());

						((CNPC *)personagem)->setID(dado[0]);

						char * nome = toChar(dados[nomeCampos->IndexOf(L"PGNOME")]->ToString());

						((CNPC *)personagem)->setName(nome);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGAGILIDADE")]->ToString());
						dado[1] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDESTREZA")]->ToString());
						dado[2] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGFORCA")]->ToString());
						dado[3] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGINSTINTO")]->ToString());
						dado[4] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRESISTENCIA")]->ToString());

						CHabilidades * tempHabilidades = new CHabilidades(dado[2],dado[0],dado[1],dado[3],dado[4]);

						((CNPC *)personagem)->setBaseStats(tempHabilidades);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGRACA")]->ToString());

						((CNPC *)personagem)->setRace((Raca)dado[0]);

						CBolsa tempBolsa;

		/////////////////////////////COLOCAR UM ITEM PARA O TANDAN

						((CNPC *)personagem)->setBolsa(&tempBolsa);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGDINHEIRO")]->ToString());

						((CNPC *)personagem)->setMoney(dado[0]);

						float posX = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGX")]->ToString());
						float posZ = (float)System::Double::Parse(dados[nomeCampos->IndexOf(L"PGZ")]->ToString());

						((CNPC *)personagem)->setPosition(posX, posZ);

						float tempVel = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGVELOCIDADE")]->ToString()));

						((CNPC *)personagem)->setMoveSpeed(tempVel);

						float tempDir = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PGDIRECAO")]->ToString()));
						((CNPC *)personagem)->setDirection(tempDir);

						dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGTEMPORESPAW")]->ToString());
						((CNPC *)personagem)->setRespawnTime(dado[0]);

						//FICA PRA DEPOIS
						((CNPC *)personagem)->setTarget(NULL);

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

						((CNPC *)personagem)->getStats()->setAttackRate(dado[0]);
						((CNPC *)personagem)->getStats()->setChargeTime(dado[1]);
						((CNPC *)personagem)->getStats()->setDefense(dado[2]);
						((CNPC *)personagem)->getStats()->setMaxPM(dado[3]);
						((CNPC *)personagem)->getStats()->setMaxPV(dado[4]);
						((CNPC *)personagem)->getStats()->setMeleeAttack(dado[5]);
						((CNPC *)personagem)->getStats()->setMeleeDamage(dado[6]);
						((CNPC *)personagem)->getStats()->setPM(dado[7]);
						((CNPC *)personagem)->getStats()->setPV(dado[8]);
						((CNPC *)personagem)->getStats()->setRangedAttack(dado[9]);
						((CNPC *)personagem)->getStats()->setRangedDamage(dado[10]);
					}

					break;
				}
		}


		if(personagem != NULL)
		{
			personagem->setType((TypeClassChars) tipoPersonagem);
			personagem->set2DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDHUD")]->ToString()));
			personagem->set3DTexture(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDTEXTURA")]->ToString()));
			personagem->setModel(System::Int32::Parse(dados[nomeCampos->IndexOf(L"PGIDMODELO")]->ToString()));
		
		}

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

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CConsumableItem *)item)->setID(dado[0]);

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

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CWeapon *)item)->setID(dado[0]);

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

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CArmor *)item)->setID(dado[0]);

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

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CQItem *)item)->setID(dado[0]);

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


				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CScroll *)item)->setID(dado[0]);

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

				dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
				((CLoyaltyScroll *)item)->setID(dado[0]);

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

	for(int i = 0; i < (int)numRegs; i++)
	{

		int idcenario = System::Int32::Parse(dados[nomeCampos->IndexOf(L"CNID")]->ToString());
		
		CPeopleList * listaInimigos = getPersonagem( SOLDADO, ALLRACE, idcenario);
		CPeopleList * listaPersonagem = new CPeopleList();
		CPeopleList * listaNPC = new CPeopleList();
		CPeopleList * listaVendedores = new CPeopleList();
		CBolsaList  * listaBolsas = getListBolsa(idcenario);
		CPortal * portalSul = getPortal(idcenario,SUL);
		CPortal * portalNorte = getPortal(idcenario,NORTE);
		CPortal * portalOeste = getPortal(idcenario,OESTE);
		CPortal * portalLeste = getPortal(idcenario,LESTE);

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
	System::String ^ query;

	query = L"SELECT C.CNID FROM CENARIO C, PERSONAGEM_CENARIO PC, JOGADOR_PERSONAGEM JP "
		    +"WHERE PC.PGID = JP.PGID AND C.CNID  = PC.CNID AND "
			+"JP.JDID = "+idJogador
			+" AND JP.PGID = "+idPersonagem;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);


	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi encontrado nenhum Cenário!";
		WarBugsLog::_log->Items->Add(texto);		
		return -1;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	idCenario = System::Int32::Parse(dados[0]->ToString());

	return idCenario;
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

					dado[0] = System::Int32::Parse(dados[nomeCampos->IndexOf(L"ITID")]->ToString());
					((CConsumableItem *)item)->setID(dado[0]);

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
	CBolsaList * listaBolsa = new CBolsaList();

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

			float tempX = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"BSX")]->ToString()));
			float tempY = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"BSY")]->ToString()));
			float tempZ = float(System::Double::Parse(dados[nomeCampos->IndexOf(L"BSZ")]->ToString()));

			bolsa.setPosition(tempX,tempZ);

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
	CPortal * portal = new CPortal();

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
						 float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTX")]->ToString())),
					     float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PTDESTZ")]->ToString())));


	portal->setPosition(float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCX")]->ToString())),
					   float(System::Double::Parse(dados[nomeCampos->IndexOf(L"PTLOCZ")]->ToString())));



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

	System::String ^ query;

	query = L"SELECT MAX(PGID) NOVOID FROM PERSONAGEM";

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

	return result+1;
}

long  CDataManager::novoIdBolsas()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();
	TDadosBD ^ nomeCampos = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	System::String ^ query;

	query = L"SELECT MAX(BSID) NOVOID FROM BOLSA";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi possível contar as Bolsas";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		nomeCampos->Add(dados[0]);
		dados->RemoveAt(0);
	}

	result = System::Int32::Parse(dados[0]->ToString());

	return result+1;
}

long  CDataManager::novoIdItens()
{
	long result = 0;
	
	TDadosBD ^ dados      = gcnew TDadosBD();

	unsigned int numRegs   = 0;
	unsigned int numCampos = 0;

	System::String ^ query;

	query = L"SELECT MAX(ITID)NOVOID FROM ITEMBASE";

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi possível contar os Personagens";
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}

	for(int i = 0; i < (int)numCampos; i++)
	{
		dados->RemoveAt(0);
	}

	result = System::Int32::Parse(dados[0]->ToString());

	return result+1;
}

//ATUALIZAÇÕES
//Personagem
void CDataManager::updatePersonagem(int id, float posX, float posZ)
{}

void CDataManager::updatePersonagem(int id, int nivel, int xp)
{}

//Inserções
bool CDataManager::insertPersonagemJogador(CPersonagemJogador * p1, int idJogador)
{
	bool result = false;

	System::String ^ query;
	System::String ^ temp;
	
	p1->setID(novoIdPersonagem());

	temp = gcnew System::String(p1->getName());

	int tempRaca = p1->getRace();

	System::String ^ moveSpeed = L""+p1->getMoveSpeed();
	moveSpeed = pointFormat(moveSpeed);

	System::String ^ direction = L""+p1->getDirection();
	direction = pointFormat(direction);

	System::String ^ x = L""+p1->getPosition()->x;
	x = pointFormat(x);

	System::String ^ z = L""+p1->getPosition()->z;
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

	
	System::String ^texto;

	//se não for inserido com sucesso
	if(_dataBase->insertNow(toChar(query)))
	{
		texto = L"Personagem '"+temp+"' Incluído com sucesso";

		query = L"INSERT INTO JOGADOR_PERSONAGEM "
				+" VALUES ("+p1->getID()+","+idJogador+")";

		
		//se não for inserido com sucesso
		if(_dataBase->insertNow(toChar(query)))
		{
			texto = L"Personagem '"+temp+"' Incluído com sucesso";

			if(p1->getRace() == BESOURO)
			{
				query = L"INSERT INTO ITEM_RELACIONAL(ITID, PGID) "
						+" VALUES ("+(((int)I_MARTELO_GUERRA)-1)+","+p1->getID()+")";

				
				//se não for inserido com sucesso
				if(_dataBase->insertNow(toChar(query)))
				{
					texto = L"item do Personagem '"+temp+"' Incluído com sucesso";
				}
				else
				{
					texto = L"Não foi possivel incluir item do personagem '"+temp+"'.";
				}
			}

			result = true;
		}
		else
		{
			texto = L"Não foi possivel incluir o personagem '"+temp+"'.";
		}

		WarBugsLog::_log->Items->Add(texto);	

	}
	else
	{
		texto = L"Não foi possivel incluir o personagem '"+temp+"'.";
	}

	WarBugsLog::_log->Items->Add(texto);

	return result;

}

void CDataManager::insertPersonagem(CPeopleList p1)
{}


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

	System::String ^ query;

	query = L"SELECT COUNT(PGID) FROM JOGADOR_PERSONAGEM WHERE JDID = "+idJogador;

	_dataBase->selectNow(toChar(query), numCampos, numRegs, dados);

	if(numRegs == 0 || numCampos == 0)
	{
		System::String ^texto = L"Não foi possível contar os Personagens do Jogador "+idJogador;
		WarBugsLog::_log->Items->Add(texto);		
		return result;	
	}	
	
	
	for(int i = 0; i < (int)numCampos; i++)
	{
		dados->RemoveAt(0);
	}

	result = System::Int32::Parse(dados[0]->ToString());

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

	System::String ^ query;
	System::String ^ temp;
	
	temp = gcnew System::String(nomePersonagem);


	query = L"DELETE FROM JOGADOR_PERSONAGEM JP"
			+" USING JOGADOR_PERSONAGEM JP, PERSONAGEM P"
			+" WHERE JP.PGID = P.PGID AND JP.JDID = "+idJogador
			+" AND P.PGID = "+idPersonagem
			+" AND P.PGNOME = '"+temp+"'";

	
	System::String ^texto;

	//se não for EXCLUIDO com sucesso
	if(_dataBase->deleteNow(toChar(query)))
	{
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PGID = "+idPersonagem;
		
		//se não for EXCLUIDO com sucesso
		if(_dataBase->deleteNow(toChar(query)))
		{
			texto = L"Os Itens do personagem '"+temp+"' foram excluido com sucesso";
			result = true;
		}
		else
		{
			texto = L"Não foi possivel excluir os itens do personagem '"+temp+"'.";
		}

		query = L"DELETE FROM PERSONAGEM WHERE PGID = "+idPersonagem;
		
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
		texto = L"Não foi possivel exluir o personagem '"+temp+"'.";
	}

	WarBugsLog::_log->Items->Add(texto);

	return result;

}

/*
	Transforma ',' em '.'
*/
System::String ^ CDataManager::pointFormat(System::String ^ d1)
{
	char * c = toChar(d1);

	for(int i = 0; i < (int)strlen(c); i++)
	{
		if(c[i] == ',')
		{
			c[i] = '.';
		}
	}

	d1 = gcnew System::String(c);

	return d1;

}

/*
	Salvará todas as informações que estão na memória, para o servidor
*/
void CDataManager::backupAll(CCenarioList * cenarioList)
{

	// 1. Salva Persoangens
		// 1.1 Update do personagem e todas as suas variaveis
	// 2. Salva Itens Personagens
		// 2.1 Remove itens que não estão mais com o personagem
		// 2.2 Atualiza os que ainda estão com ele(inclusive a durabilidade, mas no relacionamento)
		// 2.3 Insere os novos itens que o persoangem possui
	// 3. Salva Poderes do Personagem
		// 3.1 Atualiza as informações dos poderes que o personagem possui
	// 4. Salva Informações da formula de mercado se o personagem for o vendedor
		// 4.1 Insere as informações que o vendedor possui naquele momento
	// 5. Salva as bolsas
		// 5.1 Remove as que não existirem mais
		// 5.2 Atualiza as que ainda existirem
		// 5.3 Insere as que não estão salvas
	// 6. Salva o Cénario
		// 6.1 Atualiza a Localização de todos os Personagens

	for(int p = 0; p < cenarioList->size(); p++)
	{
		for(int a = 0; a < cenarioList->getElementAt(p)->playerCount(); a++)
		{
			updatePersonagemJogador(cenarioList->getElementAt(p)->getPlayerAt(a));		
		}

		for(int u = 0; u < cenarioList->getElementAt(p)->bagCount(); u++)
		{
			updateBolsa(cenarioList->getElementAt(p)->getBagAt(u);
		}
	
	}


}

/*
	Atualiza todas as bolsa que estiverem no cenário
	param b1 -> bolsa que esrá atualizada no BD
*/
void CDataManager::updateBolsa(CBolsa * b1, int idCenario)
{
	System::String ^ query;

	int tempItem[9][8];

	query = L"DELETE FROM ITEM_RELACIONAL WHERE BSID = "+b1->getID();

	_dataBase->deleteNow(toChar(query));

	query = L"DELETE FROM BOLSA WHERE BSID = "+b1->getID();

	_dataBase->deleteNow(toChar(query));

	query = L"INSERT INTO BOLSA VALUES ("+novoIdBolsas()+","+pointFormat(L""+b1->getPosition()->x)+",0,"
		+pointFormat(L""+b1->getPosition()->z)+","+idCenario+")";

	_dataBase->insertNow(query);

	
	for(int p = 0; p < 9; p++)
	{
		if(b1->getElementAt(p) != NULL)
		if(b1->getElementAt(p)->getID() != NULL)
		{
		
			if(b1->getElementAt(p)->getTipo() == ARMA)
			{
				tempItem[p][0] = ((CWeapon *)b1->getElementAt(p))->getID();
				tempItem[p][1] = ((CWeapon *)b1->getElementAt(p))->getDurability();
				tempItem[p][2] = ((CWeapon *)b1->getElementAt(p))->getMod();
				tempItem[p][3] = ((CWeapon *)b1->getElementAt(p))->getMinDamage();
				tempItem[p][4] = ((CWeapon *)b1->getElementAt(p))->getMaxDamage();
				tempItem[p][5] = ((CWeapon *)b1->getElementAt(p))->getSpeed();
				tempItem[p][6] = ((CWeapon *)b1->getElementAt(p))->getRange();
				tempItem[p][7] = ((CWeapon *)b1->getElementAt(p))->getMagicLevel();
			}
			else
			if(b1->getElementAt(p)->getTipo() == ARMADURA)
			{
				tempItem[p][0] = ((CArmor *)b1->getElementAt(p))->getID();
				tempItem[p][1] = ((CArmor *)b1->getElementAt(p))->getDurability();
				tempItem[p][2] = ((CArmor *)b1->getElementAt(p))->getDef();
				tempItem[p][3] = ((CArmor *)b1->getElementAt(p))->getMagicLevel();
				tempItem[p][4] = 0;
				tempItem[p][5] = 0;
				tempItem[p][6] = 0;
				tempItem[p][7] = 0;
			}
			else
			{
				tempItem[p][0] = b1->getElementAt(p)->getID();
				tempItem[p][1] = b1->getElementAt(p)->getDurability();
				tempItem[p][2] = 0;
				tempItem[p][3] = 0;
				tempItem[p][4] = 0;
				tempItem[p][5] = 0;
				tempItem[p][6] = 0;
				tempItem[p][7] = 0;
			}
		}
		else
		{
			tempItem[p][0] = -1;
			tempItem[p][1] = 0;
			tempItem[p][2] = 0;
			tempItem[p][3] = 0;
			tempItem[p][4] = 0;
			tempItem[p][5] = 0;
			tempItem[p][6] = 0;
			tempItem[p][7] = 0;
		}				
	
	}

	//ARMA
	//IRVALBONUS1 = DURABILIDADE DO ITEM
	//IRVALBONUS2 = MODIFICADOR ARMA
	//IRVALBONUS3 = DANO MINIMO
	//IRVALBONUS4 = DANO MAXIMO
	//IRVALBONUS5 = TAXA ATAQUE
	//IRVALBONUS6 = ALCANCE
	//IRVALBONUS7 = NIVEL MAGICO

	//ARMADURA
	//IRVALBONUS1 = DURABILIDADE DO ITEM
	//IRVALBONUS2 = DEFESA
	//IRVALBONUS3 = NIVEL MAGICO
	//IRVALBONUS4 = 0
	//IRVALBONUS5 = 0
	//IRVALBONUS6 = 0
	//IRVALBONUS7 = 0

	for(int p = 0; p < 9; p++)
	{
		if(tempItem[p][0] != -1)
		{
			query = L"INSERT INTO ITEM_RELACIONAL(ITID, BSID, IRVALBONUS1, "
					+"IRVALBONUS2, IRVALBONUS3, IRVALBONUS4, IRVALBONUS5,  "
					+"IRVALBONUS6, IRVALBONUS7) VALUES ( "
					+tempItem[p][0]+", "+b1->getID()+", "+tempItem[p][1]+", "
					+tempItem[p][2]+", "+tempItem[p][3]+", "+tempItem[p][4]+", "
					+tempItem[p][5]+", "+tempItem[p][6]+", "+tempItem[p][7]+")";

			_dataBase->insertNow(toChar(query));
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
	System::String ^ query;

	query = L"UPDATE PERSONAGEM SET "
			+"  PGNIVEL = "+p1->getLevel()+
			+", PGDINHEIRO = "+p1->getMoney()+
			+", PGEXPERIENCIA = "+p1->getXP()+
			+", PGEXPERIENCIAMAX = "+p1->getMaxXP()+
			+", PGPONTOSVIDA = "+p1->getStats()->getPV()+
			+", PGPONTOSVIDAMAX = "+p1->getStats()->getMaxPV()+
			+", PGPONTOSPODER = "+p1->getStats()->getPM()+
			+", PGPONTOSPODERMAX = "+p1->getStats()->getMaxPM()+
			+", PGDIRECAO = "+pointFormat(L""+p1->getDirection())+
			+", PGVELOCIDADE = "+pointFormat(L""+p1->getMoveSpeed())+
			+", PGFORCA = "+p1->getFOR()+
			+", PGAGILIDADE = "+p1->getAGI()+
			+", PGDESTREZA = "+p1->getDES()+
			+", PGRESISTENCIA = "+p1->getRES()+
			+", PGINSTINTO = "+p1->getINS()+
			+", PGATAQUEDISTANCIA = "+p1->getStats()->getRangedAttack()+
			+", PGATAQUECORPO = "+p1->getStats()->getMeleeAttack()+
			+", PGDANOCORPO = "+p1->getStats()->getMeleeDamage()+
			+", PGDANODISTANCIA = "+p1->getStats()->getRangedDamage()+
			+", PGDEFESA = "+p1->getStats()->getDefense()+
			+", PGTAXAATAQUE = "+p1->getStats()->getAttackRate()+
			+", PGTEMPOCARGA = "+p1->getStats()->getChargeTime()+
			+", PGLEALARANHA = "+p1->getLoyalty()->getLoyaltyToSpider()+
			+", PGLEALBESOURO = "+p1->getLoyalty()->getLoyaltyToBeetle()+
			+", PGLEALESCORPIAO = "+p1->getLoyalty()->getLoyaltyToScorpion()+
			+", PGLEALLOUVA = "+p1->getLoyalty()->getLoyaltyToMantis()+
			+", PGLEALVESPA = "+p1->getLoyalty()->getLoyaltyToWasp()+
			+", PGIDARMOR = "+(p1->getEquip()->armadura != NULL ? p1->getEquip()->armadura->getID() : -1)+
			+", PGIDWEAPON = "+(p1->getEquip()->arma != NULL ? p1->getEquip()->arma->getID() : -1)+
			+", PGX = "+p1->getPosition()->x+
			+", PGZ = "+p1->getPosition()->z+
			+", PGBONUSPOINTSPRIMARIAS = "+p1->getPointsLeft()+
			+", PGBONUSPOINTSPODER = "+p1->getSkillPointsLeft()+
			+"  WHERE PGID = "+p1->getID();

	if(_dataBase->updateNow(toChar(query)))
	{

		//não esquecer que o item equipado também entra nesta lista
		query = L"DELETE FROM ITEM_RELACIONAL WHERE PGID = "+p1->getID();
				
		//se exluiu os itens que não estavam com ele
		if(_dataBase->deleteNow(toChar(query)))
		{

			int tempItem[11][8];

			for(int p = 0; p < 11; p++)
			{
				if(p1->getBolsa()->getElementAt(p) != NULL)
				if(p1->getBolsa()->getElementAt(p)->getID() != NULL)
				{
					tempItem[9][0] = p1->getBolsa()->getElementAt(p)->getID();
					tempItem[9][1] = p1->getBolsa()->getElementAt(p)->getDurability();
					tempItem[9][2] = 0;
					tempItem[9][3] = 0;
					tempItem[9][4] = 0;
					tempItem[9][5] = 0;
					tempItem[9][6] = 0;
					tempItem[9][7] = 0;
				}
				else
				{
					tempItem[9][0] = -1;
					tempItem[9][1] = 0;
					tempItem[9][2] = 0;
					tempItem[9][3] = 0;
					tempItem[9][4] = 0;
					tempItem[9][5] = 0;
					tempItem[9][6] = 0;
					tempItem[9][7] = 0;
				}				
			
			}

			if(p1->getEquip() != NULL)
			if(p1->getEquip()->arma != NULL)
			if(p1->getEquip()->arma->getID() != NULL)
			{
				tempItem[9][0] = p1->getEquip()->arma->getID();
				tempItem[9][1] = p1->getEquip()->arma->getDurability();
				tempItem[9][2] = p1->getEquip()->arma->getMod();
				tempItem[9][3] = p1->getEquip()->arma->getMinDamage();
				tempItem[9][4] = p1->getEquip()->arma->getMaxDamage();
				tempItem[9][5] = p1->getEquip()->arma->getSpeed();
				tempItem[9][6] = p1->getEquip()->arma->getRange();
				tempItem[9][7] = p1->getEquip()->arma->getMagicLevel();
			}
			else
			{
				tempItem[9][0] = -1;
				tempItem[9][1] = 0;
				tempItem[9][2] = 0;
				tempItem[9][3] = 0;
				tempItem[9][4] = 0;
				tempItem[9][5] = 0;
				tempItem[9][6] = 0;
				tempItem[9][7] = 0;
			}

			if(p1->getEquip() != NULL)
			if(p1->getEquip()->armadura != NULL)
			if(p1->getEquip()->armadura->getID() != NULL)
			{
				tempItem[10][0] = p1->getEquip()->armadura->getID();
				tempItem[10][1] = p1->getEquip()->armadura->getDurability();
				tempItem[10][2] = p1->getEquip()->armadura->getDef();
				tempItem[10][3] = p1->getEquip()->armadura->getMagicLevel();
				tempItem[10][4] = 0;
				tempItem[10][5] = 0;
				tempItem[10][6] = 0;
				tempItem[10][7] = 0;

			}
			else
			{
				tempItem[10][0] = -1;
				tempItem[10][1] = 0;
				tempItem[10][2] = 0;
				tempItem[10][3] = 0;
				tempItem[10][4] = 0;
				tempItem[10][5] = 0;
				tempItem[10][6] = 0;
				tempItem[10][7] = 0;
			}

			//ARMA
			//IRVALBONUS1 = DURABILIDADE DO ITEM
			//IRVALBONUS2 = MODIFICADOR ARMA
			//IRVALBONUS3 = DANO MINIMO
			//IRVALBONUS4 = DANO MAXIMO
			//IRVALBONUS5 = TAXA ATAQUE
			//IRVALBONUS6 = ALCANCE
			//IRVALBONUS7 = NIVEL MAGICO

			//ARMADURA
			//IRVALBONUS1 = DURABILIDADE DO ITEM
			//IRVALBONUS2 = DEFESA
			//IRVALBONUS3 = NIVEL MAGICO
			//IRVALBONUS4 = 0
			//IRVALBONUS5 = 0
			//IRVALBONUS6 = 0
			//IRVALBONUS7 = 0

			for(int p = 0; p < 11; p++)
			{
				if(tempItem[p][0] != -1)
				{
					query = L"INSERT INTO ITEM_RELACIONAL(ITID, PGID, IRVALBONUS1, "
							+"IRVALBONUS2, IRVALBONUS3, IRVALBONUS4, IRVALBONUS5,  "
							+"IRVALBONUS6, IRVALBONUS7) VALUES ( "
							+tempItem[p][0]+", "+p1->getID()+", "+tempItem[p][1]+", "
							+tempItem[p][2]+", "+tempItem[p][3]+", "+tempItem[p][4]+", "
							+tempItem[p][5]+", "+tempItem[p][6]+", "+tempItem[p][7]+")";

					_dataBase->insertNow(toChar(query));
				}
			}
			
			//DEPOIS DE DESCOBRIR COMO FUNCIONARÁ O SISTEMA DE PODER COLOCAREI A VINCULAÇÃO DELE AKI


			//ATUALIZA O CENÁRIO NO JOGADOR SE ENCONTRA

			query = L"UPDATE PERSONAGEM_CENARIO SET CNID = "+p1->getScene()->getSceneID()
					+", PGID = "+p1->getID()+" WHERE PGID = "+p1->getID();

			_dataBase->updateNow(toChar(query));

		}
	}
			
}