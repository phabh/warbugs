/*
* Classe CEventManager
*
* Autor: Eder Figueiredo
*
* Objetivo: Classe que gerencia os eventos ao decorrer do jogo
*
*/
/*
 * Primeiro Byte: Indetificação de caso
 * Segundo Byte: Especificação de caso
 */
class CEventManager
{
private:
	//Conversão de dados
	static int charToInt(char a)
	{
		return((int)a - 48);
	}
	//Pacotes fora da tela de jogo
	static void onLogin(char package[]){}
	static void onCharCreate(char package[]){}
	static void onCharSelect(char package[]){}
	static void onCharDelete(char package[]){}
	static void onEnterScene(char package[]){}
	static void onExit(char package[]){}
	//Pacotes da tela de jogo
	static void onExitScene(char package[]){}

	static void onUpdate(char package[]){}
	static void onEquip(char package[]){}
	static void onUnequip(char package[]){}
	static void onUseItem(char package[]){}
	static void onTradeCheck(char package[]){}
	static void onTradeExecution(char package[]){}
	static void onLoot(char package[]){}
	static void onDrop(char package[]){}

	static void onTarget(char package[]){}
	static void onAttack(char package[]){}
	static void onUseSkill(char package[]){}
	static void onDeath(char package[]){}
	static void onTakeDamage(char package[]){}
	
public:
	static void getPackage(char package[])
	{
		int i = charToInt(package[0]);
		switch(i)
		{
		case 0:
			//Caso de login
			i = charToInt(package[1]);
			switch(i)
			{
			case 0:
				onLogin(package);
				break;
			case 1:
				onCharCreate(package);
				break;
			case 2:
				onCharSelect(package);
				break;
			case 3:
				onCharDelete(package);
				break;
			case 4:
				onEnterScene(package);
				break;
			case 5:
				onExitScene(package);
				break;
			case 6:
				onExit(package);
				break;
			default:
				//Decidir o que colokr aki
				break;
			}
			break;
		case 1:
			//Caso de update
			i = charToInt(package[1]);
			switch(i)
			{
			case 0:
				onUpdate(package);
				break;
			case 1:
				onEquip(package);
				break;
			case 2:
				onUnequip(package);
				break;
			case 3:
				onUseItem(package);
				break;
			case 4:
				onTradeCheck(package);
				break;
			case 5:
				onTradeExecution(package);
				break;
			case 6:
				onLoot(package);
				break;
			case 7:
				onDrop(package);
				break;
			default:
				//Decidir o que colokr aki
				break;
			}
		case 2:
			//Caso de combate
			i = charToInt(package[1]);
			switch(i)
			{
			}
		}
	}
};