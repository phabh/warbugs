#include <string>
#include <iostream>
#include <stdlib.h>
#include "DataBase.h"
using namespace std;



/**
 *  Classe de Menu
 *		Esta classe conterá o menu para a manutenção do BD e do jogo inteiro em si
 */
class Menu
{
		int quantidade;
		string *listaMenu;
		CDataBase BD;

	public:
		Menu();
		void criarMenuPrincipal();
		void opcoesMenuPrincipal();
		void criarMenuBD();
		void opcoesMenuBD();
		void criarMenu(string menu[], int numItens);
		void exibirMenu();
		void criarConexaoBD();
		void fazerConsulta();

};
//Fim classe Menu

//Metodos
Menu::Menu()
{}

void Menu::criarMenu(string menu[], int numItens)
{
	quantidade = numItens;
	listaMenu = new string[numItens];
	listaMenu = menu;
}

void Menu::criarMenuPrincipal()
{
	string menu[3];
	menu[0] = "Operações com Banco de Dados";
	menu[1] = "Operações com o jogo";
	menu[2] = "Status do jogo";

	criarMenu(menu, 3);
	exibirMenu();
	opcoesMenuPrincipal();
}

void Menu::exibirMenu()
{
	system("cls");
	cout<<"WarBugs Server 1.0v\n\n";
	cout<<"Opções:\n\n";

	for(int i = 0; i < quantidade; i++)
	{
		cout<<"  ";
		cout<<i+1;
		cout<<" - ";
		cout<<listaMenu[i];
		cout<<"\n";
	}
	cout<<"\n\n";
}

void Menu::opcoesMenuPrincipal()
{
	int opcao = 0;
	cout<<"\nEscolha: ";
	cin>>opcao;
	

	switch(opcao)
	{
		case 1: //Operações com Banco de Dados
			{
				criarMenuBD();
				break;
			}
		case 2: //Operações com o jogo
			{
				break;
			}

		case 3: //Status do jogo
			{
				break;
			}
		default:
			{
				cout<<"Escolha invalida!\n";
				opcoesMenuPrincipal();
				break;
			}
	}
}

void Menu::criarMenuBD()
{
	string menu[4];
	menu[0] = "Verificar conexão";
	menu[1] = "Criar conexão";
	menu[2] = "Fazer consultas";
	menu[3] = "Voltar";

	criarMenu(menu, 4);
	exibirMenu();
	opcoesMenuBD();		
}

void Menu::opcoesMenuBD()
{
	int opcao = 0;
	cout<<"\nEscolha: ";
	cin>>opcao;
	

	switch(opcao)
	{
		case 1: //Verificar Conexão
			{

				break;
			}
		case 2: //Criar Conexão
			{
				criarConexaoBD();
				break;
			}

		case 3: //Fazer Consultas
			{
				fazerConsulta();
				break;
			}
		case 4:
			{
				criarMenuPrincipal();
				break;
			}
		default:
			{
				cout<<"Escolha invalida!\n";
				opcoesMenuBD();
				break;
			}
	}
}

void Menu::criarConexaoBD()
{
	BD.connectNow("localhost","warbugs","bd","bugsteam");
	criarMenuBD();
}

void Menu::fazerConsulta()
{
	char* str;
	TDadosBD dados;
	unsigned int numCampos;
	unsigned int numRegs;
	unsigned int indexCampos = 0, indexRegs = 0;

	str = new char[2];
	gets_s(str,2);
	str = new char[2000];
	cout<<"\n\n\nDigite a sua consulta SQL e aperte Enter:\n";
	gets_s(str,2000);

	BD.selectNow(str, numCampos, numRegs, dados);
	cout<<numCampos<<" - "<<numRegs;
	
	while (numRegs > indexRegs)
	{
		for(indexCampos = 0; indexCampos < numCampos+1; indexCampos++)
		{
			printf("%s\n",dados[indexCampos].c_str() != NULL ? dados[indexCampos].c_str(): "NULL");	
		}
		indexRegs++;
	} 

	system("pause");
	criarMenuBD();
}