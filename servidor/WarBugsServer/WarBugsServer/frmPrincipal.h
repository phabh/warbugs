#pragma once
#include "CCoreServer.h"
#include <stdlib.h>
#include <vcclr.h>

namespace WarBugsServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmPrincipal : public System::Windows::Forms::Form
	{
	public:
		// Variaveis do Jogo
		CDataBase			* _dataBase;
	private: System::Windows::Forms::ToolStripStatusLabel^  barHora;
	private: System::Windows::Forms::ToolStripStatusLabel^  barFPS;
	private: System::Windows::Forms::ToolStripStatusLabel^  barTempoAtualizacao;
	private: System::Windows::Forms::TabPage^  tabConfig;
	private: System::Windows::Forms::GroupBox^  gbConfigIniciais;




	private: System::Windows::Forms::GroupBox^  gbConfigBD;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  labValorAtualBkp;

	private: System::Windows::Forms::Button^  btAplicarHorasBkp;



	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  labValorBkpMercado;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btAplicarMercadoBkp;



	private: System::Windows::Forms::Label^  lnovoValorBkp;
	private: System::Windows::Forms::Label^  labValorBkpTotal;









	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  labValorToleranciaPing;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btAplicarToleranciaPing;



	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  labValorVerPing;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  btAplicarIntervaloPing;




	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  labValorFPS;


	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  btAplicarFPS;
	private: System::Windows::Forms::MaskedTextBox^  txtValorBkpTotal;

	private: System::Windows::Forms::MaskedTextBox^  txtToleranciaPing;
	private: System::Windows::Forms::MaskedTextBox^  txtValorVerPing;
	private: System::Windows::Forms::MaskedTextBox^  txtValorFPS;
	private: System::Windows::Forms::MaskedTextBox^  txtValorBkpMercado;










	public: 
		CCoreServer			^ _coreServer;


		frmPrincipal(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			WarBugsLog::_log = logBox;
			_dataBase = new CDataBase("localhost","warbugs","bd","bugsteam");
			this->barStatusBD->Text = L"Status BD: "+( _dataBase->isConnected() ? "ON":"OFF");
			this->barStatusJogo->Text = L"Status Jogo: "+( timer->Enabled ? "ON":"OFF");
			_coreServer = gcnew CCoreServer(_dataBase);
			this->barHora->Text = L""+DateTime::Now;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmPrincipal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  abas;
	protected: 

	protected: 

	private: System::Windows::Forms::TabPage^  tabJogadoresOn;
	private: System::Windows::Forms::TabPage^  tabManutencaoBD;
	private: System::Windows::Forms::StatusStrip^  barStatus;
	protected: 


	private: System::Windows::Forms::ToolStripStatusLabel^  barStatusJogo;
	private: System::Windows::Forms::MenuStrip^  menu;
	private: System::Windows::Forms::DataGridView^  gridResultados;



	private: System::Windows::Forms::Button^  btConsultar;

	private: System::Windows::Forms::Button^  btExecutar;

	private: System::Windows::Forms::Button^  btConectar;

	private: System::Windows::Forms::TextBox^  txtBD;

	private: System::Windows::Forms::TextBox^  txtHost;

	private: System::Windows::Forms::TextBox^  txtSenha;

	private: System::Windows::Forms::TextBox^  txtLogin;
	private: System::Windows::Forms::TextBox^  txtSQL;


	private: System::Windows::Forms::Label^  labResultados;

	private: System::Windows::Forms::Label^  labSQL;


	private: System::Windows::Forms::Label^  labBD;

	private: System::Windows::Forms::Label^  labHost;

	private: System::Windows::Forms::Label^  labSenha;

	private: System::Windows::Forms::Label^  labLogin;
	private: System::Windows::Forms::ToolStripStatusLabel^  barStatusBD;
	private: System::Windows::Forms::ToolStripStatusLabel^  barNumJogadores;
	private: System::Windows::Forms::ToolStripMenuItem^  arquivoToolStripMenuItem;
	private: System::Windows::Forms::DataGridView^  gridJogadores;




	private: System::Windows::Forms::GroupBox^  gbJogador;
	private: System::Windows::Forms::Button^  btMandarMSG;


	private: System::Windows::Forms::Button^  btKicar;

	private: System::Windows::Forms::GroupBox^  gbServer;
	private: System::Windows::Forms::Button^  btLigarServer;
	private: System::Windows::Forms::TextBox^  txtMSG;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  idConexao;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomeJogador;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomePersonagem;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomeCenario;
private: System::Windows::Forms::Timer^  timer;

	private: System::Windows::Forms::TabPage^  tabLog;
	private: System::Windows::Forms::ListBox^  logBox;
	private: System::ComponentModel::IContainer^  components;











	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmPrincipal::typeid));
			this->abas = (gcnew System::Windows::Forms::TabControl());
			this->tabJogadoresOn = (gcnew System::Windows::Forms::TabPage());
			this->gbJogador = (gcnew System::Windows::Forms::GroupBox());
			this->txtMSG = (gcnew System::Windows::Forms::TextBox());
			this->btMandarMSG = (gcnew System::Windows::Forms::Button());
			this->btKicar = (gcnew System::Windows::Forms::Button());
			this->gbServer = (gcnew System::Windows::Forms::GroupBox());
			this->btLigarServer = (gcnew System::Windows::Forms::Button());
			this->gridJogadores = (gcnew System::Windows::Forms::DataGridView());
			this->idConexao = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomeJogador = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomePersonagem = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomeCenario = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabConfig = (gcnew System::Windows::Forms::TabPage());
			this->gbConfigBD = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorBkpMercado = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labValorBkpMercado = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btAplicarMercadoBkp = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorBkpTotal = (gcnew System::Windows::Forms::MaskedTextBox());
			this->lnovoValorBkp = (gcnew System::Windows::Forms::Label());
			this->labValorBkpTotal = (gcnew System::Windows::Forms::Label());
			this->labValorAtualBkp = (gcnew System::Windows::Forms::Label());
			this->btAplicarHorasBkp = (gcnew System::Windows::Forms::Button());
			this->gbConfigIniciais = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->txtToleranciaPing = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->labValorToleranciaPing = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btAplicarToleranciaPing = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorVerPing = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labValorVerPing = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->btAplicarIntervaloPing = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorFPS = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labValorFPS = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btAplicarFPS = (gcnew System::Windows::Forms::Button());
			this->tabManutencaoBD = (gcnew System::Windows::Forms::TabPage());
			this->labResultados = (gcnew System::Windows::Forms::Label());
			this->labSQL = (gcnew System::Windows::Forms::Label());
			this->labBD = (gcnew System::Windows::Forms::Label());
			this->labHost = (gcnew System::Windows::Forms::Label());
			this->labSenha = (gcnew System::Windows::Forms::Label());
			this->labLogin = (gcnew System::Windows::Forms::Label());
			this->gridResultados = (gcnew System::Windows::Forms::DataGridView());
			this->btConsultar = (gcnew System::Windows::Forms::Button());
			this->btExecutar = (gcnew System::Windows::Forms::Button());
			this->btConectar = (gcnew System::Windows::Forms::Button());
			this->txtBD = (gcnew System::Windows::Forms::TextBox());
			this->txtHost = (gcnew System::Windows::Forms::TextBox());
			this->txtSenha = (gcnew System::Windows::Forms::TextBox());
			this->txtLogin = (gcnew System::Windows::Forms::TextBox());
			this->txtSQL = (gcnew System::Windows::Forms::TextBox());
			this->tabLog = (gcnew System::Windows::Forms::TabPage());
			this->logBox = (gcnew System::Windows::Forms::ListBox());
			this->barStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->barStatusJogo = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barStatusBD = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barNumJogadores = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barHora = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barTempoAtualizacao = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->arquivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->abas->SuspendLayout();
			this->tabJogadoresOn->SuspendLayout();
			this->gbJogador->SuspendLayout();
			this->gbServer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridJogadores))->BeginInit();
			this->tabConfig->SuspendLayout();
			this->gbConfigBD->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->gbConfigIniciais->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tabManutencaoBD->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridResultados))->BeginInit();
			this->tabLog->SuspendLayout();
			this->barStatus->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// abas
			// 
			this->abas->Controls->Add(this->tabJogadoresOn);
			this->abas->Controls->Add(this->tabConfig);
			this->abas->Controls->Add(this->tabManutencaoBD);
			this->abas->Controls->Add(this->tabLog);
			this->abas->Location = System::Drawing::Point(2, 27);
			this->abas->Name = L"abas";
			this->abas->SelectedIndex = 0;
			this->abas->Size = System::Drawing::Size(774, 449);
			this->abas->TabIndex = 0;
			// 
			// tabJogadoresOn
			// 
			this->tabJogadoresOn->Controls->Add(this->gbJogador);
			this->tabJogadoresOn->Controls->Add(this->gbServer);
			this->tabJogadoresOn->Controls->Add(this->gridJogadores);
			this->tabJogadoresOn->Location = System::Drawing::Point(4, 22);
			this->tabJogadoresOn->Name = L"tabJogadoresOn";
			this->tabJogadoresOn->Padding = System::Windows::Forms::Padding(3);
			this->tabJogadoresOn->Size = System::Drawing::Size(766, 423);
			this->tabJogadoresOn->TabIndex = 0;
			this->tabJogadoresOn->Text = L"Jogadores On-Line";
			this->tabJogadoresOn->UseVisualStyleBackColor = true;
			// 
			// gbJogador
			// 
			this->gbJogador->Controls->Add(this->txtMSG);
			this->gbJogador->Controls->Add(this->btMandarMSG);
			this->gbJogador->Controls->Add(this->btKicar);
			this->gbJogador->Location = System::Drawing::Point(644, 99);
			this->gbJogador->Name = L"gbJogador";
			this->gbJogador->Size = System::Drawing::Size(115, 231);
			this->gbJogador->TabIndex = 8;
			this->gbJogador->TabStop = false;
			this->gbJogador->Text = L" Jogador Selecionado";
			// 
			// txtMSG
			// 
			this->txtMSG->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtMSG->Location = System::Drawing::Point(6, 79);
			this->txtMSG->MaxLength = 255;
			this->txtMSG->Multiline = true;
			this->txtMSG->Name = L"txtMSG";
			this->txtMSG->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtMSG->Size = System::Drawing::Size(103, 91);
			this->txtMSG->TabIndex = 5;
			// 
			// btMandarMSG
			// 
			this->btMandarMSG->Location = System::Drawing::Point(6, 176);
			this->btMandarMSG->Name = L"btMandarMSG";
			this->btMandarMSG->Size = System::Drawing::Size(103, 23);
			this->btMandarMSG->TabIndex = 4;
			this->btMandarMSG->Text = L"Mandar MSG";
			this->btMandarMSG->UseVisualStyleBackColor = true;
			// 
			// btKicar
			// 
			this->btKicar->Location = System::Drawing::Point(6, 38);
			this->btKicar->Name = L"btKicar";
			this->btKicar->Size = System::Drawing::Size(103, 23);
			this->btKicar->TabIndex = 3;
			this->btKicar->Text = L"Kicar";
			this->btKicar->UseVisualStyleBackColor = true;
			this->btKicar->Click += gcnew System::EventHandler(this, &frmPrincipal::btKicar_Click);
			// 
			// gbServer
			// 
			this->gbServer->Controls->Add(this->btLigarServer);
			this->gbServer->Location = System::Drawing::Point(644, 6);
			this->gbServer->Name = L"gbServer";
			this->gbServer->Size = System::Drawing::Size(115, 64);
			this->gbServer->TabIndex = 7;
			this->gbServer->TabStop = false;
			this->gbServer->Text = L" Server ";
			// 
			// btLigarServer
			// 
			this->btLigarServer->Location = System::Drawing::Point(6, 29);
			this->btLigarServer->Name = L"btLigarServer";
			this->btLigarServer->Size = System::Drawing::Size(103, 23);
			this->btLigarServer->TabIndex = 3;
			this->btLigarServer->Text = L"Ligar";
			this->btLigarServer->UseVisualStyleBackColor = true;
			this->btLigarServer->Click += gcnew System::EventHandler(this, &frmPrincipal::btLigarServer_Click);
			// 
			// gridJogadores
			// 
			this->gridJogadores->AllowUserToAddRows = false;
			this->gridJogadores->AllowUserToDeleteRows = false;
			this->gridJogadores->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridJogadores->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->idConexao, 
				this->nomeJogador, this->nomePersonagem, this->nomeCenario});
			this->gridJogadores->Location = System::Drawing::Point(3, 6);
			this->gridJogadores->Name = L"gridJogadores";
			this->gridJogadores->ReadOnly = true;
			this->gridJogadores->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->gridJogadores->Size = System::Drawing::Size(637, 414);
			this->gridJogadores->TabIndex = 0;
			// 
			// idConexao
			// 
			this->idConexao->HeaderText = L"IDConexao";
			this->idConexao->Name = L"idConexao";
			this->idConexao->ReadOnly = true;
			this->idConexao->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->idConexao->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->idConexao->Width = 70;
			// 
			// nomeJogador
			// 
			this->nomeJogador->HeaderText = L"Nome do Jogador";
			this->nomeJogador->Name = L"nomeJogador";
			this->nomeJogador->ReadOnly = true;
			this->nomeJogador->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomeJogador->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomeJogador->Width = 150;
			// 
			// nomePersonagem
			// 
			this->nomePersonagem->HeaderText = L"Nome Personagem";
			this->nomePersonagem->Name = L"nomePersonagem";
			this->nomePersonagem->ReadOnly = true;
			this->nomePersonagem->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomePersonagem->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomePersonagem->Width = 150;
			// 
			// nomeCenario
			// 
			this->nomeCenario->HeaderText = L"Cenário";
			this->nomeCenario->Name = L"nomeCenario";
			this->nomeCenario->ReadOnly = true;
			this->nomeCenario->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomeCenario->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomeCenario->Width = 150;
			// 
			// tabConfig
			// 
			this->tabConfig->Controls->Add(this->gbConfigBD);
			this->tabConfig->Controls->Add(this->gbConfigIniciais);
			this->tabConfig->Location = System::Drawing::Point(4, 22);
			this->tabConfig->Name = L"tabConfig";
			this->tabConfig->Padding = System::Windows::Forms::Padding(3);
			this->tabConfig->Size = System::Drawing::Size(766, 423);
			this->tabConfig->TabIndex = 3;
			this->tabConfig->Text = L"Configuração Server";
			this->tabConfig->UseVisualStyleBackColor = true;
			// 
			// gbConfigBD
			// 
			this->gbConfigBD->Controls->Add(this->groupBox2);
			this->gbConfigBD->Controls->Add(this->groupBox1);
			this->gbConfigBD->Location = System::Drawing::Point(352, 6);
			this->gbConfigBD->Name = L"gbConfigBD";
			this->gbConfigBD->Size = System::Drawing::Size(406, 411);
			this->gbConfigBD->TabIndex = 1;
			this->gbConfigBD->TabStop = false;
			this->gbConfigBD->Text = L" Configurações de Saves ";
			this->gbConfigBD->UseCompatibleTextRendering = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->txtValorBkpMercado);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->labValorBkpMercado);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->btAplicarMercadoBkp);
			this->groupBox2->Location = System::Drawing::Point(6, 110);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(245, 85);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L" Tempo de Backup de Mercado ";
			// 
			// txtValorBkpMercado
			// 
			this->txtValorBkpMercado->Location = System::Drawing::Point(83, 59);
			this->txtValorBkpMercado->Mask = L"00";
			this->txtValorBkpMercado->Name = L"txtValorBkpMercado";
			this->txtValorBkpMercado->Size = System::Drawing::Size(73, 20);
			this->txtValorBkpMercado->TabIndex = 15;
			this->txtValorBkpMercado->Text = L"00";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 62);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(66, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Novo Valor: ";
			// 
			// labValorBkpMercado
			// 
			this->labValorBkpMercado->AutoSize = true;
			this->labValorBkpMercado->Location = System::Drawing::Point(132, 27);
			this->labValorBkpMercado->Name = L"labValorBkpMercado";
			this->labValorBkpMercado->Size = System::Drawing::Size(16, 13);
			this->labValorBkpMercado->TabIndex = 9;
			this->labValorBkpMercado->Text = L"0 ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(17, 27);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(110, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Valor Atual (Minutos): ";
			// 
			// btAplicarMercadoBkp
			// 
			this->btAplicarMercadoBkp->Location = System::Drawing::Point(162, 58);
			this->btAplicarMercadoBkp->Name = L"btAplicarMercadoBkp";
			this->btAplicarMercadoBkp->Size = System::Drawing::Size(76, 20);
			this->btAplicarMercadoBkp->TabIndex = 7;
			this->btAplicarMercadoBkp->Text = L"Aplicar";
			this->btAplicarMercadoBkp->UseVisualStyleBackColor = true;
			this->btAplicarMercadoBkp->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarMercadoBkp_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtValorBkpTotal);
			this->groupBox1->Controls->Add(this->lnovoValorBkp);
			this->groupBox1->Controls->Add(this->labValorBkpTotal);
			this->groupBox1->Controls->Add(this->labValorAtualBkp);
			this->groupBox1->Controls->Add(this->btAplicarHorasBkp);
			this->groupBox1->Location = System::Drawing::Point(6, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(245, 85);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L" Tempo de Backup Total  ";
			// 
			// txtValorBkpTotal
			// 
			this->txtValorBkpTotal->Location = System::Drawing::Point(83, 58);
			this->txtValorBkpTotal->Mask = L"00";
			this->txtValorBkpTotal->Name = L"txtValorBkpTotal";
			this->txtValorBkpTotal->Size = System::Drawing::Size(73, 20);
			this->txtValorBkpTotal->TabIndex = 14;
			this->txtValorBkpTotal->Text = L"00";
			// 
			// lnovoValorBkp
			// 
			this->lnovoValorBkp->AutoSize = true;
			this->lnovoValorBkp->Location = System::Drawing::Point(16, 62);
			this->lnovoValorBkp->Name = L"lnovoValorBkp";
			this->lnovoValorBkp->Size = System::Drawing::Size(66, 13);
			this->lnovoValorBkp->TabIndex = 10;
			this->lnovoValorBkp->Text = L"Novo Valor: ";
			// 
			// labValorBkpTotal
			// 
			this->labValorBkpTotal->AutoSize = true;
			this->labValorBkpTotal->Location = System::Drawing::Point(121, 27);
			this->labValorBkpTotal->Name = L"labValorBkpTotal";
			this->labValorBkpTotal->Size = System::Drawing::Size(16, 13);
			this->labValorBkpTotal->TabIndex = 9;
			this->labValorBkpTotal->Text = L"0 ";
			// 
			// labValorAtualBkp
			// 
			this->labValorAtualBkp->AutoSize = true;
			this->labValorAtualBkp->Location = System::Drawing::Point(17, 27);
			this->labValorAtualBkp->Name = L"labValorAtualBkp";
			this->labValorAtualBkp->Size = System::Drawing::Size(101, 13);
			this->labValorAtualBkp->TabIndex = 8;
			this->labValorAtualBkp->Text = L"Valor Atual (Horas): ";
			// 
			// btAplicarHorasBkp
			// 
			this->btAplicarHorasBkp->Location = System::Drawing::Point(162, 58);
			this->btAplicarHorasBkp->Name = L"btAplicarHorasBkp";
			this->btAplicarHorasBkp->Size = System::Drawing::Size(76, 20);
			this->btAplicarHorasBkp->TabIndex = 7;
			this->btAplicarHorasBkp->Text = L"Aplicar";
			this->btAplicarHorasBkp->UseVisualStyleBackColor = true;
			this->btAplicarHorasBkp->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarHorasBkp_Click);
			// 
			// gbConfigIniciais
			// 
			this->gbConfigIniciais->Controls->Add(this->groupBox5);
			this->gbConfigIniciais->Controls->Add(this->groupBox4);
			this->gbConfigIniciais->Controls->Add(this->groupBox3);
			this->gbConfigIniciais->Location = System::Drawing::Point(3, 6);
			this->gbConfigIniciais->Name = L"gbConfigIniciais";
			this->gbConfigIniciais->Size = System::Drawing::Size(343, 411);
			this->gbConfigIniciais->TabIndex = 0;
			this->gbConfigIniciais->TabStop = false;
			this->gbConfigIniciais->Text = L" Configurações Iniciais ";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->txtToleranciaPing);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Controls->Add(this->labValorToleranciaPing);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Controls->Add(this->btAplicarToleranciaPing);
			this->groupBox5->Location = System::Drawing::Point(6, 201);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(245, 85);
			this->groupBox5->TabIndex = 14;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L" Valor de Tolerância de Ping ";
			// 
			// txtToleranciaPing
			// 
			this->txtToleranciaPing->Location = System::Drawing::Point(83, 58);
			this->txtToleranciaPing->Mask = L"000";
			this->txtToleranciaPing->Name = L"txtToleranciaPing";
			this->txtToleranciaPing->Size = System::Drawing::Size(73, 20);
			this->txtToleranciaPing->TabIndex = 13;
			this->txtToleranciaPing->Text = L"005";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(16, 62);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(66, 13);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Novo Valor: ";
			// 
			// labValorToleranciaPing
			// 
			this->labValorToleranciaPing->AutoSize = true;
			this->labValorToleranciaPing->Location = System::Drawing::Point(144, 27);
			this->labValorToleranciaPing->Name = L"labValorToleranciaPing";
			this->labValorToleranciaPing->Size = System::Drawing::Size(16, 13);
			this->labValorToleranciaPing->TabIndex = 9;
			this->labValorToleranciaPing->Text = L"0 ";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(17, 27);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(121, 13);
			this->label12->TabIndex = 8;
			this->label12->Text = L"Valor Atual (Segundos): ";
			// 
			// btAplicarToleranciaPing
			// 
			this->btAplicarToleranciaPing->Location = System::Drawing::Point(162, 58);
			this->btAplicarToleranciaPing->Name = L"btAplicarToleranciaPing";
			this->btAplicarToleranciaPing->Size = System::Drawing::Size(76, 20);
			this->btAplicarToleranciaPing->TabIndex = 7;
			this->btAplicarToleranciaPing->Text = L"Aplicar";
			this->btAplicarToleranciaPing->UseVisualStyleBackColor = true;
			this->btAplicarToleranciaPing->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarToleranciaPing_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->txtValorVerPing);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Controls->Add(this->labValorVerPing);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->btAplicarIntervaloPing);
			this->groupBox4->Location = System::Drawing::Point(6, 110);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(245, 85);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Tempo de Verificação de Ping ";
			// 
			// txtValorVerPing
			// 
			this->txtValorVerPing->Location = System::Drawing::Point(83, 58);
			this->txtValorVerPing->Mask = L"000";
			this->txtValorVerPing->Name = L"txtValorVerPing";
			this->txtValorVerPing->Size = System::Drawing::Size(73, 20);
			this->txtValorVerPing->TabIndex = 12;
			this->txtValorVerPing->Text = L"010";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 62);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Novo Valor: ";
			// 
			// labValorVerPing
			// 
			this->labValorVerPing->AutoSize = true;
			this->labValorVerPing->Location = System::Drawing::Point(144, 27);
			this->labValorVerPing->Name = L"labValorVerPing";
			this->labValorVerPing->Size = System::Drawing::Size(16, 13);
			this->labValorVerPing->TabIndex = 9;
			this->labValorVerPing->Text = L"0 ";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(17, 27);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(121, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Valor Atual (Segundos): ";
			// 
			// btAplicarIntervaloPing
			// 
			this->btAplicarIntervaloPing->Location = System::Drawing::Point(162, 58);
			this->btAplicarIntervaloPing->Name = L"btAplicarIntervaloPing";
			this->btAplicarIntervaloPing->Size = System::Drawing::Size(76, 20);
			this->btAplicarIntervaloPing->TabIndex = 7;
			this->btAplicarIntervaloPing->Text = L"Aplicar";
			this->btAplicarIntervaloPing->UseVisualStyleBackColor = true;
			this->btAplicarIntervaloPing->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarIntervaloPing_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->txtValorFPS);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->labValorFPS);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->btAplicarFPS);
			this->groupBox3->Location = System::Drawing::Point(6, 19);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(245, 85);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"FPS ";
			// 
			// txtValorFPS
			// 
			this->txtValorFPS->Location = System::Drawing::Point(83, 58);
			this->txtValorFPS->Mask = L"00";
			this->txtValorFPS->Name = L"txtValorFPS";
			this->txtValorFPS->Size = System::Drawing::Size(73, 20);
			this->txtValorFPS->TabIndex = 11;
			this->txtValorFPS->Text = L"30";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(16, 62);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(66, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Novo Valor: ";
			// 
			// labValorFPS
			// 
			this->labValorFPS->AutoSize = true;
			this->labValorFPS->Location = System::Drawing::Point(87, 27);
			this->labValorFPS->Name = L"labValorFPS";
			this->labValorFPS->Size = System::Drawing::Size(16, 13);
			this->labValorFPS->TabIndex = 9;
			this->labValorFPS->Text = L"0 ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 27);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(64, 13);
			this->label8->TabIndex = 8;
			this->label8->Text = L"Valor Atual: ";
			// 
			// btAplicarFPS
			// 
			this->btAplicarFPS->Location = System::Drawing::Point(162, 58);
			this->btAplicarFPS->Name = L"btAplicarFPS";
			this->btAplicarFPS->Size = System::Drawing::Size(76, 20);
			this->btAplicarFPS->TabIndex = 7;
			this->btAplicarFPS->Text = L"Aplicar";
			this->btAplicarFPS->UseVisualStyleBackColor = true;
			this->btAplicarFPS->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarFPS_Click);
			// 
			// tabManutencaoBD
			// 
			this->tabManutencaoBD->Controls->Add(this->labResultados);
			this->tabManutencaoBD->Controls->Add(this->labSQL);
			this->tabManutencaoBD->Controls->Add(this->labBD);
			this->tabManutencaoBD->Controls->Add(this->labHost);
			this->tabManutencaoBD->Controls->Add(this->labSenha);
			this->tabManutencaoBD->Controls->Add(this->labLogin);
			this->tabManutencaoBD->Controls->Add(this->gridResultados);
			this->tabManutencaoBD->Controls->Add(this->btConsultar);
			this->tabManutencaoBD->Controls->Add(this->btExecutar);
			this->tabManutencaoBD->Controls->Add(this->btConectar);
			this->tabManutencaoBD->Controls->Add(this->txtBD);
			this->tabManutencaoBD->Controls->Add(this->txtHost);
			this->tabManutencaoBD->Controls->Add(this->txtSenha);
			this->tabManutencaoBD->Controls->Add(this->txtLogin);
			this->tabManutencaoBD->Controls->Add(this->txtSQL);
			this->tabManutencaoBD->Location = System::Drawing::Point(4, 22);
			this->tabManutencaoBD->Name = L"tabManutencaoBD";
			this->tabManutencaoBD->Padding = System::Windows::Forms::Padding(3);
			this->tabManutencaoBD->Size = System::Drawing::Size(766, 423);
			this->tabManutencaoBD->TabIndex = 1;
			this->tabManutencaoBD->Text = L"Manutenção Banco de Dados";
			this->tabManutencaoBD->UseVisualStyleBackColor = true;
			// 
			// labResultados
			// 
			this->labResultados->AutoSize = true;
			this->labResultados->Location = System::Drawing::Point(3, 250);
			this->labResultados->Name = L"labResultados";
			this->labResultados->Size = System::Drawing::Size(60, 13);
			this->labResultados->TabIndex = 14;
			this->labResultados->Text = L"Resultados";
			// 
			// labSQL
			// 
			this->labSQL->AutoSize = true;
			this->labSQL->Location = System::Drawing::Point(3, 64);
			this->labSQL->Name = L"labSQL";
			this->labSQL->Size = System::Drawing::Size(28, 13);
			this->labSQL->TabIndex = 13;
			this->labSQL->Text = L"SQL";
			// 
			// labBD
			// 
			this->labBD->AutoSize = true;
			this->labBD->Location = System::Drawing::Point(449, 17);
			this->labBD->Name = L"labBD";
			this->labBD->Size = System::Drawing::Size(126, 13);
			this->labBD->TabIndex = 12;
			this->labBD->Text = L"Nome da Base de Dados";
			// 
			// labHost
			// 
			this->labHost->AutoSize = true;
			this->labHost->Location = System::Drawing::Point(289, 17);
			this->labHost->Name = L"labHost";
			this->labHost->Size = System::Drawing::Size(29, 13);
			this->labHost->TabIndex = 11;
			this->labHost->Text = L"Host";
			// 
			// labSenha
			// 
			this->labSenha->AutoSize = true;
			this->labSenha->Location = System::Drawing::Point(132, 17);
			this->labSenha->Name = L"labSenha";
			this->labSenha->Size = System::Drawing::Size(38, 13);
			this->labSenha->TabIndex = 10;
			this->labSenha->Text = L"Senha";
			// 
			// labLogin
			// 
			this->labLogin->AutoSize = true;
			this->labLogin->Location = System::Drawing::Point(5, 17);
			this->labLogin->Name = L"labLogin";
			this->labLogin->Size = System::Drawing::Size(33, 13);
			this->labLogin->TabIndex = 9;
			this->labLogin->Text = L"Login";
			// 
			// gridResultados
			// 
			this->gridResultados->AllowUserToAddRows = false;
			this->gridResultados->AllowUserToDeleteRows = false;
			this->gridResultados->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridResultados->Location = System::Drawing::Point(6, 266);
			this->gridResultados->Name = L"gridResultados";
			this->gridResultados->ReadOnly = true;
			this->gridResultados->Size = System::Drawing::Size(752, 150);
			this->gridResultados->TabIndex = 8;
			// 
			// btConsultar
			// 
			this->btConsultar->Location = System::Drawing::Point(607, 241);
			this->btConsultar->Name = L"btConsultar";
			this->btConsultar->Size = System::Drawing::Size(151, 19);
			this->btConsultar->TabIndex = 7;
			this->btConsultar->Text = L"Consultar";
			this->btConsultar->UseVisualStyleBackColor = true;
			this->btConsultar->Click += gcnew System::EventHandler(this, &frmPrincipal::btConsultar_Click);
			// 
			// btExecutar
			// 
			this->btExecutar->Location = System::Drawing::Point(450, 241);
			this->btExecutar->Name = L"btExecutar";
			this->btExecutar->Size = System::Drawing::Size(151, 19);
			this->btExecutar->TabIndex = 6;
			this->btExecutar->Text = L"Executar";
			this->btExecutar->UseVisualStyleBackColor = true;
			this->btExecutar->Click += gcnew System::EventHandler(this, &frmPrincipal::btExecutar_Click);
			// 
			// btConectar
			// 
			this->btConectar->Location = System::Drawing::Point(606, 31);
			this->btConectar->Name = L"btConectar";
			this->btConectar->Size = System::Drawing::Size(151, 22);
			this->btConectar->TabIndex = 5;
			this->btConectar->Text = L"Conectar";
			this->btConectar->UseVisualStyleBackColor = true;
			this->btConectar->Click += gcnew System::EventHandler(this, &frmPrincipal::btConectar_Click);
			// 
			// txtBD
			// 
			this->txtBD->Location = System::Drawing::Point(449, 33);
			this->txtBD->Name = L"txtBD";
			this->txtBD->Size = System::Drawing::Size(151, 20);
			this->txtBD->TabIndex = 4;
			// 
			// txtHost
			// 
			this->txtHost->Location = System::Drawing::Point(292, 33);
			this->txtHost->Name = L"txtHost";
			this->txtHost->Size = System::Drawing::Size(151, 20);
			this->txtHost->TabIndex = 3;
			// 
			// txtSenha
			// 
			this->txtSenha->Location = System::Drawing::Point(135, 33);
			this->txtSenha->Name = L"txtSenha";
			this->txtSenha->PasswordChar = '?';
			this->txtSenha->Size = System::Drawing::Size(151, 20);
			this->txtSenha->TabIndex = 2;
			// 
			// txtLogin
			// 
			this->txtLogin->Location = System::Drawing::Point(5, 33);
			this->txtLogin->Name = L"txtLogin";
			this->txtLogin->Size = System::Drawing::Size(124, 20);
			this->txtLogin->TabIndex = 1;
			// 
			// txtSQL
			// 
			this->txtSQL->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtSQL->Location = System::Drawing::Point(6, 80);
			this->txtSQL->Multiline = true;
			this->txtSQL->Name = L"txtSQL";
			this->txtSQL->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtSQL->Size = System::Drawing::Size(752, 155);
			this->txtSQL->TabIndex = 0;
			// 
			// tabLog
			// 
			this->tabLog->Controls->Add(this->logBox);
			this->tabLog->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->tabLog->Location = System::Drawing::Point(4, 22);
			this->tabLog->Name = L"tabLog";
			this->tabLog->Padding = System::Windows::Forms::Padding(3);
			this->tabLog->Size = System::Drawing::Size(766, 423);
			this->tabLog->TabIndex = 2;
			this->tabLog->Text = L"Log";
			this->tabLog->UseVisualStyleBackColor = true;
			// 
			// logBox
			// 
			this->logBox->FormattingEnabled = true;
			this->logBox->Location = System::Drawing::Point(6, 10);
			this->logBox->Name = L"logBox";
			this->logBox->ScrollAlwaysVisible = true;
			this->logBox->Size = System::Drawing::Size(754, 407);
			this->logBox->TabIndex = 0;
			// 
			// barStatus
			// 
			this->barStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->barStatusJogo, this->barStatusBD, 
				this->barNumJogadores, this->barHora, this->barFPS, this->barTempoAtualizacao});
			this->barStatus->Location = System::Drawing::Point(0, 476);
			this->barStatus->Name = L"barStatus";
			this->barStatus->Size = System::Drawing::Size(776, 22);
			this->barStatus->TabIndex = 1;
			this->barStatus->Text = L"statusStrip1";
			// 
			// barStatusJogo
			// 
			this->barStatusJogo->AutoSize = false;
			this->barStatusJogo->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusJogo->Name = L"barStatusJogo";
			this->barStatusJogo->Size = System::Drawing::Size(120, 17);
			this->barStatusJogo->Text = L"Status do Jogo:";
			this->barStatusJogo->Click += gcnew System::EventHandler(this, &frmPrincipal::toolStripStatusLabel1_Click);
			// 
			// barStatusBD
			// 
			this->barStatusBD->AutoSize = false;
			this->barStatusBD->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusBD->Name = L"barStatusBD";
			this->barStatusBD->Size = System::Drawing::Size(120, 17);
			this->barStatusBD->Text = L"Status BD:";
			// 
			// barNumJogadores
			// 
			this->barNumJogadores->AutoSize = false;
			this->barNumJogadores->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barNumJogadores->Name = L"barNumJogadores";
			this->barNumJogadores->Size = System::Drawing::Size(200, 17);
			this->barNumJogadores->Text = L"Número de Jogador ON:";
			// 
			// barHora
			// 
			this->barHora->AutoSize = false;
			this->barHora->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barHora->Name = L"barHora";
			this->barHora->Size = System::Drawing::Size(100, 17);
			this->barHora->Text = L"Horario do Server";
			// 
			// barFPS
			// 
			this->barFPS->AutoSize = false;
			this->barFPS->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barFPS->Name = L"barFPS";
			this->barFPS->Size = System::Drawing::Size(60, 17);
			this->barFPS->Text = L"FPS";
			// 
			// barTempoAtualizacao
			// 
			this->barTempoAtualizacao->AutoSize = false;
			this->barTempoAtualizacao->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barTempoAtualizacao->Name = L"barTempoAtualizacao";
			this->barTempoAtualizacao->Size = System::Drawing::Size(150, 17);
			this->barTempoAtualizacao->Text = L"Tempo de Atualização:";
			// 
			// menu
			// 
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->arquivoToolStripMenuItem});
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(776, 24);
			this->menu->TabIndex = 2;
			this->menu->Text = L"menuStrip1";
			// 
			// arquivoToolStripMenuItem
			// 
			this->arquivoToolStripMenuItem->Name = L"arquivoToolStripMenuItem";
			this->arquivoToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->arquivoToolStripMenuItem->Text = L"&Arquivo";
			// 
			// timer
			// 
			this->timer->Interval = 33;
			this->timer->Tick += gcnew System::EventHandler(this, &frmPrincipal::timerBD_Tick);
			// 
			// frmPrincipal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 498);
			this->Controls->Add(this->barStatus);
			this->Controls->Add(this->menu);
			this->Controls->Add(this->abas);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menu;
			this->Name = L"frmPrincipal";
			this->Text = L"WarBugs Server";
			this->Load += gcnew System::EventHandler(this, &frmPrincipal::frmPrincipal_Load);
			this->abas->ResumeLayout(false);
			this->tabJogadoresOn->ResumeLayout(false);
			this->gbJogador->ResumeLayout(false);
			this->gbJogador->PerformLayout();
			this->gbServer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridJogadores))->EndInit();
			this->tabConfig->ResumeLayout(false);
			this->gbConfigBD->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->gbConfigIniciais->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->tabManutencaoBD->ResumeLayout(false);
			this->tabManutencaoBD->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridResultados))->EndInit();
			this->tabLog->ResumeLayout(false);
			this->barStatus->ResumeLayout(false);
			this->barStatus->PerformLayout();
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void frmPrincipal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {

			 }
	private: System::Void toolStripStatusLabel1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }
	private: System::Void btConectar_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			
			_dataBase = NULL;
			_dataBase = new CDataBase(toChar2(txtHost->Text),toChar2(txtBD->Text),toChar2(txtLogin->Text),toChar2(txtSenha->Text));
		 }

/*Transforma a porra do tipo string do windows em coisa de macho!*/
	private : char * toChar2(System::String^ str)
		{
			char * target;

			pin_ptr<const wchar_t> wch = PtrToStringChars( str );

			size_t i;

			int len = (( str->Length+1) * 2);

			target = new char[ len ];
						
			wcstombs_s(&i, target, (size_t)len, wch, (size_t)len );

			return target;
		}

private: System::Void timerBD_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
		
			 __int64 startTime = DateTime::Now.Ticks;
			 

			this->barStatusBD->Text = L"Status BD: "+( _dataBase->isConnected() ? "ON":"OFF");

			this->barHora->Text = L""+DateTime::Now;

			this->barNumJogadores->Text = L"Número de Jogadores: "+_coreServer->getPlayers()->size();

			_coreServer->readPackets();
			
			if(gridJogadores->Rows->Count > _coreServer->getPlayers()->size())
			{
				gridJogadores->Rows->Clear();
			}

			while(gridJogadores->Rows->Count < _coreServer->getPlayers()->size())
			{
				gridJogadores->Rows->Add(_coreServer->getPlayers()->size());
			}

			String ^ temp2;
			String ^ temp3;
			String ^ temp4;

			for(int i = 0; i < _coreServer->getPlayers()->size(); i++)
			{
				

				try
				{
					temp2 = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getName());
				}
				catch(...)
				{
					temp2 = L"";
				}

				try
				{
					temp3 = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getCharacter()->getName());
				}
				catch(...)
				{
					temp3 = L"";
				}

				try
				{
					temp4 = gcnew String(L""+_coreServer->getPlayers()->getElementAt(i)->getScene()->getID());
				}
				catch(...)
				{
					temp4 = L"";
				}

				//primeira coluna
				gridJogadores->Rows[i]->Cells[0]->Value = i+1;
				gridJogadores->Rows[i]->Cells[1]->Value = temp2;
				gridJogadores->Rows[i]->Cells[2]->Value = temp3;
				gridJogadores->Rows[i]->Cells[3]->Value = temp4;

			}

			
			//Atualiza os Server
			_coreServer->updateAll();



	/*		int tempoPing = ((DateTime::Now.Ticks/TimeSpan::TicksPerSecond) - _coreServer->getBeginTimePing());
	
			if(tempoPing > _coreServer->getIntervalTimePing() && _coreServer->getPlayers()->size() > 0)
			{
				//envia mensagem de ping
				_coreServer->sendMessage(true,-1,NULL,PING);

				for(int i = 0; i < _coreServer->getPlayers()->size(); i++)
				{

					//Verifica o jogador que está  com o ping Alto
					long pingInicial = _coreServer->getPlayers()->getElementAt(i)->getEndTimePing();
					long pingFinal   = _coreServer->getPlayers()->getElementAt(i)->getBeginTimePing();
					if( (pingFinal - pingInicial) >_coreServer->getToleranceMaxPing())
					{
						kicar(i);
					}
					else
					{
						_coreServer->getPlayers()->getElementAt(i)->setBeginTimePing(_coreServer->getBeginTimePing());
					}
				}
			}*/

			//Envia mensagens para os clientes
			_coreServer->sendAllMessages();

			//Verifica a taxa de atualização e FPS
			__int64 timeNow = DateTime::Now.Ticks;

			long time = (timeNow  - startTime)/TimeSpan::TicksPerMillisecond;

			this->barTempoAtualizacao->Text = L"Tempo Atualização: "+time;

			this->barFPS->Text = L"FPS: "+(1000/(timer->Interval + time));

		 }


private: System::Void btExecutar_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 try
			 {
				 if(_dataBase->insertNow(toChar2(txtSQL->Text)))
				 {
					 System::Windows::Forms::MessageBox::Show(L"OK, Feito!",L"Mensagem - OK");
				 }
				 else
				 {
					 System::Windows::Forms::MessageBox::Show(L"É... Deu pau!",L"Mensagem - Erro");			 
				 }
			 }
			 catch(...)
			 {
				System::Windows::Forms::MessageBox::Show(L"É... Deu pau! Não foi dos bons não.",L"Mensagem - Erro");
			 }
		 }
private: System::Void btConsultar_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 try{
					TDadosBD ^ dados = gcnew ArrayList();
					unsigned int numCampos;
					unsigned int numRegs;
					unsigned int indexCampos = 0, indexRegs = 0;
					gridResultados->Columns->Clear();
					
					if(_dataBase->selectNow(toChar2(txtSQL->Text), numCampos, numRegs, dados))
					{

						for(indexCampos = 0; indexCampos < numCampos; indexCampos++)
						{
							String ^ text = dados[0]->ToString();
							gridResultados->Columns->Add(L"_"+text,L""+text);
							dados->RemoveAt(0);
						}

						gridResultados->Rows->Add(numRegs);


						while (numRegs > indexRegs)
						{
							for(indexCampos = 0; indexCampos < numCampos; indexCampos++)
							{
								char * s = toChar2(dados[0]->ToString()) != NULL ? toChar2(dados[0]->ToString()): "NULL";
								String ^ text = gcnew String(s);
								gridResultados->Rows[indexRegs]->Cells[indexCampos]->Value = text;
								dados->RemoveAt(0);
							}

							indexRegs++;
						} 			
					}
				}
				catch(...)
				{
					System::Windows::Forms::MessageBox::Show(L"É... Deu pau! Preocupa não um dia resolve.",L"Mensagem - Erro");
				}
		 }
private: System::Void btKicar_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 int i = 0;
			 for(i = 0; i < gridJogadores->Rows->Count; i++)
			 {
				 if(gridJogadores->Rows[i]->Selected)
				 {
					 gridJogadores->Rows->RemoveAt(i);
					 kicar(i);
				 }
			 }
			 gridJogadores->Rows->Clear();

		 }
private: void kicar(int posJogador)
		 {
			 if(_coreServer->getPlayers()->size() > 0)
			 {
				char c[1400];
				CBugMessage m;
				m.init(c,1400);
	
				 m.writeByte(DISCONNECT);

				_coreServer->getPlayers()->getElementAt(posJogador)->getSocket()->SendLine(m);
				_coreServer->getPlayers()->getElementAt(posJogador)->getSocket()->Close();
				_coreServer->getPlayers()->removeJogadorAt(posJogador);					 
			}
		 }
private: System::Void btLigarServer_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer->Enabled = true;
			 this->barStatusJogo->Text = L"Status Jogo: "+( timer->Enabled ? "ON":"OFF");
		 }
private: System::Void btAplicarFPS_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 if(txtValorFPS->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorFPS->Text);
				 if(temp > 0)
				 {
					 _coreServer->setFPS(temp);
					 labValorFPS->Text = L""+temp;
					 timer->Interval = 1000/_coreServer->getFPS();
				 }
				 else
				 {
					 _coreServer->setFPS(0);				 
					 labValorFPS->Text = L"0";
				 }
				
			 }
		 }
private: System::Void btAplicarIntervaloPing_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorVerPing->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorVerPing->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimePing(temp);
					 _coreServer->setBeginTimePing(DateTime::Now.Ticks/TimeSpan::TicksPerSecond);
					 labValorVerPing->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimePing(0);
					 labValorVerPing->Text = L"0";
				 }
			 }

		 }
private: System::Void btAplicarToleranciaPing_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtToleranciaPing->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtToleranciaPing->Text);
				 if(temp > 0)
				 {
					 _coreServer->setToleranceMaxPing(temp);
					 labValorToleranciaPing->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setToleranceMaxPing(0);				 
					 labValorToleranciaPing->Text = L"0";
				 }
				
			 }

		 }
private: System::Void btAplicarHorasBkp_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorBkpTotal->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorBkpTotal->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimeSaveAll(temp);
					 labValorBkpTotal->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimeSaveAll(0);
					 labValorBkpTotal->Text = L"0";
				 }
				
			 }
		 }
private: System::Void btAplicarMercadoBkp_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorBkpMercado->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorBkpMercado->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimeSaveMarket(temp);
					 labValorBkpMercado->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimeSaveMarket(0);
					 labValorBkpMercado->Text = L"0";
				 }
				
			 }
		 }
};
}

